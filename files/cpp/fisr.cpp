#include <iostream>
#include <cmath>
#include <vector>

float Q_rsqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long*) &y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*) &i;
	y = y * (threehalfs - (x2 * y * y));

	return y;
}

int main()
{
	std::vector<float> v;
	float ans = 0.0;
	for (int i = 0; i < 10000000; i++){
		float n = i + 0.264;
		Q_rsqrt(n);
		//ans += n;
		v.push_back(n);
		//printf("%f\n", n);
	}
	for (int i = 0; i < v.size(); i++){
		ans += v[i];
	}
	printf("%f", ans);

	return 0;
}
