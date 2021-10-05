#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <map>
#include <ctime>

using namespace std;

class Rotor
{
public:
	int A;
	int B;
	int C;
	
	Rotor()
	{
		A = (rand() % 26) + 1;
		B = (rand() % 26) + 1;
		C = (rand() % 26) + 1;
	}

	void Encrypt(vector<int>& message, int start, int end)
	{
		for (int i = 0; i < message.size(); i++){
			if (message[i] == ' ') continue;
			message[i] += C;
			while (message[i] > end) message[i] -= (end - start) + 1;
			message[i] += B;
			while (message[i] > end) message[i] -= (end - start) + 1;
			message[i] += A;
			while (message[i] > end) message[i] -= (end - start) + 1;

			C++;
			if (C == 27){
				C = 1;
				B++;
				if (B == 27){
					B = 1;
					A++;
					if (A == 27){
						A = 1;
					}
				}
			}
		}
	}

	void Decrypt(vector<int>& message, int start, int end, int a, int b, int c)
	{
		for (int i = 0; i < message.size(); i++){
			if (message[i] == ' ') continue;
			message[i] -= a;
			while (message[i] < start) message[i] += (end - start) + 1;
			message[i] -= b;
			while (message[i] < start) message[i] += (end - start) + 1;
			message[i] -= c;
			while (message[i] < start) message[i] += (end - start) + 1;

			c++;
			if (c == 27){
				c = 1;
				b++;
				if (b == 27){
					b = 1;
					a++;
					if (a == 27){
						a = 1;
					}
				}
			}
		}
	}
};

int main()
{
	srand(time(NULL));
	Rotor *rotor = new Rotor();
	printf("Starting position: %d %d %d\n", rotor->A, rotor->B, rotor->C);
	vector<int> message;
	char c;
	int x = rotor->A;
	int y = rotor->B;
	int z = rotor->C;

	//a = 97    z = 122     range: 26 inclusive
	//get message
	while (cin.get(c)){
		if (c == '\n') break;
		if (c <= 90 && c >= 65) c += 32;
		message.push_back(c);
	}

	//print original message
	printf("Original message: ");
	for (int i = 0; i < message.size(); i++) printf("%c", message[i]);
	cout << endl;

	//encrypt message
	rotor->Encrypt(message, 'a', 'z');

	//print encrypted message
	printf("Encrypted message: ");
	for (int i = 0; i < message.size(); i++) printf("%c", message[i]);
	cout << endl;

	//decrypt message
	rotor->Decrypt(message, 'a', 'z', x, y, z);

	//print decrypted message
	printf("Decrypted message: ");
	for (int i = 0; i < message.size(); i++) printf("%c", message[i]);
	cout << endl;

	return 0;
}
