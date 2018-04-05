#pragma once

#include <iostream> 
#include <math.h>
#include <string>
#include "calc.h"
using namespace std;

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