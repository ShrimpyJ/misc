#include <iostream>
#include <iomanip>
using namespace std;

const int CALORIES = 2600;
const int FAT = 65;
const int SODIUM = 2400;
const int CARBS = 275;
const int FIBER = 25;
const int SUGAR = 40;
const int PROTEIN = 100;

int main(){
	double calories = 0, fat = 0, sodium = 0, carbs = 0, fiber = 0, sugar = 0, protein = 0;
	double servings = 1;
	double caloriesP = 0, fatP = 0, sodiumP = 0, carbsP = 0, fiberP = 0, sugarP = 0, proteinP = 0;
	double score, price;

	cout << "Enter calories: ";
	cin >> calories;
	cout << "Enter fat: ";
	cin >> fat;
	cout << "Enter sodium: ";
	cin >> sodium;
	cout << "Enter carbs: ";
	cin >> carbs;
	cout << "Enter fiber: ";
	cin >> fiber;
	cout << "Enter sugar: ";
	cin >> sugar;
	cout << "Enter protein: ";
	cin >> protein;

	cout << "Enter number of servings: ";
	cin >> servings;

	calories *= servings;
	fat *= servings;
	sodium *= servings;
	carbs *= servings;
	fiber *= servings;
	sugar *= servings;
	protein *= servings;

	caloriesP = (calories / CALORIES) * 100;
	fatP = (fat / FAT) * 100;
		if (fatP > 100){
			int temp = fatP - 100;
			fatP = fatP - (temp * 2);
		}
	sodiumP = (sodium / SODIUM) * 100; 
			int temp = sodiumP - 100;
			sodiumP = sodiumP - (temp * 2);
	carbsP = (carbs / CARBS) * 100;
			int temp2 = carbsP - 100;
			carbsP = carbsP - (temp2 * 2);
	fiberP = (fiber / FIBER) * 100;
	sugarP = (sugar / SUGAR) * 100;
			int temp3 = sugarP - 100;
			sugarP = sugarP - (temp3 * 2);
	proteinP = (protein / PROTEIN) * 100;

	score = (fatP + sodiumP + carbsP + fiberP + sugarP + proteinP) / 6;
	cout << "Health score: " << score << endl;
	cout << "Enter price: ";
	cin >> price;
	if (price == 0){score *= 2;}
	else if (price <= 1){score *= 1.8;}
	else if (price <= 3){score *= 1.7;}
	else if (price <= 5){score *= 1.5;}
	else if (price <= 10){score *= 1.3;}
	else if (price <= 20){score *=1.2;}
	else if (price <= 30){score *=1.1;}
	cout << "Final score: " << score << endl;
	cout.setf(ios::fixed | ios::showpoint);
	cout.precision(2);
	return 0;	
}
