#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stack>
#include<string>
#include<iostream>
#include<map>

using namespace std; 

int preop(char c1, char c2);
int isoperator(char c);
double operate(double a, char c, double b);
string calc_double(string s);

class Fraction {
private:
	int nume;  // numerator
	int deno;  // denominator
public:
	Fraction(int nu = 0, int de = 1) :nume(nu), deno(de) {}
	void simplify();
	string display();
	void setNume(int nu)
	{
		nume = nu;
	}
	void setDeno(int de)
	{
		deno = de;
	}
	int getNume()
	{
		return nume;
	}
	int getDeno()
	{
		return deno;
	}

	friend Fraction operator+(const Fraction &c1, const Fraction &c2);
	friend Fraction operator-(const Fraction &c1, const Fraction &c2);
	friend Fraction operator*(const Fraction &c1, const Fraction &c2);
	friend Fraction operator/(const Fraction &c1, const Fraction &c2);
	friend Fraction operator^(const Fraction &c1, const int &c2);

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


