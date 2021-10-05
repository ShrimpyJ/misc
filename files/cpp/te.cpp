#include <iostream>

using namespace std;

int main()
{
	int il = 0, jl = 0, kl = 0, ml = 0, nl = 0;
	for (int i = 0; i < 10; i++){
		il++;
		for (int j = 0; j <= i; j++){
			jl++;
			for (int k = 0; k <= j; k++){
				kl++;
				for (int m = 0; m <= k; m++){
					ml++;
					for (int n = 0; n <= m; n++){
						nl++;
					}
				}
			}
		}
	}

	cout << "il: " << il << "\njl: " << jl << "\nkl: " << kl << "\nml: " << ml << "\nnl: " << nl <<  endl;

	return 0;
}
