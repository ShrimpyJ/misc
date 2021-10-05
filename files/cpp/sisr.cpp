#include <iostream>
#include <cmath>
#include <vector>

float Q_rsqrt(float number)
{
	return 1 / sqrt(number);
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
