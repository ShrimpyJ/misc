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

////adjacency lists for each city (0-indexed where Ald'ruhn==0, Balmora==1, ... Vos==21)////
//adjacency list for all connections (boat, silt strider, and mage guild)
const vector<vector<int> > ADJ = { {1,2,7,10,11,14,20},                //00: Ald'ruhn
                                   {0,2,14,15,16,20},                  //01: Balmora
                                   {0,1,14,20},                        //02: Caldera
                                   {10,14,17,19},                      //03: Dagon Fel
                                   {8,9,14,18,20},                     //04: Ebonheart
                                   {10,13},                            //05: Fort Frostmoth
                                   {8,10},                             //06: Gnaar Mok
                                   {0,10,11,15},                       //07: Gnisis
                                   {4,6,12,20},                        //08: Hla Oad
                                   {4},                                //09: Holamayan
                                   {0,3,5,6,7,11},                     //10: Khuul
                                   {0,7,10},                           //11: Maar Gan
                                   {8,16,18,20},                       //12: Molag Mar
                                   {5},                                //13: Raven Rock
                                   {3,4,18,19},                        //14: Sadrith Mora
                                   {1,7,16,20},                        //15: Seyda Neen
                                   {1,12,15,20},                       //16: Suran
                                   {3,19,21},                          //17: Tel Aruhn
                                   {4,12,14,20},                       //18: Tel Branora
                                   {3,14,17,21},                       //19: Tel Mora
                                   {0,1,2,4,8,11,12,14,15,16,18},      //20: Vivec
                                   {14,17,19} };                       //21: Vos

//adjacency list for boat connections
const vector<vector<int> > BAD = { {},                                 //00: Ald'ruhn
                                   {},                                 //01: Balmora
                                   {},                                 //02: Caldera
                                   {10,14,17,19},                      //03: Dagon Fel
                                   {8,9,14,18,20},                     //04: Ebonheart
                                   {},                                 //05: Fort Frostmoth
                                   {8,10},                             //06: Gnaar Mok
                                   {},                                 //07: Gnisis
                                   {4,6,12,20},                        //08: Hla Oad
                                   {4},                                //09: Holamayan
                                   {3,6},                              //10: Khuul
                                   {},                                 //11: Maar Gan
                                   {8,18,20},                          //12: Molag Mar
                                   {},                                 //13: Raven Rock
                                   {3,4,18,19},                        //14: Sadrith Mora
                                   {},                                 //15: Seyda Neen
                                   {},                                 //16: Suran
                                   {3,19,21},                          //17: Tel Aruhn
                                   {4,12,14,20},                       //18: Tel Branora
                                   {3,14,17,21},                       //19: Tel Mora
                                   {4,8,12,18},                        //20: Vivec
                                   {14,17,19} };                       //21: Vos

//adjacency list for silt strider connections
const vector<vector<int> > SAD = { {1,7,10,11},                        //00: Ald'ruhn
                                   {0,15,16,20},                       //01: Balmora
                                   {},                                 //02: Caldera
                                   {},                                 //03: Dagon Fel
                                   {},                                 //04: Ebonheart
                                   {},                                 //05: Fort Frostmoth
                                   {},                                 //06: Gnaar Mok
                                   {0,10,11,15},                       //07: Gnisis
                                   {},                                 //08: Hla Oad
                                   {},                                 //09: Holamayan
                                   {0,7,11},                           //10: Khuul
                                   {0,7,10},                           //11: Maar Gan
                                   {16,20},                            //12: Molag Mar
                                   {},                                 //13: Raven Rock
                                   {},                                 //14: Sadrith Mora
                                   {1,7,16,20},                        //15: Seyda Neen
                                   {1,12,15,20},                       //16: Suran
                                   {},                                 //17: Tel Aruhn
                                   {},                                 //18: Tel Branora
                                   {},                                 //19: Tel Mora
                                   {1,12,15,16},                       //20: Vivec
                                   {} };                               //21: Vos

//adjacency list for mage guild connections
const vector<vector<int> > MAD = { {1,2,14,20},                        //00: Ald'ruhn
                                   {0,2,14,20},                        //01: Balmora
                                   {0,1,14,20},                        //02: Caldera
                                   {},                                 //03: Dagon Fel
                                   {},                                 //04: Ebonheart
                                   {},                                 //05: Fort Frostmoth
                                   {},                                 //06: Gnaar Mok
                                   {},                                 //07: Gnisis
                                   {},                                 //08: Hla Oad
                                   {},                                 //09: Holamayan
                                   {},                                 //10: Khuul
                                   {},                                 //11: Maar Gan
                                   {},                                 //12: Molag Mar
                                   {},                                 //13: Raven Rock
                                   {0,1,2,20},                         //14: Sadrith Mora
                                   {},                                 //15: Seyda Neen
                                   {},                                 //16: Suran
                                   {},                                 //17: Tel Aruhn
                                   {},                                 //18: Tel Branora
                                   {},                                 //19: Tel Mora
                                   {0,1,2,14},                         //20: Vivec
                                   {} };                               //21: Vos


