#include <iostream>
#include <cstdlib>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <vector>
#include <set>
#include <bits/stdc++.h>

using namespace std;

void print(string word);
void permute(string word, int l, int r, int& count, unordered_set<string>& list, unordered_set<string>& str);
void find(string word, unordered_set<string>& list, unordered_set<string>& str);

int main()
{
	ifstream input;
	unordered_set<string> list;
	unordered_set<string> str;
	string temp;

	input.open("/usr/share/dict/words");
	while (!input.eof()){
		input >> temp;
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		list.insert(temp);
	}
	input.close();

	string word;
	cout << "Enter word (all lowercase): ";
	cin >> word;
	int count = 0, factorial = 1;

	for (int i = word.size(); i > 0; i --){
		factorial *= i;
	}

	int l = 0;
	int r = word.size()-1;
	permute(word,l,r,count,list,str);
	find(word,list,str);

	cout << "Total permutations: " << count << endl;

	return 0;
}

void print(string word)
{
	for (int i = 0; i < word.size(); i++){
		cout << word[i];
	}
	cout << endl;
}

void permute(string word, int l, int r, int& count, unordered_set<string>& list, unordered_set<string>& str)
{
	if (l == r){
		print(word);
		str.insert(word);
		count++;
	}
	for (int i = l; i <= r; i++){
		swap(word[l],word[i]);
		permute(word,l+1,r,count,list,str);
		swap(word[l],word[i]);
	}
}

void find(string word, unordered_set<string>& list, unordered_set<string>& str)
{
	unordered_set<string>::iterator it;
	for (it = str.begin(); it != str.end(); ++it){
	//for (int i = 0; i < list.size(); i++){
		if (list.find(*it) != list.end()){
			cout << "\n\nPossible solution found: " << *it << endl;
		}
	}
}
