#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
	int i = 0;
	for (int z = 1; ; z++){
		for (int x = 1; x <= z; x++){
			for (int y = x; y <= z; y++){
				if (x*x + y*y == z*z){
					cout << x << " " << y << " " << z << endl;
					if (++i == 100) goto done;
				}
			}
		}
	}
	done:

	return 0;
}
