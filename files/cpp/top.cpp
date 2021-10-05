#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <tr1/unordered_map>
#include <vector>
#include <algorithm>
#include <ctime>
#include <map>
#include <cmath>
#include <random>
#include <unistd.h>

using namespace std;

const int MS = 25000;
const wchar_t ASCII[20] = {L'\u2027',L'\u2032',L'\u2033',L'\u2034',L'\u2058',L'\u2059',
	                     L'\u23C9',L'\u22B9',L'\u2E38',L'\u22A4',L'\u2A4D',L'\u205C',L'\u28FF',
			     L'\u2A68',L'\u2A69',L'\u2A0C',L'\u2230',L'\u2593',L'\u2592',L'\u2591'};

class SquareMile{
public:
	int SIZE, FULL;
	int HEIGHT, MAX, INC, DEC, DIV;
	std::tr1::unordered_map<int,double> sqm;
	int iterations;
	pair<int,int> severity;
	vector<wchar_t> ascii;

	SquareMile(int n){
		SIZE = n;
		FULL = SIZE*SIZE;
		HEIGHT = SIZE*2;
		MAX = HEIGHT*2;
		INC = ceil(SIZE / 100.0);
		DEC = SIZE * ((rand() % 100+1) * .01);
		DIV = (MAX / (sizeof(ASCII) / 4))+1;
	}

	void genMile(vector<double> &last);
	wchar_t heightToAscii(int h);
	void print();
};

wchar_t SquareMile::heightToAscii(int h)
{
	int n = h / DIV;
	//if (n == sizeof(ASCII) / 4) n--;
	//wcout << ASCII[n] << "   at   " << n << endl;
	return ASCII[n];
}

//values (r & 16) and (r & 31) give flat terrain
//values (r & 31) and (r & 0) give downhill terrain
//values (r & 0) and (r & 31) give uphill terrain
void SquareMile::genMile(vector<double> &last)
{
	int h;         //starting altitude
	if (last.empty()){
		h = rand() % MAX;
	}
	else{
		h = last[0];
	}
	int down = 0;   //explained above
	int up = 16;
	int above, prev;           //altitude of above and left squares
	int iterations = 0;        //# of loops an UP/DOWN/FLAT event should occur
	int less = 0, more = 0;    //these grow in size during long periods of lowest/highest altitude
	for (int i = 0; i < FULL; i++){
		std::tr1::unordered_map<int,double>::iterator itr;
		if (i == SIZE){
			last.clear();
		}

		//handle top row with last
		if (i < SIZE && !last.empty()){
			h = last[i];
			sqm.insert(pair<int,double>(i,h));
			wchar_t c = heightToAscii(h);
			ascii.push_back(c);
			continue;
		}

		//handle left edge cases (only look at above value)
		if (i % SIZE == 0 && i != 0){
			itr = sqm.find(i-SIZE);
			h = itr->second;
		}
		//handle all cases other than first row and left column (look at above and prev)
		else if (i >= SIZE){
			itr = sqm.find(i-SIZE);
			above = itr->second;
			itr = sqm.find(i-1);
			prev = itr->second;
			if (above != prev){
				int diff = abs(above - prev) / 2;
				if (above > prev) h = above - diff;
				else h = prev - diff;
			}
			else h = above;
		}

		//once UP/DOWN/FLAT event ends, roll for next event and length of next event
		if (iterations == 0){
			//roll length of next event
			iterations = rand() % (FULL / (SIZE / DEC));

			//roll to decide UP/DOWN/FLAT events
			int e = rand() % 3;
			if (e == 0){        //UP
				down = 0;
				up = 31;
			}
			else if (e == 1){   //DOWN
				down = 31;
				up = 0;
			}
			else{               //FLAT
				down = 16;
				up = 31;
			}
		}

		int r = rand() % 123456789;

		if (r & down) h -= INC;     //decrement height (more likely during DOWN)
		else if (r & up) h += INC;  //increment height (more likely during UP)

		//handle periods where height exceeds either lower or upper bounds
		if (h > MAX){
			h = MAX - less;
			less++;         //increment this to subtract more height next time MAX is exceeded

			//keep 'less' from getting TOO big
			int n = rand() % 15+1;
			if (n < 4) n += 3;
			if (less >= ceil(MAX*(n*.01))){
				less -= INC;
			}
		}
		else if (h < 0){
			h = 0 + more;
			more++;        //increment this to add more height next time 0 is exceeded

			//keep 'more' from getting TOO big
			int n = rand() % 15+1;
			if (n < 4) n += 3;
			if (more >= ceil(MAX*(n*.01))){
				more -= INC;
			}
		}
		sqm.insert(pair<int,double>(i,h));
		if (i >= FULL - SIZE){
			last.push_back(h);
		}
		iterations--;
		wchar_t c = heightToAscii(h);
		ascii.push_back(c);
	}

	print();
}

void SquareMile::print()
{
	std::tr1::unordered_map<int,double>::iterator itr;
	int i = 1;
	for (int i = 1; i <= ascii.size(); i++){
		wcout << ascii[i-1];
		if (i % SIZE == 0){
			usleep(MS);
			wcout << '\n';
		}
	}
}

class Map{
public:
	vector<SquareMile> mv;
};

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
	wchar_t ch = L'\u2654';
	srand(time(NULL));

	if (argc != 3){
		printf("Incorrect # of args. Format:\n./top SIZE_OF_MILE NUM_OF_MILES\n");
		printf("\nExample:\n./top 22 3\n   generates 3 miles of size 22\n");
		printf("\nInput 0 as last number for infinite miles\n");
		exit(1);
	}
	Map m;
	int numMiles = atoi(argv[2]);
	vector<double> last;

	if (numMiles == 0){
		while (true){
			SquareMile sqMile(atoi(argv[1]));
			sqMile.genMile(last);
		}
	}

	for (int i = 0; i < numMiles; i++){
		SquareMile sqMile(atoi(argv[1]));
		sqMile.genMile(last);
	}

	return 0;
}
