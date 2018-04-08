#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stack>
#include<string>
#include<map>
#include<iostream>
#include<ctime>

#ifndef ArithmeticDLL
#define ArithmeticAPI __declspec(dllexport)
#else 
#define ArithmeticAPI __declspec(dllimport)
#endif 

#define epsilon 1e-8
#define eleMax 9;
#define INTEGER 0
#define DECIMAL 1
#define FRACTION 2
#define ADDSUB 0
#define MULDIV 1
#define POW 2
#define DIVISIONSIZE 500
using namespace std;

ArithmeticAPI int preop(char c1, char c2);
ArithmeticAPI int isoperator(char c);

ArithmeticAPI double operate(double a, char c, double b);

ArithmeticAPI string calc_double(string s);

//*********************************************

class ArithmeticAPI Fraction
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

	ArithmeticAPI friend Fraction operator+(const Fraction &c1, const Fraction &c2);
	ArithmeticAPI friend Fraction operator-(const Fraction &c1, const Fraction &c2);
	ArithmeticAPI friend Fraction operator*(const Fraction &c1, const Fraction &c2);
	ArithmeticAPI friend Fraction operator/(const Fraction &c1, const Fraction &c2);
	ArithmeticAPI friend Fraction operator^(const Fraction &c1, const Fraction &c2);

	Fraction operator+();
	Fraction operator-();

	ArithmeticAPI friend bool operator>(const Fraction &c1, const Fraction &c2);
	ArithmeticAPI friend bool operator<(const Fraction &c1, const Fraction &c2);
	ArithmeticAPI friend bool operator==(const Fraction &c1, const Fraction &c2);
	ArithmeticAPI friend bool operator!=(const Fraction &c1, const Fraction &c2);
	ArithmeticAPI friend bool operator>=(const Fraction &c1, const Fraction &c2);
	ArithmeticAPI friend bool operator<=(const Fraction &c1, const Fraction &c2);

	ArithmeticAPI friend Fraction operate(const Fraction &c1, char c, const Fraction &c2);
};

ArithmeticAPI string calc_frac(string s);

ArithmeticAPI double randomInt(int min, int max);

ArithmeticAPI string newExp(int oprNum, int oprType, int min, int max, double &result);

ArithmeticAPI int randomDivisor(int dividend, int min, int max);

ArithmeticAPI int randomDividend(int divisor, int min, int max);

ArithmeticAPI string newExactDivExp(int oprNum, int oprType, int min, int max, int &result);

ArithmeticAPI Fraction randomFrac(Fraction min, Fraction max);

ArithmeticAPI string newFracExp(int oprNum, int oprType, Fraction &result);

class ArithmeticAPI arithmetic {
private:
	typedef struct expNode {
		string exp;
		string ans;
	}expNode;
	expNode *p;
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

	void generate();
	
};
