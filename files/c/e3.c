#include <stdio.h>

int largest_prime_factor(long num)
{
	long i = 0;
	while (num != 1 && i < num){
		i++;
		if (num % i == 0) num = num / i;
	}

	return num;
}

int main()
{
	long num = 200;
	long arr[num];
	long ans;
	int i;

	for (i = 0; i < num; i++){
		ans = largest_prime_factor(i);
		arr[i] = ans;
	}
	for (i = 0; i < num; i++){
		printf("%ld\n", arr[i]);
	}

	return 0;
}
