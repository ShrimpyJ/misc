#include <iostream>
#include <iomanip>

using std::cout;

struct People
{
	int time;
	std::string name;
	bool isSafe;
};

void crossToSafe (struct People people[], int i, int j, int& timeElapsed);
void crossBack (struct People people[], int i, int j, int& timeElapsed);

int main()
{
	//initialize each person's: time to cross (in mins)
	//                          name
	//                          bool flag to determine if they are on safe side or not
	People people[4] = {{1, "Hugh", 0},
	                    {2, "Assistant", 0},
			    {5, "Janitor", 0},
			    {10, "Professor", 0}};

	cout << "\n\n\n\nStarting...\n";
	bool victory = 0;       //stays at zero until the solution is found
	int timeLimit = 17;     //all people must be on safe side <= this number
	int timeElapsed = 0;    //total time elapsed in a single attempt
	int count = 0;

	//i and j each represent a person depending on the following key:
		//0 = Hugh
		//1 = Assistant
		//2 = Janitor
		//3 = Professor

	//they can be initialized to any person, though it may take longer
	//for the program to find the solution depending on the starting values
	int i = 1;
	int j = 3;

	//outer loop to reset puzzle and continue until victory condition is met
	while (victory != 1){
		count++;
		//inner loop to brute force solution and continue until timeLimit is exceeded
		while (timeElapsed < timeLimit){
			//shift i and j around if needed
			  //if i and j both point to same person, change j's person
			if (i == j){j++;}
			  //reset i or j if exceeding number of people
			if (i >= 4){i = 0;}
			if (j >= 4){
				j = 0;
				//change i's person only when j's person is 0
				//this ensures every combination of i and j can be hit
				i++;
			}

			//if both people are on unsafe side, have them cross to safe side
			else if (people[i].isSafe == 0 && people[j].isSafe == 0){
				crossToSafe(people,i,j,timeElapsed);
				cout << "\nElapsed time: " << timeElapsed << "\n\n";

				//victory condition (program ends here if met)
				if (people[0].isSafe == 1 && people[1].isSafe == 1 &&
				    people[2].isSafe == 1 && people[3].isSafe == 1 &&
				    timeElapsed <= timeLimit){
					cout << "\nVictory!\nAttempts: " << count << "\n\n\n";
					victory = 1;
				}

				//otherwise the fastest person on safe side crosses back
				else{
					crossBack(people,i,j,timeElapsed);
					cout << "\nElapsed time: " << timeElapsed << "\n\n";
				}
			}
			//always change j's person every loop
			j++;
		}
		if (victory != 1){
			cout << "Time limit reached\nTrying again...\n\n\n\n";
		}
		//increment i for different starting combination next loop
		i++;
		//reset i or j if exceeding number of people
		if (i >= 4){i = 0;}
		if (j >= 4){j = 0;}

		//reset time and place all people back to unsafe side
		timeElapsed = 0;
		for (int k = 0; k < 4; k++){
			people[k].isSafe = 0;
		}
	}
	return 0;
}

void crossToSafe (struct People people[], int i, int j, int& timeElapsed)
{
	int timeAdd;

	//find slower person's time and add to timeElapsed
	if (people[i].time > people[j].time){
		timeAdd = people[i].time;
	}else{
		timeAdd = people[j].time;
	}
	timeElapsed += timeAdd;
	people[i].isSafe = 1;
	people[j].isSafe = 1;
	cout << people[i].name << " and " << people[j].name << " cross to safety";
}

void crossBack (struct People people[], int i, int j, int& timeElapsed)
{
	int timeAdd;
	int smallest = -1;

	//find fastest person on safe side and have them run back; add to timeElapsed
	for (i = 0; i < 4; i++){
		if (people[i].isSafe == 1){
			if (smallest == -1){
				smallest = i;
			}
			else if (people[i].time < people[smallest].time){
				smallest = i;
			}
		}
	}

	timeAdd = people[smallest].time;
	timeElapsed += timeAdd;
	people[smallest].isSafe = 0;
	cout << people[smallest].name << " crosses back";
}