struct City
{
	string name;             //city name
	int index;               //city index (0-indexed)
	vector<int> adj;         //city's adjacency matrixes
	vector<int> bad;
        vector<int> sad;
        vector<int> mad;
	int distance = -1;       //city's distance from starting city (FROM)
	City* backedge = NULL;   //city's backedge to previous city
};

void initialize(vector<City*>& cv)
{
	//simply use the hard-coded NAMES and adj vectors to feed city info into structs
	for (int i = 0; i < NAMES.size(); i++){
		City* c = new City();
		c->index = i;
		c->name = NAMES[i];
		c->adj = ADJ[i];
		c->bad = BAD[i];
		c->sad = SAD[i];
		c->mad = MAD[i];
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

bool bfs(vector<City*>& cv, int from, vector<int> adj)
{
	vector<int> adj_list = adj;
	//return false if no way to travel by given travel type
	if (adj_list.empty()) return false;
	
	//queue of cities
	multimap<int, City*> q;

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
//		City* temp = q.begin()->second;
		q.erase(q.begin());

		//for each city adjacent to current city, check if its been visited
		vector<int>::iterator vit;
		for (vit = adj_list.begin(); vit != adj_list.end(); vit++){
			cout << "{BIT\n";
			if (cv[*vit] == NULL){
				cout <<"ETJEITJEITJEITJEITJEITJ\n";
				exit(1);
			}

			//if not yet visited, set adjacent city's distance and backedge accordingly,
			//   then insert it into the queue
			if (cv[*vit]->distance == -1){
				cv[*vit]->distance = cv[*vit]->distance+1;
				cv[*vit]->backedge = cv[*vit];
				q.insert(pair<int, City*>(cv[*vit]->distance+1, cv[*vit]));
			}
		}
	}

	return true;
}

void find_all(vector<City*>& cv)
{
//	//analyze every fastest route for every possible starting and ending cities
//	//write the reults to a .txt file
//	FILE *fp;
//	fp = fopen("./morrowind_paths.txt", "w+");
//	for (int i = 0; i < NAMES.size(); i++){
//		vector<City*> path;
//		bfs(cv, i);
//		for (int j = 0; j < NAMES.size(); j++){
//			if (j == i) continue;
//			City* loop = cv[j];
//			while (loop != cv[i]){
//				path.push_back(loop->backedge);
//				loop = loop->backedge;
//			}
//
//			//print path and write to .txt file
//			for (int i = path.size()-1; i >= 0; i--){
//				cout << path[i]->name << " -> ";
//				fprintf(fp, "%s -> ",path[i]->name.c_str());
//			}
//			cout << cv[j]->name << endl;
//			fprintf(fp, "%s\n", cv[j]->name.c_str());
//			path.clear();
//		}
//		if (i < NAMES.size()-1){
//			printf("\n");
//			fprintf(fp, "\n");
//		}
//	}
}

void find_one(vector<City*>& cv, int from, int to, int travel_type)
{
	//bfs to find shortest path
	bool valid_path = 0;
	int failures = 0;
	while (!valid_path){
		if      (travel_type == 0) valid_path = bfs(cv, from, cv[from]->bad);
		else if (travel_type == 1) valid_path = bfs(cv, from, cv[from]->sad);
		else if (travel_type == 2) valid_path = bfs(cv, from, cv[from]->mad);
		else    valid_path = bfs(cv, from, cv[from]->adj);

		if (!valid_path) failures++;

		if (failures == 1){
			if      (travel_type == 0) travel_type = 1;
			else if (travel_type == 1) travel_type = 0;
			else if (travel_type == 2) travel_type = 0;
		}
		else if (failures == 2){
			if      (travel_type == 0 || travel_type == 1) travel_type = 99;
			else if (travel_type == 2) travel_type = 99;
		}
	}

	//trace backedges: TO -> FROM
	vector<City*> path;
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

void get_input(int& n, string s, int lb, int ub)
{
	bool valid = 0;
	while (!valid){
		printf("%s: ", s.c_str());
		if (cin >> n){
			if (n >= lb && n <= ub) valid = 1;
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
	get_input(from, "Type number of city you're travelling from", 0, 21);
	if (from != 99) get_input(to, "Type number of city you're travelling to", 0, 21);

	//get nearest way of travel from user
	int travel_type;
	printf("\n 0: Boat\n 1: Silt Strider\n 2: Mage's Guild\n99: Doesn't Matter\n");
	get_input(travel_type, "Type number of travel method you intend to start from", 0, 2);

	//if user input a 99 for city, find all fastest paths, print and write to .txt file
	if (from == 99 || to == 99) find_all(cv);

	//otherwise get fastest path for user
	else find_one(cv, from, to, travel_type);

	return 0;
}
