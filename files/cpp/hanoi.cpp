#include <iostream>
#include <iomanip>
using namespace std;

void print(int a[3][8]);
void checkValid(int a[3][8], int topLeft, int topMid, int topRight);
void leftTower(int a[3][8], int topLeft, int topMid, int topRight);
void midTower(int a[3][8], int topLeft, int topMid, int topRight);
void rightTower(int a[3][8], int topLeft, int topMid, int topRight);

int main(){
	int topLeft = 0;
	int topMid = 7;
	int topRight = 7;
	int a[3][8] = {{1,2,3,4,5,6,7,8},
				   {0,0,0,0,0,0,0,0},
				   {0,0,0,0,0,0,0,0},
	};
	print (a);
	checkValid(a, topLeft,topMid, topRight);
	return 0;
}

void print(int a[3][8]){
	for (int i = 0; i < 1; i++){
		for (int j = 0; j < 8; j++){
			cout << a[i][j] << "\t" << a[i+1][j] << "\t" << a[i+2][j]<< endl;
		}
	}
	cin.get();
}


void checkValid(int a[3][8], int topLeft, int topMid, int topRight){
	if (a[2][0] == 1 && a[2][1] == 2 && a[2][2] == 3 && a[2][3] == 4 &&
		a[2][4] == 5 && a[2][5] == 6 && a[2][6] == 7 && a[2][7] == 8){
			cout << "Victory!" << endl;
			exit(0);
	}
	bool leftValid = false;
	bool midValid = false;
	bool rightValid = false;
	int lValue = 0, mValue = 0, rValue = 0;
	if (a[0][topLeft] == 0){
		leftValid = false;
		lValue = a[0][topLeft];
	}
	else if (a[0][topLeft] % 2 != 0){
		if (a[1][topMid] == 0){
			leftValid = true;
			lValue = a[0][topLeft];
		}
		else if (a[0][topLeft] < a[1][topMid]){
			leftValid = true;
			lValue = a[0][topLeft];
		}
	}
	if (a[0][topLeft] % 2 == 0){
		if (a[2][topRight] == 0){
			leftValid = true;
			lValue = a[0][topLeft]; }
		else if (a[0][topLeft] < a[2][topRight]){
			leftValid = true;
			lValue = a[0][topLeft];
		}
	}
		///////
	if (a[1][topMid] == 0){
		midValid = false;
		mValue = a[1][topMid];
	}
	else if (a[1][topMid] % 2 != 0){
		if (a[2][topRight] == 0){
			midValid = true;
			mValue = a[1][topMid];
			}
		else if (a[1][topMid] < a[2][topRight]){
			midValid = true;
			mValue = a[1][topMid];
		}
	}
	else if (a[1][topMid] % 2 == 0){
		if (a[0][topLeft] == 0){
			midValid = true;
			mValue = a[1][topMid];
			}
		else if (a[1][topMid] < a[0][topLeft]){
			midValid = true;
			mValue = a[1][topMid];
		}
	}
	////////
	if (a[2][topRight] == 0){
		rightValid = false;
		rValue = a[1][topRight];
	}
	else if (a[2][topRight] % 2 != 0){
		if (a[0][topLeft] == 0){
			rightValid = true;
			rValue = a[2][topRight];
			}
		else if (a[2][topRight] < a[0][topLeft]){
			rightValid = true;
			rValue = a[2][topRight];
		}
	}
	if (a[2][topRight] % 2 == 0){
		if (a[1][topMid] == 0){
			rightValid = true;
			rValue = a[2][topRight];
			}
		else if (a[2][topRight] < a[1][topMid]){
			rightValid = true;
			rValue = a[2][topRight];
		}
	}
//	cout << lValue << " " << mValue << " " << rValue << endl;
	if (leftValid == true){
		if (midValid == true && rightValid == true){
			if (lValue > mValue && lValue > rValue){
				leftTower(a, topLeft, topMid, topRight);
			}
		}else if (midValid == true){
			if (lValue > mValue){
				leftTower(a, topLeft, topMid, topRight);
			}
		}else if (rightValid == true){
			if (lValue > rValue){
				leftTower(a, topLeft, topMid, topRight);
			}
		}else leftTower(a, topLeft, topMid, topRight);
	}
	if (midValid == true){
		if (leftValid == true && rightValid == true){
			if (mValue > lValue && mValue > rValue){
				midTower(a, topLeft, topMid, topRight);
			}
		}else if (leftValid == true){
			if (mValue > lValue){
				midTower(a, topLeft, topMid, topRight);
			}
		}else if (rightValid == true){
			if (mValue > rValue){
				midTower(a, topLeft, topMid, topRight);
			}
		}else midTower(a, topLeft, topMid, topRight);
	}
	if (rightValid == true){
		if (leftValid == true && midValid == true){
			if (rValue > lValue && rValue > mValue){
				rightTower(a, topLeft, topMid, topRight);
			}
		}else if (leftValid == true){
			if (rValue > lValue){
				rightTower(a, topLeft, topMid, topRight);
			}
		}else if (midValid == true){
			if (rValue > mValue){
				rightTower(a, topLeft, topMid, topRight);
			}
		}else rightTower(a, topLeft, topMid, topRight);
	}
}

