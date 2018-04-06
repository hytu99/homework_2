#include<iostream>
#include<math.h>
#include<random>
#include<ctime>
#include<string>
#include"calc.h"
#define epsilon 1e-8
using namespace std;

int randomInt(int min, int max) {

	//default_random_engine e((unsigned)time(NULL));
	//uniform_int_distribution<int> u(min, max);
	//return u(e);
	return rand() % (max - min + 1) + min;
}

string newExp(int oprNum, int oprType, int min, int max) {

	if (!min) {
		min++;
	}
	string exp;
	const char opr[5] = { '+','-','*','/','^' };
	int oprMax;
	switch (oprType) {
	case 0:oprMax = 1; break;
	case 1:oprMax = 3; break;
	case 2:oprMax = 4; break;
	}
	int curOpr, lastOpr;
	int	leftVal, rightVal, tempVal;
	int powerNum = 2;
	
	leftVal = randomInt(min, max);
	if (leftVal > 10 && oprMax == 4)
		oprMax = 3;
	curOpr = randomInt(0, oprMax);
	oprNum--;
	switch (curOpr) {
	case 0: //leftVal = randomInt(min, max);
		rightVal = randomInt(min, max);
		break;
	case 1: //leftVal = randomInt(min, max);
		rightVal = randomInt(min, leftVal);
		break;
	case 2: //leftVal = randomInt(min, max);
		rightVal = randomInt(min, max);
		break;
	case 3: //leftVal = randomInt(min, max);
		rightVal = randomInt(min, max);
		break;
	case 4:rightVal = randomInt(2, 3);
		//leftVal = randomInt(min, max);
		powerNum--;
		break;
	}

	exp = to_string(leftVal) + opr[curOpr] + to_string(rightVal);
	tempVal = operate(leftVal, opr[curOpr], rightVal);

	while (oprNum) {
		lastOpr = curOpr;
		if ((!powerNum || tempVal > 10) && oprMax == 4)
			oprMax = 3;
		curOpr = randomInt(0, oprMax);
		oprNum--;
		if (curOpr == 4) {
			powerNum--;
			leftVal = tempVal;
			rightVal = randomInt(2, 3);
			exp = "(" + exp + ")" + opr[curOpr] + to_string(rightVal);				
			tempVal = operate(leftVal, opr[curOpr], rightVal);
		}
		else {
			if (curOpr == 3&&tempVal == 0 || curOpr == 1&&tempVal >= max || randomInt(0,1)&&(!(curOpr == 1 && tempVal == 0))) {
				leftVal = tempVal;
				curOpr == 1 ? rightVal = randomInt(min, leftVal < max? leftVal : max) : rightVal = randomInt(min, max);
				if (curOpr >= 2 && lastOpr <= 1) {
					exp = "(" + exp + ")" + opr[curOpr] + to_string(rightVal);
					tempVal = operate(leftVal, opr[curOpr], rightVal);
				}
				else {
					exp = exp + opr[curOpr] + to_string(rightVal);
					tempVal = operate(leftVal, opr[curOpr], rightVal);
				}
			}
			else {
				rightVal = tempVal;
				curOpr == 1 ? leftVal = randomInt(rightVal > min ? rightVal: min, max) : leftVal = randomInt(min, max);
				if (curOpr >= 2 && lastOpr <= 1 || curOpr == 1 && lastOpr <= 1 || curOpr == 3 && (lastOpr ==3||lastOpr==2)) {
					exp = to_string(leftVal)+ opr[curOpr] + "(" + exp + ")";
					tempVal = operate(leftVal, opr[curOpr], rightVal);
				}
				else {
					exp = to_string(leftVal) + opr[curOpr] + exp;
					tempVal = operate(leftVal, opr[curOpr], rightVal);
				}
			}
		}
	}
	return exp;
}

int main() {
	srand((unsigned)(time(NULL)));
	string test;
	for (int i = 0; i < 25; i++) {
		test = newExp(3, 2, 0, 20);
		cout << i+1 <<'\t'<< test << " = " << calc_double(test)<<endl;
	}
	//system("pause");
	/*int i;
	for (i = 0; i < 20; i++) {
		cout << randomInt(0, 1) << endl;
	}*/
	system("pause");
}