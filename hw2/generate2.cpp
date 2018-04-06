#include<iostream>
#include<math.h>
#include<random>
#include<ctime>
#include<string>
#include"calc.h"
#define epsilon 1e-8
#define eleMax 9;
using namespace std;

double randomInt(int min, int max) {
	return rand() % (max - min + 1) + min;
}

string newExp(int oprNum, int oprType, int min, int max, double &result) {

	if (!min) {
		min++;
	}

	string exp;
	const char opr[5] = { '+','-','*','/','^' };
	int oprMax;
	int curOpr, lastOpr;
	double leftVal, rightVal, tempVal;
	int powerNum = 2;

	switch (oprType) {
	case 0:oprMax = 1; break;
	case 1:oprMax = 3; break;
	case 2:oprMax = 4; break;
	}
	
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
		rightVal = randomInt(min, floor(leftVal));
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

	exp = to_string((int)leftVal) + " " + opr[curOpr] + " " + to_string((int)rightVal);
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
			exp = "( " + exp + " ) " + opr[curOpr] + " " + to_string((int)rightVal);
			tempVal = operate(leftVal, opr[curOpr], rightVal);
		}
		else {
			if (curOpr == 3&&tempVal == 0 || curOpr == 1&&tempVal >= max  || randomInt(0,1)&&(!(curOpr == 1 && tempVal < min))) {
				leftVal = tempVal;
				curOpr == 1 ? rightVal = randomInt(min, leftVal < max? leftVal : max) : rightVal = randomInt(min, max);
				if (curOpr >= 2 && lastOpr <= 1) {
					exp = "( " + exp + " ) " + opr[curOpr] + " " + to_string((int)rightVal);
					tempVal = operate(leftVal, opr[curOpr], rightVal);
				}
				else {
					exp = exp + " " + opr[curOpr] + " " + to_string((int)rightVal);
					tempVal = operate(leftVal, opr[curOpr], rightVal);
				}
			}
			else {
				rightVal = tempVal;
				curOpr == 1 ? leftVal = randomInt(rightVal > min ? rightVal: min, max) : leftVal = randomInt(min, max);
				if (curOpr >= 2 && lastOpr <= 1 || curOpr == 1 && lastOpr <= 1 || curOpr == 3 && (lastOpr ==3||lastOpr==2)) {
					exp = to_string((int)leftVal)+ " " + opr[curOpr] + " ( " + exp + " )";
					tempVal = operate(leftVal, opr[curOpr], rightVal);
				}
				else {
					exp = to_string((int)leftVal) + " " + opr[curOpr] + " " + exp;
					tempVal = operate(leftVal, opr[curOpr], rightVal);
				}
			}
		}
	}
	result = tempVal;
	return exp;

}

Fraction randomFrac(Fraction min, Fraction max) {

	int deno = min.getDeno()*max.getDeno();
	int numeMin = min.getNume()*max.getDeno();
	int numeMax = min.getDeno()*max.getNume();
	int nume = randomInt(numeMin, numeMax);
	Fraction frac(nume, deno);
	return frac;
}

string newFracExp(int oprNum, int oprType, Fraction &result) {

	string exp;
	Fraction minFrac(1, 10), maxFrac(1, 1);
	const char opr[4] = { '+','-','*','/' };
	int oprMax;
	switch (oprType) {
	case 0:oprMax = 1; break;
	case 1:oprMax = 3; break;
	}
	Fraction leftVal, rightVal, tempVal;
	int lastOpr, curOpr;

	leftVal = randomFrac(minFrac, maxFrac);
	curOpr = randomInt(0, oprMax);
	oprNum--;

	switch (curOpr) {
	case 0:
		rightVal = randomFrac(minFrac, maxFrac);
		break;
	case 1: //leftVal = randomInt(min, max);
		rightVal = randomFrac(minFrac, leftVal);
		break;
	case 2: //leftVal = randomInt(min, max);
		rightVal = randomFrac(minFrac, maxFrac);
		break;
	case 3: //leftVal = randomInt(min, max);
		rightVal = randomFrac(minFrac, maxFrac);
		break;
	}

	leftVal.simplify();
	rightVal.simplify();
	exp = leftVal.display() + " " + opr[curOpr] + " " + rightVal.display();
	tempVal = operate(leftVal, opr[curOpr], rightVal);

	while (oprNum) {
		lastOpr = curOpr;
		curOpr = randomInt(0, oprMax);
		oprNum--;

		if (curOpr == 3 && tempVal == Fraction(0, 1) || curOpr == 1 && tempVal >= maxFrac || randomInt(0, 1) && (!(curOpr == 1 && tempVal <minFrac))) {
			leftVal = tempVal;
			curOpr == 1 ? rightVal = randomFrac(minFrac, leftVal < maxFrac ? leftVal : maxFrac) : rightVal = randomFrac(minFrac, maxFrac);

			leftVal.simplify();
			rightVal.simplify();
			if (curOpr >= 2 && lastOpr <= 1) {
				exp = " ( " + exp + " ) " + opr[curOpr] + " " + rightVal.display();
				tempVal = operate(leftVal, opr[curOpr], rightVal);
			}
			else {
				exp = exp + " " + opr[curOpr] + " " + rightVal.display();
				tempVal = operate(leftVal, opr[curOpr], rightVal);
			}
		}
		else {
			rightVal = tempVal;
			curOpr == 1 ? leftVal = randomFrac(rightVal > minFrac ? rightVal : minFrac, maxFrac) : leftVal = randomFrac(minFrac, maxFrac);

			leftVal.simplify();
			rightVal.simplify();
			if (curOpr >= 2 && lastOpr <= 1 || curOpr == 1 && lastOpr <= 1 || curOpr == 3 && (lastOpr == 3 || lastOpr == 2)) {
				exp = leftVal.display() + " " + opr[curOpr] + " ( " + exp + " ) ";
				tempVal = operate(leftVal, opr[curOpr], rightVal);
			}
			else {
				exp = leftVal.display() + " " + opr[curOpr] + " " + exp;
				tempVal = operate(leftVal, opr[curOpr], rightVal);
			}
		}


	}
	result = tempVal;
	return exp;
}

//int main() {
//	srand((unsigned)(time(NULL)));
//	string test;
//	double result = 0;
//	for (int i = 0; i < 100; i++) {
//		test = newExp(3, 2, 0, 20, result);
//		cout << i+1 <<'\t'<< test << "  =  " << calc_double(test)<<"  "<< result <<endl;
//	}
//	//system("pause");
//	/*int i;
//	for (i = 0; i < 20; i++) {
//		cout << randomInt(0, 1) << endl;
//	}*/
//	system("pause");
//}