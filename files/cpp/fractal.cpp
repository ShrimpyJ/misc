#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int LOOPS = 5;
const int ROWS = 129;

class Grid{
public:
	int rows = ROWS;
	int cols = rows*0.56;
	map<int, char> m;
	int center = (rows*cols) / 2;

	Grid()
	{
		for (int i = 0; i < rows*cols; i++) m.insert(pair<int,char>(i, '-'));
	}

	void print()
	{
		map<int, char>::iterator it;
		for (it = m.begin(); it != m.end(); it++){
			if (it->first != 0 && it->first % rows == 0) cout << endl;
			printf("%c", it->second);
		}
		cout << endl;
	}

};

void recursive(int start, vector<int> pos, map<int, char>& m)
{
	if (start < 0) return;
}

int main()
{
	Grid grid;

	//set up
	map<int, char>::iterator it;
	it = grid.m.find(grid.center);
	it->second = 'O';
	
	vector<int> shape;
	shape.push_back(grid.center);
	int width = shape.size();
	int height = shape.size();

	for (int i = 0; i < LOOPS; i++){
		grid.print();
		int size = shape.size();
		for (int j = 0; j < size; j++){
			//horizontal
			shape.push_back(shape[j]-width);
			shape.push_back(shape[j]+width);

			//vertical
			shape.push_back(shape[j]-(height*grid.rows));
			shape.push_back(shape[j]+(height*grid.rows));
		}
		for (int j = 0; j < shape.size(); j++){
			it = grid.m.find(shape[j]);
			it->second = 'O';
		}
		width *= 3;
		height *= 3;
		cout << endl;
	}

	grid.print();

	return 0;
}
