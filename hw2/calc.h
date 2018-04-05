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
	friend Fraction operator+(const Fraction &c1, const Fraction &c2);
	friend Fraction operator-(const Fraction &c1, const Fraction &c2);
	friend Fraction operator*(const Fraction &c1, const Fraction &c2);
	friend Fraction operator/(const Fraction &c1, const Fraction &c2);

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


