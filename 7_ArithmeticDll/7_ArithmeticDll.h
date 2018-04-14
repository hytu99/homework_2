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
#define INTEGER 0
#define DECIMAL 1
#define FRACTION 2
#define DIVISIONSIZE 500
using namespace std;

//Compare the precedence of two opetator
ArithmeticAPI int preop(char c1, char c2);

//Judge if it's an operator
ArithmeticAPI int isoperator(char c);

//Compute the operation result of two numbers
ArithmeticAPI double operate(double a, char c, double b);

//Compute the value of the expression composed of integers and decimals
ArithmeticAPI string calc_double(string s);

//Fraction
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

//Compute the value of the expression composed of integers and fractions
ArithmeticAPI string calc_frac(string s);

//return a random number between min and max
ArithmeticAPI int randomInt(int min, int max);

ArithmeticAPI double randomDec(double min, double max, int k);

//return an expression composed of integers meeting the requirements
ArithmeticAPI string newExp(int oprNum, int oprType[], int min, int max, double &result, int accuracy);

//return a random divisor between min and max for the dividend
ArithmeticAPI int randomDivisor(int dividend, int min, int max);

//return a random multiple of the dividend between min and max 
ArithmeticAPI int randomDividend(int divisor, int min, int max);

//return an expression composed of integers meeting the requirements
ArithmeticAPI string newExactDivExp(int oprNum, int oprType[], int min, int max, int &result);

//return a random fraction between min and max
ArithmeticAPI Fraction randomFrac(Fraction min, Fraction max, int denoMin, int denoMax);

//return an expression composed of fractions meeting the requirements
ArithmeticAPI string newFracExp(int oprNum, int oprType[], int min, int max, Fraction &result);

class ArithmeticAPI arithmetic {
private:
	typedef struct expNode {
		string exp;
		string ans;
	}expNode;
	expNode *p;
	int expNum;
	int expType;    //0 for integers, 1 for decimals, 2 for fractions
	int oprNum;
	int oprType[5];    //0 for +-, 1 for +-x/, 2 for +-x/^
	int min, max;
	int accuracy;   //the accuracy of decimals

public:
	arithmetic() {

		expNum = 1;
		expType = 0;
		oprNum = 1;
		oprType[0] = 1; 
		oprType[1] = 1;
		oprType[2] = 0;
		oprType[3] = 0;
		oprType[4] = 0;
		min = 1;
		max = 10;
		accuracy = 2;

	}

	void setExpNum(int n);
	void setExpType(int n);
	void setOprNum(int n);
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
