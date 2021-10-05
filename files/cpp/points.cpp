#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>

const double PI = 3.14159;
const double radius = 1;
const double diameter = radius * 2;

struct Point
{
	double x;
	double y;
};

double getDistance (struct Point p1, struct Point p2);

int main(){
	Point center, p1, p2, p3;
	center.x = 0;
	center.y = 0;
	double angle;
	double d, a1, a2;
	int i, success = 0;
	float avg;

	srand(time(0));

	for (i = 0; i < 353535; ++i){
		angle = rand()*PI*2*radius;
		p1.x = cos(angle);
		p1.y = sin(angle);
		angle = rand()*PI*2*radius;
		p2.x = cos(angle);
		p2.y = sin(angle);
		angle = rand()*PI*2*radius;
		p3.x = cos(angle);
		p3.y = sin(angle);

		p1.x = p1.x * -1;
		p1.y = p1.y * -1;
		p2.x = p2.x * -1;
		p2.y = p2.y * -1;

		d = getDistance(p1,p2);
		angle = (asin(d/diameter)) * 2;
		angle = angle * (180 / PI);

		d = getDistance(p3,p1);
		a1 = (asin(d/diameter)) * 2;
		a1 = a1 * (180 / PI);

		d = getDistance(p3,p2);
		a2 = (asin(d/diameter)) * 2;
		a2 = a2 * (180 / PI);

		if (a1 + a2 <= angle + .002){
			++success;
		//	std::cout << a1 + a2 << '\n' << angle << '\n';
			}
		else if (a1 + a2 < angle){
			std::cout.precision(30);
			std::cout << a1 + a2 << '\n' << angle << '\n';
			std::cout << '\n';
		}
	}

	std::cout.precision(3);
	std::cout << "P1: (" << p1.x << ',' << p1.y << ")\n";
	std::cout << "P2: (" << p2.x << ',' << p2.y << ")\n";
	std::cout << "P3: (" << p3.x << ',' << p3.y << ")\n";

	avg = (success / (double)i) * 100;
	std:: cout << success << '\n' << i << '\n';
	std::cout << "Average success rate: " << std::fixed << std::setprecision(2) << avg << "%\n";

	return 0;
}

double getDistance (struct Point p1, struct Point p2)
{
	return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}
