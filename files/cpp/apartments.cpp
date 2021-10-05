#include <iostream>
#include <string>
#include <iomanip>

struct City
{
	double cost;
	double size;
	double average;
};

int main()
{
	City city[255][255];
	int i = 0;
	char ans;
	char ans2;
	std::string cityName[255];
	do{
		int j = 0;
		std::cout << "Enter city name: ";
		std::getline (std::cin, cityName[i]);
		do{
			std::cout << "Enter apartment price: ";
			std::cin >> city[i][j].cost;
			std::cout << "Enter size (in square feet): ";
			std::cin >> city[i][j].size;
			++j;
			std::cout << "Enter another apartment (y/n)?\n";
			std::cin >> ans;
		}while (ans != 'n' && ans != 'N');
		int num = j;
	
		double bigAverage = 0;
		for (j = 0; j < num; ++j){
			city[i][j].average = city[i][j].cost / city[i][j].size;
			std::cout << std::fixed << std::setprecision(2) << 
			          "Price for apt. " << j+1 << ": $"
				  << city[i][j].average << " per sq. ft.\n";
			bigAverage += city[i][j].average;
		}
	
		bigAverage = bigAverage / num;
	
		std::cout << "\n\nTotal Average for " << cityName[i] << ": $" 
		          << std::fixed << std::setprecision(2) << bigAverage << " per sq. ft.\n";
		std::cout << "Enter another city (y/n)?\n";
		std::cin >> ans2;
		std::cin.ignore();
		++i;
	}while (ans2 != 'n' && ans2 != 'N');

	return 0;
}
