#include <fstream>
#include <unistd.h>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <bits/stdc++.h>

using namespace std;

//directory holding all files
const string DIRECTORY = "/home/pete/ipbans/";
//location of fail2ban log file
const string FAIL2BAN_LOG = "/var/log/fail2ban.log";
//artificial time limit between ip lookups (change to 0 for instant)
const unsigned int usecs = 33333;

void readFile(struct IPAddr ip[], ifstream& input, int& totalBans, int& logCount);
void getNum(struct IPAddr ip[], int totalBans);
void print(struct IPAddr ip[], int totalBans);
void findCountry(struct IPAddr ip[], int totalBans);
void getInfo(vector<int>& index, vector<string>& key, string temp);
void getFullName(struct IPAddr ip[], int totalBans, string& temp);

struct IPAddr{
	string str;
	unsigned long int num;
	string full;
	string byte[4];
	string country;
};

int main()
{
	cout << "\n\n   This program uses GeoIP to lookup country information.";
	string temp;
	IPAddr ip[500];
	int totalBans;
	int logCount = 1;
	ifstream input;
	input.open(FAIL2BAN_LOG);

	//read log file for all banned IP's
	readFile(ip,input,totalBans,logCount);
	input.close();

	//print chronologically
	cout << "\n\nBanned IP Addresses in chronological order (left to right):\n";
	print(ip, totalBans);
	
	//convert IP strings to ints and sort
	getNum(ip, totalBans);

	//print sorted (ascending)
	cout << "\n\nBanned IP Addresses in ascending order (left to right):\n";
	print(ip, totalBans);
	
	cout << "\nTotal bans: " << totalBans << '\n';

	cout << "\nPress ENTER to begin geolocation process\n\n";
	cin.clear();
	cin.ignore();

	//find country using IP
	findCountry(ip,totalBans);

	//get info for # of bans per country
	vector<int> index;
	vector<string> key;
	for (int i = 0; i < totalBans; ++i){
		getInfo(index,key,ip[i].country);
	}

	//print countries and number of bans for each
	cout << "Geotracking complete\n\nAll countries and # of bans for each:\n\n";
	for (int i = 0; i < index.size(); ++i){
		cout << key[i] << '\n';
		for (int j = 0; j < index[i]; ++j){
			cout << '-';
		}
		cout << index[i];
		cout << endl;
	}

	cout << "\nTotal bans: " << totalBans << '\n';
	return 0;
}

void readFile(struct IPAddr ip[], ifstream& input, int& totalBans, int& logCount){
	string temp;
	int i = 0, j = 0;
	int count;

	//scan through fail2ban log for the word "Ban"
	while (input >> temp){
		int count = 0;
		//if ban is found, check if IP is already in struct to avoid repeats
		if (temp == "Ban"){
			input >> temp;
			for (j = 0; j < i; ++j){
				if (ip[j].str != temp){
					count++;
				}
			}
			if (count == i){
				ip[i].str = temp;
				i++;
			}
		}
	}
	input.close();

	//search through old log roll files
	string logCountString = to_string(logCount);
	input.open(FAIL2BAN_LOG + "." + logCountString);
	if (!input.fail()){
		logCount++;
		readFile(ip,input,totalBans,logCount);
	}

	//return when no more files
	else{
		totalBans = i;
		return;
	}
}

void print(struct IPAddr ip[], int totalBans)
{
	for (int i = 0; i < totalBans; ++i){
		for (int j = 0; j < 4; ++j){
			cout << setw(20) << left << ip[i+j].str;
		}
		i += 3;
		cout << '\n';
	}
}

void getNum(struct IPAddr ip[], int totalBans)
{
	string num;

	for (int index = 0; index < totalBans; ++index){
		//store each byte of IPADDR (4 bytes each)
		int j = 0;
		string temp = ip[index].str;
		for (int i = 0; i < 4; ++i){
			while (temp[j] != '.' && j < temp.size()){
				ip[index].byte[i] += temp[j];
				j++;
			}
			j++;
		}
	
		//add '0' character(s) to beginning of bytes with less than 3 digits 
		j = 0;
		for (int i = 0; i < 4; ++i){
			if (ip[index].byte[i].size() == 2){
				ip[index].byte[i] = "0" + ip[index].byte[i];
			}
			else if (ip[index].byte[i].size() == 1){
				ip[index].byte[i] = "00" + ip[index].byte[i];
			}
		}
		//concatenate bytes into full string, convert to int and store in iArray
		num = ip[index].byte[0] + ip[index].byte[1] + ip[index].byte[2] + ip[index].byte[3];
		unsigned long int n;
		n = stol(num);
		ip[index].num = n;

		//reset num
		num = "";
	}

	//sort IP's from smallest to largest
	int max,i,j;
	for (i = 0; i < totalBans - 1; ++i){
		max = i;
		for (j = i+1; j < totalBans; ++j){
			if (ip[j].num < ip[max].num){
				max = j;
			}
		}
		struct IPAddr tmp = ip[i];
		ip[i] = ip[max];
		ip[max] = tmp;
	}
}

void findCountry(struct IPAddr ip[], int totalBans)
{
	ofstream output;
	ifstream input;
	string temp;
	output.open(DIRECTORY + "ipinfo");
	for (int i = 0; i < totalBans; ++i){
		cin.clear();
		input.open(DIRECTORY + "temp");
		//write current IP to temp file using geoiplookup (will be overwritten by next IP)
		string get = "geoiplookup " + ip[i].str + " > " + DIRECTORY + "temp 2>&1";
		const char *command = get.c_str();
		system(command);

		cout << "Working on IP: " << ip[i].str << '\n';
		usleep(usecs);
		//find country in temp file
		for (int j = 0; j < 5; ++j){
			input >> temp;
			if (j == 3){
				char ch;
				input.get(ch);
				getline(input,ip[i].country);
				transform(ip[i].country.begin(), ip[i].country.end(), ip[i].country.begin(), ::toupper);

				//if geoiptracker fails, use whois
				if (ip[i].country == "ADDRESS NOT FOUND"){
					string get = "whois " + ip[i].str + " > " + DIRECTORY + "temp 2>&1";
					const char *command = get.c_str();
					system(command);
					while (input >> temp){
						if (temp == "country:" || temp == "Country:"){
							input >> temp;
							getFullName(ip,totalBans,temp);
							ip[i].country = temp;
							break;
						}
					}
				}
			}
		}
		cout << "Country: " << ip[i].country << '\n';

		//write to output file
		output << ip[i].str << '\t';
		output << ip[i].country << '\n';
		input.close();
	}
	output.close();
}

//find # of bans per country
void getInfo(vector<int>& index, vector<string>& key, string temp)
{
	if (key.size() == 0){
		key.push_back(temp);
		index.push_back(1);
		return;
	}
	int i = 0;
	for (i = 0; i < key.size(); ++i){
		//if match is found, increment index of matching string and return
		if (key[i] == temp){
			index[i]++;
			return;
		}
	}

	//if no matches found, push new string and int into vectors
	if (key.size() == i){
		key.push_back(temp);
		index.push_back(1);
	}
}


/////////////////only called if geoiplookup fails to find address////////////////////
void getFullName(struct IPAddr ip[], int totalBans, string& temp)
{
	ifstream input;
	string s;
	for (int i = 0; i < totalBans; ++i){
		//search abbreviated country for matching full name
		input.open(DIRECTORY + "countries.txt");
		while (input >> s){
			if (s == temp){
				char ch;
				input.get(ch);
				getline(input,temp);
				//get info regarding # of bans country has
				input.close();
				break;
			}
		}
	}
}
