#include <iostream>
#include <map>

using namespace std;

int main()
{
	int n = 55;
	map<int,pair<int,int> > m;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			int x = i+j*n;
			m.insert(pair<int,pair<int,int> >(x, pair<int,int>(i,j)));
		}
	}

	cout << "n*n: " << n*n << "   m.size(): " << m.size() << endl;
	map<int,pair<int,int> >::iterator itr;
	for (itr = m.begin(); itr != m.end(); itr++){
		int a, b;
		
	}
	return 0;
}
