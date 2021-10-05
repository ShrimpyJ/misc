#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char** argv)
{
	int sum = 0;
	for (int i = 0; i <= 19; i++){
		sum += i + 4*i;
	}
	printf("%d\n",sum);
	return 0;
}
