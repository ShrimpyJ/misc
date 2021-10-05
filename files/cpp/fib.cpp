#include <iostream>

int main(){
	int x, y, z;

	while (true){
		x = 0;
		y = 1;
		do{
			std::cout << x << '\n';

			z = x + y;
			x = y;
			y = z;
		}while (x < 255);
	}
	return 0;
}
