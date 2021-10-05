#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

int main(){
	srand(time(0));
	std::vector<int> bday;
	int r;
	int sentinel = 0;
	int bigCount = 0;
	int count = 0;
	while (count < 100){
		count = 0;
		while (sentinel == 0){
			r = rand() % 365 + 1;
			bday.push_back(r);
			for (int i = 0; i < count - 1; ++i){
				if (bday[count] == bday[i]){
					sentinel = 1;
					break;
				}
			}
			count++;
		}
		bday.clear();
		bigCount++;
		sentinel = 0;
	}
	std::cout << '\n';
	std::cout << "Two matching birthdays found after " << count << " people.\n";
	std::cout << "It took " << bigCount << " loops to get this result.\n";
	return 0;
}