void leftTower(int a[3][8], int topLeft, int topMid, int topRight){
	if (a[0][topLeft] % 2 != 0){
		if (a[1][topMid] == 0){
			a[1][topMid] = a[0][topLeft];
			a[0][topLeft] = 0;
			if (topLeft != 7){
				topLeft += 1;
			}
			print (a);
			checkValid(a, topLeft,topMid, topRight);
			}
		else if (a[0][topLeft] < a[1][topMid]){
			a[1][topMid-1] = a[0][topLeft];
			a[0][topLeft] = 0;
			if (topLeft != 7){
				topLeft += 1;
			}
			topMid -= 1;
			print (a);
			checkValid(a, topLeft,topMid, topRight);
		}
	}
	if (a[0][topLeft] % 2 == 0 && a[0][topLeft] != 0){
		if (a[2][topRight] == 0){
			a[2][topRight] = a[0][topLeft];
			a[0][topLeft] = 0;
			if (topLeft != 7){
				topLeft += 1;
			}
			print (a);
			checkValid(a, topLeft,topMid, topRight);
			}
		else if (a[0][topLeft] < a[2][topRight]){
			a[2][topRight-1] = a[0][topLeft];
			a[0][topLeft] = 0;
			if (topLeft != 7){
				topLeft += 1;
			}
			topRight -= 1;
			print (a);
			checkValid(a, topLeft,topMid, topRight);
		}
	}
}
	///////////////Mid/////////////////
void midTower(int a[3][8], int topLeft, int topMid, int topRight){
	if (a[1][topMid] % 2 != 0){
		if (a[2][topRight] == 0){
			a[2][topRight] = a[1][topMid];
			a[1][topMid] = 0;
			if (topMid != 7){
				topMid += 1;
			}
			print (a);
			checkValid(a, topLeft,topMid, topRight);
			}
		else if (a[1][topMid] < a[2][topRight]){
			a[2][topRight-1] = a[1][topMid];
			a[1][topMid] = 0;
			if (topMid != 7){
				topMid += 1;
			}
			topRight -= 1;
			print (a);
			checkValid(a, topLeft,topMid, topRight);
		}
	}
	if (a[1][topMid] % 2 == 0 && a[1][topMid] != 0){
		if (a[0][topLeft] == 0){
			a[0][topLeft] = a[1][topMid];
			a[1][topMid] = 0;
			if (topMid != 7){
				topMid += 1;
			}
			print (a);
			checkValid(a, topLeft,topMid, topRight);
			}
		else if (a[1][topMid] < a[0][topLeft]){
			a[0][topLeft-1] = a[1][topMid];
			a[1][topMid] = 0;
			if (topMid != 7){
				topMid += 1;
			}
			topLeft -= 1;
			print (a);
			checkValid(a, topLeft,topMid, topRight);
		}
	}
}

	//////////////Right////////////////////
void rightTower(int a[3][8], int topLeft, int topMid, int topRight){
	if (a[2][topRight] % 2 != 0){
		if (a[0][topLeft] == 0){
			a[0][topLeft] = a[2][topRight];
			a[2][topRight] = 0;
			if (topRight != 7){
				topRight += 1;
			}
			print (a);
			checkValid(a, topLeft,topMid, topRight);
			}
		else if (a[2][topRight] < a[0][topLeft]){
			a[0][topLeft-1] = a[2][topRight];
			a[2][topRight] = 0;
			if (topRight != 7){
				topRight += 1;
			}
			topLeft -= 1;
			print (a);
			checkValid(a, topLeft,topMid, topRight);
		}
	}
	if (a[2][topRight] % 2 == 0 && a[2][topRight] != 0){
		if (a[1][topMid] == 0){
			a[1][topMid] = a[2][topRight];
			a[2][topRight] = 0;
			if (topRight != 7){
				topRight += 1;
			}
			print (a);
			checkValid(a, topLeft,topMid, topRight);
			}
		else if (a[2][topRight] < a[1][topMid]){
			a[1][topMid-1] = a[2][topRight];
			a[2][topRight] = 0;
			if (topRight != 7){
				topRight += 1;
			}
			topMid -= 1;
			print (a);
			checkValid(a, topLeft,topMid, topRight);
		}
	}
}
