#include<iostream>
#include<math.h>
#include<random>
#include<ctime>
#include<string>
#include"calc.h"

#define epsilon 1e-8
#define eleMax 9;
using namespace std;

int randomInt(int min, int max) {

	//default_random_engine e((unsigned)time(NULL));
	//uniform_int_distribution<int> u(min, max);
	//return u(e);
	return rand() % (max - min + 1) + min;
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

	leftVal = randomFrac(minFrac,maxFrac);
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
	exp = leftVal.display() +" "+ opr[curOpr] +" "+ rightVal.display();
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
				exp = exp +" "+ opr[curOpr] +" "+ rightVal.display();
				tempVal = operate(leftVal, opr[curOpr], rightVal);
			}
		}
		else {
			rightVal = tempVal;
			curOpr == 1 ? leftVal = randomFrac(rightVal > minFrac ? rightVal : minFrac, maxFrac) : leftVal = randomFrac(minFrac, maxFrac);

			leftVal.simplify();
			rightVal.simplify();
			if (curOpr >= 2 && lastOpr <= 1 || curOpr == 1 && lastOpr <= 1 || curOpr == 3 && (lastOpr == 3 || lastOpr == 2)) {
				exp = leftVal.display() +" "+ opr[curOpr] + " ( " + exp + " ) ";
				tempVal = operate(leftVal, opr[curOpr], rightVal);
			}
			else {
				exp = leftVal.display() +" "+ opr[curOpr] +" "+ exp;
				tempVal = operate(leftVal, opr[curOpr], rightVal);
			}
		}

		
	}
	result = tempVal;
	return exp;
}

//int main() {
//
//	srand((unsigned)(time(NULL)));
//	string test;
//	Fraction result;
//	for (int i = 0; i < 25; i++) {
//		test = newFracExp(3, 1, result);
//		result.simplify();
//		cout << i + 1 << '\t' << test << " = " << result.display() <<'\t'<< calc_frac(test) << endl;
//	}
//	system("pause");
//}