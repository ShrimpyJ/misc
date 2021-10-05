#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

void printInfo(string array[], int n, string hitLevel, string moveType, string properties);

int main(){
	string hitLevel, moveType, properties;
    string moveName;
    int selection;

	cout << "\tWelcome to Tekken 7 King Info!\n\n";
    cout << "   Main Menu:\n\tPress 1 for frame data\n\tPress 2 for punishes\n\tPress 3 for setups\n\tPress 0 to quit\n\n";
    cin >> selection;
    if (selection = 1){
       cout << "Type move for info (q to quit): ";
       cin.get();
    getline(cin, moveName);
	while (moveName != "q"){
		if (moveName == "1" || moveName == "f1" || moveName == "f 1" || moveName == "f+1"){
            string array[5] = {"7", "10", "+1", "+8", "+8"};
			hitLevel = "h";
            moveType = "attack";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
		}else if (moveName == "2"){
            string array[5] = {"10", "10", "0", "+9", "+9"};
			hitLevel = "h";
            moveType = "attack";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "3"){
            string array[5] = {"10", "15", "-9", "+2", "+2"};
			hitLevel = "m";
            moveType = "attack";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
		}else if (moveName == "4"){
            string array[5] = {"15", "12", "-9", "-1", "+7"};
			hitLevel = "h";
            moveType = "attack";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
		}else if (moveName == "1,1" || moveName == "1, 1" || moveName == "11" || moveName == "1 1"){
            string array[5] = {"7, 8", "10", "-4", "+7", "+7"};
			hitLevel = "h, h";
            moveType = "string";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
		}else if (moveName == "1,2" || moveName ==  "1, 2" || moveName ==  "12" || moveName ==  "1 2"){
            string array[5] = {"7, 8", "10", "-9", "+2", "+2"};
			hitLevel = "h, m";
            moveType = "string";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
		}else if (moveName == "1,1,3" || moveName ==  "1, 1, 3" || moveName ==  "113" || moveName ==  "1 1 3"){
            string array[5] = {"7, 8, 22", "10", "-9", "KND", "KND"};
			hitLevel = "h, h, m";
            moveType = "string";
            properties = "Knockdown on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
		}else if (moveName == "1,2,1" || moveName ==  "1, 2, 1" || moveName ==  "121" || moveName ==  "1 2 1"){
            string array[5] = {"7, 8, 20", "10", "-14", "KND", "STUN"};
			hitLevel = "h, m, m";
            moveType = "string";
            properties = "Knockdown on Hit, stun on CH";
            printInfo(array, 5, hitLevel, moveType, properties);
		}else if (moveName == "1,3" || moveName ==  "1, 3" || moveName ==  "13" || moveName ==  "1 3"){
            string array[5] = {"7, 14", "10", "-7", "+1", "+9"};
			hitLevel = "h, h";
            moveType = "string";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
		}else if (moveName == "1,3,2" || moveName ==  "1, 3, 2" || moveName ==  "132" || moveName == "1 3 2"){
            string array[5] = {"7, 14, 20", "10", "-12", "KND", "KND"};
			hitLevel = "m";
            moveType = "attack";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "2,1" || moveName == "2, 1" || moveName == "21" || moveName == "2 1"){
            string array[5] = {"10, 8", "10", "-2", "+6", "+6"};
			hitLevel = "h, h";
            moveType = "string";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "2,1,3" || moveName == "2, 1, 3" || moveName == "213" || moveName == "2 1 3"){
            string array[5] = {"10, 8, 24", "10", "-9", "KND", "KND"};
			hitLevel = "h,h,h";
            moveType = "string";
            properties = "Knockdown on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "2,1,4" || moveName == "2, 1, 4" || moveName == "214" || moveName == "2 1 4"){
            string array[5] = {"10, 8, 14", "10", "-12", "+3s", "+3s"};
			hitLevel = "h, h, l";
            moveType = "string";
            properties = "Forces opponent to crouch on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "3,1" || moveName == "3, 1" || moveName == "31" || moveName == "3 1"){
            string array[5] = {"10, 8", "15", "-2", "+7", "+7"};
			hitLevel = "m, h";
            moveType = "string";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "3,1,2" || moveName == "3, 1, 2" || moveName == "312" || moveName == "3 1 2"){
            string array[5] = {"10, 8, 24", "15", "-12", "KND", "KND"};
			hitLevel = "m, h, m";
            moveType = "string";
            properties = "Knockdown on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "3,1,4" || moveName == "3, 1, 4" || moveName == "314" || moveName == "3 1 4"){
            string array[5] = {"10, 8, 27", "15", "-9", "KND", "KND"};
			hitLevel = "m, h, h";
            moveType = "string";
            properties = "Knockdown on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "4,1" || moveName == "4, 1" || moveName == "41" || moveName == "4 1"){
            string array[5] = {"15, 12", "12", "-6", "+8", "+8"};
			hitLevel = "h,h";
            moveType = "string";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "4,3" || moveName == "4, 3" || moveName == "43" || moveName == "4 3"){
            string array[5] = {"15, 20", "12", "-12", "KND", "KND"};
			hitLevel = "h, m";
            moveType = "string";
            properties = "Knockdown on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "4,4" || moveName == "4, 4" || moveName == "44" || moveName == "4 4"){
            string array[5] = {"15, 25", "12", "+3", "KND", "KND"};
			hitLevel = "h, m (TJ)";
            moveType = "string";
            properties = "Screw on Hit and CH     2nd hit low crushes";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "1+2" || moveName == "1 + 2" || moveName == "1+ 2" || moveName == "1 +2"){
            string array[5] = {"25", "21", "-14", "KND", "TUKD"};
			hitLevel = "m";
            moveType = "attack";
            properties = "Power Crush     Knockdown on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "3+4" || moveName == "3 + 4" || moveName == "3+ 4" || moveName == "3 +4"){
            string array[5] = {"25", "25", "-14", "CS", "CS"};
			hitLevel = "h (TJ)";
            moveType = "attack";
            properties = "Low crushes     Crumples on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "f+2" || moveName == "f2" || moveName == "f 2" || moveName == "f+ 2"){
            string array[5] = {"16", "19", "-8", "+3", "+8"};
			hitLevel = "h";
            moveType = "attack";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "f+2,4" || moveName == "f+2, 4" || moveName == "f+24" || moveName == "f+2 4" ||
                  moveName == "f2,4" || moveName == "f2, 4" || moveName == "f24" || moveName == "f2 4"){
            string array[5] = {"16, 24", "19", "-7", "KND", "KND"};
			hitLevel = "h, m";
            moveType = "string";
            properties = "Knockdown on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "f+3" || moveName == "f3" || moveName == "f 3" || moveName == "f+ 3"){
            string array[5] = {"11", "20", "-6", "+2", "+2"};
			hitLevel = "m";
            moveType = "attack";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "f+3,2" || moveName == "f+3, 2" || moveName == "f+32" || moveName == "f+3 2" ||
                  moveName == "f3,2" || moveName == "f3, 2" || moveName == "f32" || moveName == "f3 2"){
            string array[5] = {"11, 20", "20", "-9", "KND", "KND"};
			hitLevel = "m, h";
            moveType = "string";
            properties = "Screw on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "f+4" || moveName == "f4" || moveName == "f+ 4" || moveName == "f +4"){
            string array[5] = {"16", "14", "-7", "+4", "+4"};
			hitLevel = "h";
            moveType = "attack";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "f+4,4" || moveName == "f+4, 4" || moveName == "f+44" || moveName == "f+4 4" ||
                  moveName == "f4,4" || moveName == "f4, 4" || moveName == "f44" || moveName == "f4 4"){
            string array[5] = {"16, 14", "14", "-11", "0", "Launch"};
			hitLevel = "h, h";
            moveType = "string";
            properties = "Launch on CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "f+4,4,3" || moveName == "f+4, 4, 3" || moveName == "f+443" || moveName == "f+4 4 3" ||
                  moveName == "f4,4,3" || moveName == "f4, 4 3" || moveName == "f443" || moveName == "f4 4 3"){
            string array[5] = {"16, 14, 20", "14", "-5", "KND", "KND"};
			hitLevel = "h, h, h";
            moveType = "string";
            properties = "Knockdown on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "f+4,d+4" || moveName == "f+4, d+4" || moveName == "f+4d+4" || moveName == "f+4 d+4" ||
                  moveName == "f4,d4" || moveName == "f4, d4" || moveName == "f4d4" || moveName == "f4 d4"){
            string array[5] = {"16, 12", "14", "-12", "+3s", "+3s"};
			hitLevel = "h, l";
            moveType = "string";
            properties = "Forces opponent to crouch on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "f+1+2" || moveName == "f + 1 + 2" || moveName == "f 1+2" || moveName == "f1+2"){
            string array[5] = {"20", "17", "-9", "KND", "KND"};
			hitLevel = "h";
            moveType = "attack";
            properties = "Screw on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "d/f+1" || moveName == "d/f1" || moveName == "df+1" || moveName == "df1"){
            string array[5] = {"13", "13", "-2", "+7", "+7"};
			hitLevel = "m";
            moveType = "attack";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "df1,4" || moveName == "df1, 4" || moveName == "df14" || moveName == "df1 4"){ 
            string array[5] = {"13, 23", "13", "-7", "KND", "KND"};
			hitLevel = "m, h";
            moveType = "string";
            properties = "Knockdown on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "d/f+2" || moveName == "d/f2" || moveName == "df+2" || moveName == "df2"){
            string array[5] = {"14", "15", "-12", "Launch", "Launch"};
			hitLevel = "m";
            moveType = "attack";
            properties = "Launch on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "d/f+3" || moveName == "d/f3" || moveName == "df+3" || moveName == "df3"){
            string array[5] = {"16", "17", "-6", "+5", "+10"};
			hitLevel = "m";
            moveType = "attack";
            properties = "Throws and knocks down if connects close";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "d/f+4" || moveName == "d/f4" || moveName == "df+4" || moveName == "df4"){
            string array[5] = {"14", "12", "-9", "+2", "+2"};
			hitLevel = "m";
            moveType = "attack";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "d+1" || moveName == "d1" || moveName == "d + 1" || moveName == "d 1"){
            string array[5] = {"18", "18", "0", "+7", "KND"};
			hitLevel = "m";
            moveType = "attack";
            properties = "Knockdown on CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "d+2" || moveName == "d + 2" || moveName == "d2" || moveName == "d 2"){
            string array[5] = {"17", "18", "-13", "0", "+13"};
            hitLevel = "l (TC)";
            moveType = "attack";
            properties = "Crouch and high crush";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "d+3" || moveName == "d + 3" || moveName == "d3" || moveName == "d 3"){
            string array[5] = {"13", "17", "-14", "-3", "0s"};
            hitLevel = "l";
            moveType = "attack";
            properties = "Forces opponent to crouch on CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "d3 4" || moveName == "d3, 4" || moveName == "d3,4" || moveName == "d34"){
            string array[5] = {"13, 18", "17", "-11", "+5", "+23(KND)"};
            hitLevel = "l, m";
            moveType = "string";
            properties = "Knockdown on CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "d+4" || moveName == "d + 4" || moveName == "d4" || moveName == "d 4"){
            string array[5] = {"12", "15", "-15", "-9", "-4"};
            hitLevel = "l";
            moveType = "attack";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "d4 1" || moveName == "d4,1" || moveName == "d4, 1" || moveName == "d41"){
            string array[5] = {"12, 8", "15", "-11", "+5", "+5"};
            hitLevel = "l, h";
            moveType = "string";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "d4,1,3" || moveName == "d4, 1, 3" || moveName == "d413" || moveName == "d4 1 3"){
            string array[5] = {"12, 8, 21", "15", "-16", "KND", "KND"};
            hitLevel = "l, h, h";
            moveType = "string";
            properties = "Knockdown on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "d4 4" || moveName == "d4, 4" || moveName == "d4,4" || moveName == "d44"){
            string array[5] = {"12, 23", "15", "-15", "KND", "KND"};
            hitLevel = "l, h";
            moveType = "string";
            properties = "Knockdown on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "db4" || moveName == "db 4" || moveName == "d/b4" || moveName == "d/b+4"){
            string array[5] = {"7", "12s", "-13", "-2", "-2"};
            hitLevel = "l (TC)";
            moveType = "attack";
            properties = "High crush     Forces crouch";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "db1" || moveName == "db 1" || moveName == "d/b1" || moveName == "d/b+1"){
            string array[5] = {"5", "10s", "-5", "+6", "+6"};
            hitLevel = "Special m (TC)";
            moveType = "attack";
            properties = "High crush     Forces crouch";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "db2" || moveName == "db 2" || moveName == "d/b2" || moveName == "d/b+2"){
            string array[5] = {"12", "14", "-7", "+4", "+4"};
            hitLevel = "m";
            moveType = "attack";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "db2, 1" || moveName == "db2,1" || moveName == "db2 1" || moveName == "db21"){
            string array[5] = {"12, 10", "14", "-10", "+1", "+3"};
            hitLevel = "m, m";
            moveType = "string";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "db2, 1, 2" || moveName == "db2,1,2" || moveName == "db2 1 2" || moveName == "db212"){
            string array[5] = {"12, 10, 20", "14", "-14", "STUN", "STUN"};
            hitLevel = "m, m, m";
            moveType = "string";
            properties = "Stuns on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "db3" || moveName == "db 3" || moveName == "d/b3" || moveName == "d/b+3"){
            string array[5] = {"21", "27", "-26", "KND", "Throw(KND)"};
            hitLevel = "l (TC)";
            moveType = "attack";
            properties = "Forces crouch and crushes highs     Knockdown on Hit     Throw and knockdown on CH     14 damage and no KND if far (KND on CH)";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "fc1" || moveName == "fc 1" || moveName == "fc+1" || moveName == "crouch 1"){
            string array[5] = {"5", "10s", "-5", "+6", "+6"};
            hitLevel = "Special m (TC)";
            moveType = "attack";
            properties = "High crush     Forces crouch";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "fc2" || moveName == "fc 2" || moveName == "fc+2" || moveName == "crouch 2"){
            string array[5] = {"8", "11s", "-4", "+7", "+7"};
            hitLevel = "Special m (TC)";
            moveType = "attack";
            properties = "High crush     Forces crouch";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "fc3" || moveName == "fc 3" || moveName == "fc+3" || moveName == "crouch 3"){
            string array[5] = {"12", "16", "-17", "-3", "-3"};
            hitLevel = "l (TC)";
            moveType = "attack";
            properties = "High crush     Forces crouch";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "fc4" || moveName == "fc 4" || moveName == "fc+4" || moveName == "crouch 4"){
            string array[5] = {"10", "12s", "-15", "-4", "-4"};
            hitLevel = "l (TC)";
            moveType = "attack";
            properties = "High crush     Forces crouch";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "b1" || moveName == "b 1" || moveName == "b+1" || moveName == "b + 1"){
            string array[5] = {"14", "17", "-10", "+1", "+1"};
            hitLevel = "m";
            moveType = "attack";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "b1,2" || moveName == "b1, 2" || moveName == "b12" || moveName == "b1 2"){
            string array[5] = {"14, 18", "17", "-13", "+9k", "KND"};
            hitLevel = "m, m";
            moveType = "string";
            properties = "Hit confirmable     Screw if 2nd hit lands on airborne opponent     Knockdown on CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "b2" || moveName == "b 2" || moveName == "b+2" || moveName == "b + 2"){
            string array[5] = {"14", "15s", "-3", "+8", "+8"};
            hitLevel = "m";
            moveType = "attack";
            properties = "Force crouch on self";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "b2,1" || moveName == "b2, 1" || moveName == "b2 1" || moveName == "b21"){
            string array[5] = {"14, 11", "15", "-5", "+6", "+6"};
            hitLevel = "m, h";
            moveType = "string";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "b2,1,3" || moveName == "b2, 1, 3" || moveName == "b2 1 3" || moveName == "b213"){
            string array[5] = {"14, 11, 24", "cs15", "-26", "KND", "Throw(KND)"};
            hitLevel = "m, h, l";
            moveType = "string";
            properties = "High crush on 3rd hit     KND on Hit and Throw on CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "b3" || moveName == "b+3" || moveName == "b 3" || moveName == "b + 3"){
            string array[5] = {"17", "14", "-9", "+11kg", "+11kg"};
            hitLevel = "h";
            moveType = "attack";
            properties = "Homing Tail Spin     Screw if opponent in air";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "b4" || moveName == "b 4" || moveName == "b+4" || moveName == "b + 4"){
            string array[5] = {"15", "15", "-4", "7", "7"};
            hitLevel = "m";
            moveType = "attack";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "b4,2" || moveName == "b4, 2" || moveName == "b42" || moveName == "b4 2"){
            string array[5] = {"15, 15", "15", "-7", "+4s", "+5s"};
            hitLevel = "m, m";
            moveType = "string";
            properties = "Forces opponent to crouch on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "b4,2,1" || moveName == "b4, 2, 1" || moveName == "b421" || moveName == "b4 2 1"){
            string array[5] = {"15, 15, 17", "15", "+1", "+5", "+5"};
            hitLevel = "m, m, h";
            moveType = "string";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "b4,3" || moveName == "b4, 3" || moveName == "b43" || moveName == "b4 3"){
            string array[5] = {"15, 22", "15", "-9", "KND", "KND"};
            hitLevel = "m, h";
            moveType = "string";
            properties = "Screw and knockdown on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "b1+2" || moveName == "b 1+2" || moveName == "b+1+2" || moveName == "b + 1 + 2"){
            string array[5] = {"26", "22", "+6", "KND", "KND"};
            hitLevel = "m";
            moveType = "attack";
            properties = "Knockdown on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "b3+4" || moveName == "b 3+4" || moveName == "b+3+4" || moveName == "b + 3 + 4"){
            string array[5] = {"22", "28", "-2", "KND", "KND"};
            hitLevel = "h";
            moveType = "attack";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "b2+3" || moveName == "b 2+3" || moveName == "b+2+3" || moveName == "b + 2 + 3"){
            string array[5] = {"60", "63", "KND", "KND", "KND"};
            hitLevel = "Unblockable";
            moveType = "attack";
            properties = "Knockdown if connects";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "ub2" || moveName == "ub 2" || moveName == "ub+2" || moveName == "ub/2"){
            string array[5] = {"18", "20", "-5", "+9", "CS"};
            hitLevel = "h";
            moveType = "attack";
            properties = "Crumples opponent on CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "uf1" || moveName == "uf 1" || moveName == "uf+1" || moveName == "uf/1"){
            string array[5] = {"20", "15", "-9", "KND", "KND"};
            hitLevel = "h";
            moveType = "attack";
            properties = "Knockdown on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "u2" || moveName == "uf2" || moveName == "u 2" || moveName == "u/f2" || moveName == "u/f 2"){
            string array[5] = {"20", "30 js9", "-5", "KND", "KND"};
            hitLevel = "m (TJ)";
            moveType = "attack";
            properties = "Low crush from frame 9     Knockdown on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "uf3" || moveName == "uf 3" || moveName == "u/f3" || moveName == "u/f 3"){
            string array[5] = {"16", "17", "-7", "KND", "KND"};
            hitLevel = "m (TJ)";
            moveType = "attack";
            properties = "Low crush     Knockdown on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "ub4" || moveName == "ub 4" || moveName == "u/b4" || moveName == "u/b 4" ||
                  moveName == "u4" || moveName == "u 4" || moveName == "u+4" || moveName == "u + 4" ||
                  moveName == "uf4" || moveName == "uf 4" || moveName == "u/f4" || moveName == "u/f 4"){
            string array[5] = {"21", "22 js9", "-17", "KND", "KND"};
            hitLevel = "m";
            moveType = "attack";
            properties = "Low crush from frame 9     Knockdown on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "ff2" || moveName == "f,f2" || moveName == "f, f2" || moveName == "f f2"){
            string array[5] = {"20", "15", "-12", "KND", "KND"};
            hitLevel = "m";
            moveType = "attack";
            properties = "Knockdown on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "ff3" || moveName == "f,f3" || moveName == "f, f3" || moveName == "f f3"){
            string array[5] = {"35", "21", "+3", "KND", "KND"};
            hitLevel = "h";
            moveType = "attack";
            properties = "Homing Screw     Knockdown on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "ff4" || moveName == "f,f4" || moveName == "f, f4" || moveName == "f f4"){
            string array[5] = {"21", "26as", "-1", "+3s", "KND"};
            hitLevel = "m";
            moveType = "attack";
            properties = "Forces crouch     Forces opponent to crouch on Hit     Knockdown on CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "fff2" || moveName == "f,f,f2" || moveName == "f, f, f 2" || moveName == "wr2"){
            string array[5] = {"25", "15", "+6", "KND", "Launch"};
            hitLevel = "m";
            moveType = "attack";
            properties = "Knockdown on Hit and Launch on CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "qcf1" || moveName == "qcf 1" || moveName == "qcf+1" || moveName == "cd1"){
            string array[5] = {"20", "15", "-3", "CS", "CS"};
            hitLevel = "h";
            moveType = "attack";
            properties = "Crumples opponent on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "qcf2" || moveName == "qcf 2" || moveName == "qcf+2" || moveName == "cd2"){
            string array[5] = {"25", "18", "-14", "Launch", "Launch"};
            hitLevel = "m";
            moveType = "attack";
            properties = "Launch on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "qcf3" || moveName == "qcf 3" || moveName == "qcf+3" || moveName == "cd3"){
            string array[5] = {"17", "17s", "-15", "-6", "Throw(KND)"};
            hitLevel = "l (TC)";
            moveType = "attack";
            properties = "High crush     Throw and knockdown on CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "qcf4" || moveName == "qcf 4" || moveName == "qcf+4" || moveName == "cd4"){
            string array[5] = {"23", "17", "-10", "Throw(KND)", "Throw(KND)"};
            hitLevel = "m";
            moveType = "attack";
            properties = "Throw and knockdown on Hit and CH     Extend with 1,3,4,2 or 2,4,3,1";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "qcf1+2" || moveName == "qcf 1+2" || moveName == "qcf+1+2" || moveName == "cd1+2"){
            string array[5] = {"28", "12", "-15", "KND", "KND"};
            hitLevel = "m";
            moveType = "attack";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "qcb2" || moveName == "qcb 2" || moveName == "qcb+2" || moveName == "qcb + 2"){
            string array[5] = {"23", "26", "-15", "Launch", "Launch"};
            hitLevel = "m";
            moveType = "attack";
            properties = "Launch on Hit and CH     Evasive backswing";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "ws1" || moveName == "ws 1" || moveName == "ws+1" || moveName == "ws + 1"){
            string array[5] = {"12", "12", "-3", "+4", "+4"};
            hitLevel = "m";
            moveType = "while standing attack";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "ws1,2" || moveName == "ws1, 2" || moveName == "ws12" || moveName == "ws1 2"){
            string array[5] = {"12, 18", "12", "-7", "+10kg", "KND"};
            hitLevel = "m, h";
            moveType = "While Standing attack";
            properties = "Screw on airborne opponent     Knockdown on CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "ws1,3" || moveName == "ws1, 3" || moveName == "ws13" || moveName == "ws1 3"){
            string array[5] = {"12, 20", "12", "-13", "KND", "KND"};
            hitLevel = "m, ";
            moveType = "While Standing attack";
            properties = "Wall bounce";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "ws2" || moveName == "ws 2" || moveName == "ws+2" || moveName == "ws + 2"){
            string array[5] = {"15", "15", "-12", "Launch", "Launch"};
            hitLevel = "m";
            moveType = "While Standing attack";
            properties = "Launch on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "ws3" || moveName == "ws 3" || moveName == "ws+3" || moveName == "ws + 3"){
            string array[5] = {"21", "16", "-9", "KND", "KND"};
            hitLevel = "m";
            moveType = "While Standing attack";
            properties = "Knockdown on Hit and CH     Wall bounce";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "ws4" || moveName == "ws 4" || moveName == "ws+4" || moveName == "ws + 4"){
            string array[5] = {"15", "11", "-5", "+6", "+6"};
            hitLevel = "m";
            moveType = "While Standing attack";
            properties = "None";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else if (moveName == "ws1+2" || moveName == "ws 1+2" || moveName == "ws+1+2" || moveName == "ws + 1 + 2"){
            string array[5] = {"28", "12", "-14", "KND", "KND"};
            hitLevel = "m";
            moveType = "While Standing attack";
            properties = "Knockdown on Hit and CH";
            printInfo(array, 5, hitLevel, moveType, properties);
        }else{cout << "Invalid entry\n\n";}

		cout << "Enter another move (q to quit): ";
        getline(cin, moveName);
    }
	}
	return 0;
}

void printInfo(string array[], int n, string hitLevel, string moveType, string properties){
	string sArray[5] = {"Damage", "Impact Frame", "On Block", "On Hit", "On CH"};
    string sArray2[5] = {"------", "------------", "--------", "------", "-----"};
    cout << endl << endl << "------------------------------------------------------------------------------";
    cout << endl << endl << "Move type: " << hitLevel << " " << moveType << endl << endl;
    for (int i = 0; i < 5; i++){
         cout << setw(14) << sArray[i];
    }
    cout << endl;
    for (int i = 0; i < 5; i++){
        cout << setw(14) << sArray2[i];
    }
    cout << endl;
	for (int i = 0; i < 5; i++){
		cout << setw(14) << array[i];
	}
    cout << endl << endl << "Special properties:\n" << "\t" << properties;
	cout << endl << endl << "------------------------------------------------------------------------------";
    cout << endl << endl;
}
