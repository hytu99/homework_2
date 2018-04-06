#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stack>
#include<string>
#include<iostream>
#include<map>
#include"calc.h"
using namespace std;


class arithmetic {
private:
	map<string, string> bank;
	int expNum;
	int expType;    //0 for integers, 1 for decimals, 2 for fractions
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
		oprNum = n;
	}

	void setBounds(int min, int max) {
		this->min = min;
		this->max = max;
	}

	void setAcurracy(int n) {
		int accuracy = n;
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

	void generate() {
		bank["2/3"] = calc_frac("2/3");
		bank["3*4-8"] = calc_frac("3*4-8");
	}

};

//int main() {
//
//	arithmetic test;
//	string* expSet;
//	string* ansSet;
//	test.setExpNum(2);
//	test.generate();
//	expSet = test.getExpSet();
//	ansSet = test.getAnsSet();
//	for (int i = 0; i < 2; i++) {
//		cout << expSet[i] << "=" << ansSet[i] << endl;
//	}
//	cout << " " << endl;
//	for (int i = 0; i < 2; i++) {
//		cout << expSet[i] << "=" << test.getAnswer(expSet[i]) << endl;
//	}
//	system("pause");
//
//}