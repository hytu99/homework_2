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

	void setExpNum(int n) {
		expNum = n;
	}

	void setExpType(int n) {
		expType = n;
	}

	void setOprNum(int n) {
		oprNum = n;
	}

	void setOprType(int n) {
		oprType = n;
	}

	void setBounds(int min, int max) {
		this->min = min;
		this->max = max;
	}

	void setAccuracy(int n) {
		accuracy = n;
	}

	string* getExpSet() {
		string* expSet = new string[expNum];
		map<string, string>::iterator itr = bank.begin();
		for (int i=0; i<expNum ; i++,itr++) {
			expSet[i] = itr->first;
		}
		return expSet;
	}

	string* getAnsSet() {
		string* ansSet = new string[expNum];
		map<string, string>::iterator itr = bank.begin();
		for (int i = 0; i<expNum; i++, itr++) {
			ansSet[i] = itr->second;
		}
		return ansSet;
	}

	string getAnswer(string exp) {
		return bank[exp];
	}

	void generate() 
	{
		/*bank["2/3"] = calc_frac("2/3");
		bank["3*4-8"] = calc_frac("3*4-8");*/
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
				cout << i + 1 << '\t' << exp << " = " << result << endl;
			}
			else {
				cout << i + 1 << '\t' << exp << " = " << resultF.display() << endl;
			}

		}

	}

};

int main() {

	srand((unsigned)(time(NULL)));
	arithmetic test;
	test.setExpNum(10);
	test.setExpType(1);
	test.setBounds(0, 10);
	test.setOprNum(4);
	test.setOprType(1);
	test.setAccuracy(4);

	test.generate();

	//string* expSet;
	//string* ansSet;
	//test.setExpNum(2);
	//test.generate();
	//expSet = test.getExpSet();
	//ansSet = test.getAnsSet();
	//for (int i = 0; i < 2; i++) {
	//	cout << expSet[i] << "=" << ansSet[i] << endl;
	//}
	//cout << " " << endl;
	//for (int i = 0; i < 2; i++) {
	//	cout << expSet[i] << "=" << test.getAnswer(expSet[i]) << endl;
	//}
	system("pause");

}