//Simple Breadth-First-Search to find shortest route between cities in Morrowind

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdlib>

using namespace std;

//names of connected cities in alphabetical order
const vector<string> NAMES = {"Ald'ruhn", "Balmora", "Caldera", "Dagon Fel", "Ebonheart",
                              "Fort Frostmoth", "Gnaar Mok", "Gnisis", "Hla Oad", "Holamayan",
                              "Khuul", "Maar Gan", "Molag Mar", "Raven Rock", "Sadrith Mora",
                              "Seyda Neen", "Suran", "Tel Arun", "Tel Branora", "Tel Mora", "Vivec", "Vos"};

//adjaceny list for each city (0-indexed where Ald'ruhn==0, Balmora==1, etc.)
const vector<vector<int> > ADJ = { {1,2,7,10,11,14,20}, {0,2,14,15,16,20}, {0,1,14,20},
                                   {10,14,17,19}, {8,9,14,18,20}, {10,13}, {8,10}, {0,10,11,15},
                                   {4,6,12,20}, {4}, {0,3,5,6,7,11}, {0,7,10}, {8,16,18,20},
                                   {5}, {3,4,18,19}, {1,7,16,20}, {1,12,15,20}, {3,19,21},
                                   {4,12,14,20}, {3,14,17,21}, {0,1,2,4,8,11,12,14,15,16,18}, {14,17,19} };

struct City
{
	string name;             //city name
	int index;               //city index (0-indexed)
	vector<int> adj;         //city's adjacney matrix
	int distance = -1;       //city's distance from starting city (FROM)
	City* backedge = NULL;   //city's backedge to previous city
};

void initialize(vector<City*>& cv)
{
	//simply use the hard-coded NAMES and ADJ vectors to feed city info into structs
	for (int i = 0; i < NAMES.size(); i++){
		City* c = new City();
		c->index = i;
		c->name = NAMES[i];
		c->adj = ADJ[i];
		cv.push_back(c);
	}
}

void print(vector<City*>& cv)
{
	//prints each city's index followed by its name for user to make selection
	for (int i = 0; i < cv.size(); i++){
		printf("%2d: ", cv[i]->index);
		cout << cv[i]->name << endl;
	}
	printf("99: ALL CITIES\n");
}

void bfs(vector<City*>& cv, int from)
{
	multimap<int, City*> q;
	vector<City*> qu;

	//set all distances to -1 and backedges to NULL
	for (int i = 0; i < NAMES.size(); i++){
		cv[i]->distance = -1;
		cv[i]->backedge = NULL;
	}

	//set starting node FROM's distance to zero and insert into queue
	cv[from]->distance = 0;
	q.insert(pair<int, City*>(0, cv[from]));

	//while queue is not empty, pop city at front of queue off and look at its adjacency list
	while (!q.empty()){
		City* temp = q.begin()->second;
		q.erase(q.begin());

		//for each city adjacent to current city, check if its been visited
		vector<int>::iterator vit;
		for (vit = temp->adj.begin(); vit != temp->adj.end(); vit++){
			//if not yet visited, set adjacent city's distance and backedge accordingly,
			//   then insert it into the queue
			if (cv[*vit]->distance == -1){
				cv[*vit]->distance = temp->distance+1;
				cv[*vit]->backedge = temp;
				q.insert(pair<int, City*>(temp->distance+1, cv[*vit]));
			}
		}
	}
}

void find_all(vector<City*>& cv)
{
	//analyze every fastest route for every possible starting and ending cities
	//write the reults to a .txt file
	FILE *fp;
	fp = fopen("./morrowind_paths.txt", "w+");
	for (int i = 0; i < NAMES.size(); i++){
		vector<City*> path;
		bfs(cv, i);
		for (int j = 0; j < NAMES.size(); j++){
			if (j == i) continue;
			City* loop = cv[j];
			while (loop != cv[i]){
				path.push_back(loop->backedge);
				loop = loop->backedge;
			}

			//print path and write to .txt file
			for (int i = path.size()-1; i >= 0; i--){
				cout << path[i]->name << " -> ";
				fprintf(fp, "%s -> ",path[i]->name.c_str());
			}
			cout << cv[j]->name << endl;
			fprintf(fp, "%s\n", cv[j]->name.c_str());
			path.clear();
		}
		if (i < NAMES.size()-1){
			printf("\n");
			fprintf(fp, "\n");
		}
	}
}

void find_one(vector<City*>& cv, int from, int to)
{
	//bfs to find shortest path
	vector<City*> path;
	bfs(cv, from);

	//trace backedges: TO -> FROM
	City* loop = cv[to];
	while (loop != cv[from]){
		path.push_back(loop->backedge);
		loop = loop->backedge;
	}

	//print path
	printf("\nShortest route:\n");
	for (int i = path.size()-1; i >= 0; i--){
		cout << path[i]->name << " -> ";
	}
	cout << cv[to]->name << endl;
	cout << "Total travels: " << path.size() << endl << endl;
}

void get_input(int& n, string s)
{
	bool valid = 0;
	while (!valid){
		printf("Type number of city you're travelling %s: ", s.c_str());
		if (cin >> n){
			if (n >= 0 && n <= 21) valid = 1;
			else if (n == 99) return;
			else cout << "Invalid input. Please try again\n";
		}
		else cout << "Invalid input. Please try again\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

int main()
{
	//initialize cities
	vector<City*> cv;
	initialize(cv);

	//get cities from user
	int from;
	int to;
	print(cv);
	get_input(from, "from");
	if (from != 99) get_input(to, "to");

	//if user inputs a 99, find all fastest paths, print and write to .txt file
	if (from == 99 || to == 99) find_all(cv);

	//otherwise get fastest path for user
	else find_one(cv, from, to);

	return 0;
}
