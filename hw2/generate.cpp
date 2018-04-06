#include<iostream>
#include<math.h>
#include<random>
#include<ctime>
#include<string>
#include"calc.h"
using namespace std;

int randomInt(int min, int max) {

	default_random_engine e(time(NULL));
	uniform_int_distribution<int> u(min, max);
	return u(e);
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
	int leftVal, rightVal;

	curOpr = randomInt(0, oprMax);
	oprNum--;
	switch (curOpr) {
	case 0: do { 
		        leftVal = randomInt(min, max); } while( (max - leftVal) <= min);
		rightVal = randomInt(min, max-leftVal);
		break;
	case 1: leftVal = randomInt(min, max);
		rightVal = randomInt(min, leftVal);
		break;
	case 2:do { leftVal = randomInt(min, max); } while (max / leftVal <= min);
		rightVal = randomInt(min, max / leftVal);
		break;
	case 3:
		   do { leftVal = randomInt(min, max); } while (leftVal / min<max || leftVal / max>min);
		   rightVal = randomInt(leftVal / max, leftVal / min);
		break;
	case 4:rightVal = randomInt(2, 4);
		do { leftVal = randomInt(min, max); } while (pow(leftVal, rightVal) >= max);
		break;
	}
	exp = to_string(leftVal) + opr[curOpr] + to_string(rightVal);
	return exp;
}

//int main() {
//
//	string test = newExp(1, 1, 20, 100);
//	cout << test << endl;
//	system("pasue");
//
//}