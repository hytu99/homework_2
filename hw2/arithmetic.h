#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stack>
#include<string>
#include<iostream>
#include<map>
#include<ctime>

#define epsilon 1e-8
#define INTEGER 0
#define DECIMAL 1
#define FRACTION 2
#define DIVISIONSIZE 500
using namespace std;

int preop(char c1, char c2);
int isoperator(char c);

double operate(double a, char c, double b);

string calc_double(string s);

//*********************************************

class  Fraction
{
private:
	int nume;  // numerator
	int deno;  // denominator
public:
	Fraction(int nu = 0, int de = 1) :nume(nu), deno(de) {}
	void simplify();
	string display();
	void setNume(int nu);
	void setDeno(int de);
	int getNume();
	int getDeno();

	 friend Fraction operator+(const Fraction &c1, const Fraction &c2);
	 friend Fraction operator-(const Fraction &c1, const Fraction &c2);
	 friend Fraction operator*(const Fraction &c1, const Fraction &c2);
	 friend Fraction operator/(const Fraction &c1, const Fraction &c2);
	 friend Fraction operator^(const Fraction &c1, const Fraction &c2);

	Fraction operator+();
	Fraction operator-();

	 friend bool operator>(const Fraction &c1, const Fraction &c2);
	 friend bool operator<(const Fraction &c1, const Fraction &c2);
	 friend bool operator==(const Fraction &c1, const Fraction &c2);
	 friend bool operator!=(const Fraction &c1, const Fraction &c2);
	 friend bool operator>=(const Fraction &c1, const Fraction &c2);
	 friend bool operator<=(const Fraction &c1, const Fraction &c2);

	 friend Fraction operate(const Fraction &c1, char c, const Fraction &c2);
};

 string calc_frac(string s);

 double randomInt(int min, int max);

 string newExp(int oprNum, int oprType[], int min, int max, double &result);

 int randomDivisor(int dividend, int min, int max);

 int randomDividend(int divisor, int min, int max);

 double randomDec(double min, double max, int k);

 string newExactDivExp(int oprNum, int oprType[], int min, int max, int &result);

 Fraction randomFrac(Fraction min, Fraction max);

 string newFracExp(int oprNum, int oprType[], int min, int max, Fraction &result);

class  arithmetic {
private:
	typedef struct expNode {
		string exp;
		string ans;
	}expNode;
	expNode *p;
	int expNum;
	int expType;    //0 for integers, 1 for decimals, 2 for fractions
	int oprNum;
	//int oprTypeOption;    //0 for +-, 1 for +-x/, 2 for +-x/^
	int oprType[5]; //******
	int min, max;
	int accuracy;   //the accuracy of decimals

public:
	arithmetic() {

		expNum = 1;
		expType = 0;
		oprNum = 1;
		//oprType = 0;
		oprType[0] = 1; //***
		oprType[1] = 1;
		oprType[2] = 0;
		oprType[3] = 0;
		oprType[4] = 0; //***

		min = 1;
		max = 10;
		accuracy = 2;

	}

	void setExpNum(int n);
	void setExpType(int n);
	void setOprNum(int n);
	//void setOprType(int n);
	void setOprAdd(int n);
	void setOprSub(int n);
	void setOprMul(int n);
	void setOprDiv(int n);
	void setOprPow(int n);
	void setOprAll(int a, int s, int m, int d, int p);
	void setOprByStr(string s);

	void setBounds(int min, int max);
	void setAccuracy(int n);

	int getExpNum();

	string* getExpSet();

	string* getAnsSet();

	void generate();

};

