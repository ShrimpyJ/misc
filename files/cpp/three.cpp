#include <iostream>

using namespace std;

int main()
{
	int ans = 35;
	int c1 = 2, c2 = 4, c3 = 6;
	int x, y, z;
	for (int i = 0; i < ans; i++){
		x = i;
		for (int j = 0; j < ans; j++){
			y = j;
			for (int k = 0; k < ans; k++){
				z = k;
				if ((x*c1 + y*c2 + z*c3) == ans){
					cout << x << "  " << y << "  " << z << endl;
				}
			}
		}
	}

	return 0;
}
