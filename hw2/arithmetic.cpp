#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stack>
#include<string>
#include<iostream>
#include<map>
#include<ctime>
#include"calc.h"
#include"generate2.h"
using namespace std;

class arithmetic {
private:
	map<string, string> bank;
	int expNum;
	int expType;    //0 for decimals, 1 for fractions
	int oprNum;
	int oprType;    //0 for +-, 1 for +-x/, 2 for +-x/^
	int min, max;
	int accuracy;   //the accuracy of decimals

public:
	arithmetic() {

		expNum = 1;
		expType = 0;
		oprNum = 1;
		oprType = 0;
		min = 0;
		max = 10;
		accuracy = 0;

	}

	void setExpNum(int n);

	void setExpType(int n);

	void setOprNum(int n);

	void setOprType(int n);

	void setBounds(int min, int max);

	void setAccuracy(int n);

	string* getExpSet();

	string* getAnsSet();

	string getAnswer(string exp);

	void generate();

};

void arithmetic::setExpNum(int n) {
	expNum = n;
}

void arithmetic::arithmetic::setExpType(int n) {
	expType = n;
}

void arithmetic::arithmetic::setOprNum(int n) {
	oprNum = n;
}

void arithmetic::arithmetic::setOprType(int n) {
	oprType = n;
}

void arithmetic::setBounds(int min, int max) {
	this->min = min;
	this->max = max;
}

void arithmetic::setAccuracy(int n) {
	accuracy = n;
}

string* arithmetic::getExpSet() {
	string* expSet = new string[expNum];
	map<string, string>::iterator itr = bank.begin();
	for (int i = 0; i<expNum; i++, itr++) {
		expSet[i] = itr->first;
	}
	return expSet;
}

string* arithmetic::getAnsSet() {
	string* ansSet = new string[expNum];
	map<string, string>::iterator itr = bank.begin();
	for (int i = 0; i<expNum; i++, itr++) {
		ansSet[i] = itr->second;
	}
	return ansSet;
}

string arithmetic::getAnswer(string exp) {
	return bank[exp];
}

void arithmetic::generate()
{
	srand((unsigned)(time(NULL)));

	int i;
	string exp;
	double resultD;
	Fraction resultF;
	char result[100];
	for (i = 0; i < expNum; i++)
	{
		exp = expType == 0 ? newExp(oprNum, oprType, min, max, resultD) : newFracExp(oprNum, oprType, resultF);
		if (expType == 0) {
			switch (accuracy) {
			case 0: sprintf(result, "%.0lf", resultD); break;
			case 1: sprintf(result, "%.1lf", resultD); break;
			case 2: sprintf(result, "%.2lf", resultD); break;
			case 3: sprintf(result, "%.3lf", resultD); break;
			case 4: sprintf(result, "%.4lf", resultD); break;
			case 5: sprintf(result, "%.5lf", resultD); break;
			default: sprintf(result, "%lf", resultD);
			}
			//cout << i + 1 << '\t' << exp << " = " << result << endl;
			bank[exp] = result;
		}
		else {
			//cout << i + 1 << '\t' << exp << " = " << resultF.display() << endl;
			bank[exp] = resultF.display();
		}

	}

}

int main() {

	arithmetic test;

	test.setExpNum(10);
	test.setExpType(1);
	test.setBounds(0, 10);
	test.setOprNum(4);
	test.setOprType(2);
	test.setAccuracy(4);

	test.generate();

	string* expSet;
	string* ansSet;
	expSet = test.getExpSet();
	ansSet = test.getAnsSet();
	for (int i = 0; i < 10; i++) {
		cout << expSet[i] << " = " << ansSet[i] << endl;
	}
	//cout << " " << endl;
	//for (int i = 0; i < 2; i++) {
	//	cout << expSet[i] << "=" << test.getAnswer(expSet[i]) << endl;
	//}
	system("pause");

}