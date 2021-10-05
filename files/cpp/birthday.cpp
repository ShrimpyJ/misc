#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

int main(){
	srand(time(0));
	int count = 0;
	std::vector<int> bday;
	int r;
	int sentinel = 0;
	while (sentinel == 0){
		r = rand() % 365 + 1;
		bday.push_back(r);
		std::cout << bday[count] << " ";
		for (int i = 0; i < count - 1; ++i){
			if (bday[count] == bday[i]){
				std::cout << '\n' << bday[i] << " at " << i << " and " << bday[count] << " at " << count;
				sentinel = 1;
				break;
			}
		}
		count++;
	}
	std::cout << '\n';
	std::cout << "Two matching birthdays found after " << count << " people.\n";
	return 0;
}
