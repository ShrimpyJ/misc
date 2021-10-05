#include <fstream>
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

void readFile(struct IPAddr ip[], int& totalBans);
void getNum(struct IPAddr ip[], int totalBans);
void print(struct IPAddr ip[], int totalBans);
void findCountry(struct IPAddr ip[], int totalBans);
void getFullName(struct IPAddr ip[], int totalBans, vector<string>& key, vector<int>& index);
void getInfo(vector<int>& index, vector<string>& key, string temp);

struct IPAddr{
	string str;
	unsigned long int num;
	string full;
	string byte[4];
	string country;
};

int main()
{
	string temp;
	IPAddr ip[500];
	int totalBans;

	//read log file for all banned IP's
	readFile(ip,totalBans);

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

	//search abbreviated country for matching full name
	//(calls getInfo function from within)
	vector<string> key;
	vector<int> index;
	getFullName(ip,totalBans,key,index);

	//print countries and number of bans for each
	cout.flush();
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

void readFile(struct IPAddr ip[], int& totalBans){
	ifstream input;
	input.open(FAIL2BAN_LOG);
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

	totalBans = i;
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

void findCountry(struct IPAddr ip[], int totalBans)
{
	ofstream output;
	ifstream input;
	string temp;
	output.open(DIRECTORY + "ipinfo");
	for (int i = 0; i < 20; ++i){
		cin.clear();
		input.open(DIRECTORY + "temp");
		//write current IP to temp file (will be overwritten by next IP)
		string get = "whois " + ip[i].str + " > " + DIRECTORY + "temp 2>&1";
		const char *command = get.c_str();
		system(command);

		cout << "Working on IP: " << ip[i].str << '\n';
		//find country in temp file
		while (input >> temp){
			if (temp == "country:" || temp == "Country:"){
				input >> temp;
				cout << "Country: " << temp << '\n';
				ip[i].country = temp;
				temp = "empty";
				break;
			}
		}
		if (temp != "empty"){
			string get = "curl ipinfo.io/" + ip[i].str + " > " + DIRECTORY + "temp 2>&1";
			//curl ipinfo.io/177.93.68.240 > /home/pete/ipbans/temp 2>&1
			const char *command = get.c_str();
			system(command);
			while (input >> temp){
				cout << temp << "     ";
				if (temp == "\"country\":" || temp == "\"Country\":"){
					cout << "Here";
					cin.ignore();
					input >> temp;
					cout << "Country: " << temp << '\n';
					ip[i].country = temp;
					temp = "empty";
					break;
				}
			}
				cin.ignore();
		}

		//write to output file
		output << ip[i].str << '\t';
		output << ip[i].country << '\n';
		input.close();
	}
	output.close();
}

void getFullName(struct IPAddr ip[], int totalBans, vector<string>& key, vector<int>& index)
{
	ifstream input;
	string temp;
	for (int i = 0; i < totalBans; ++i){
		//search abbreviated country for matching full name
		input.open(DIRECTORY + "countries.txt");
		while (input >> temp){
			if (ip[i].country == temp){
				char ch;
				input.get(ch);
				getline(input,temp);
				//get info regarding # of bans country has
				getInfo(index,key,temp);
				input.close();
				break;
			}
		}
	}
}

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
