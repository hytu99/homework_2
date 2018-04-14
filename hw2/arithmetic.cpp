#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stack>
#include<string>
#include<iostream>
#include<map>
#include<ctime>
#include"arithmetic.h"

#define epsilon 1e-8
#define eleMax 9;
using namespace std;


int preop(char c1, char c2)
{
	map<char, int> ch = { { '+', 1 },{ '-', 1 },{ '*', 3 },{ '/', 3 },{ '^', 4 },{ '(', 0 },{ '#', -1 } };
	return ch[c1] >= ch[c2] ? 1 : 0;
}

int isoperator(char c)
{
	if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' || c == '#' || c == '^')
	{
		return 1;
	}
	else
		return 0;
}

double operate(double a, char c, double b)
{
	double e;
	switch (c) {
	case '+': e = a + b; break;
	case '-': e = a - b; break;
	case '*': e = a * b; break;
	case '/': e = a / b; break;
	case '^': e = pow(a, b); break;
	}
	return e;
}

string calc_double(string s)
{
	int i = 0, k = 0;
	stack<char> Opr;
	stack<double> Num;
	char ch, c;
	double a, b, temp;
	char result[100];

	Opr.push('#');
	s += "#";

	while (!Opr.empty()) {
		ch = s[i++];
		if (ch >= '0' && ch <= '9')
		{
			temp = ch - '0';
			while (((ch = s[i]) >= '0') && (ch <= '9'))
			{
				temp = temp * 10 + ch - '0';
				i++;
			}
			k = 0;
			if ((ch == '.'))
			{
				i++;
				while (((ch = s[i]) >= '0') && (ch <= '9'))
				{
					temp = temp * 10 + ch - '0';
					k++;
					i++;
				}
			}
			Num.push(temp / pow(10, k));
			continue;
		}
		if (ch == ' ')
		{
			continue;
		}
		switch (ch)
		{
		case '(': Opr.push(ch); break;
		case ')':
			while ((c = Opr.top()) && (c != '(')) {
				Opr.pop();
				b = Num.top();
				Num.pop();
				a = Num.top();
				Num.pop();
				Num.push(operate(a, c, b));
			}
			if (c == '(')
				Opr.pop();
			break;
		default:
			while (!Opr.empty() && (c = Opr.top()) && preop(c, ch)) {
				Opr.pop();
				if (c == '#')
					break;
				b = Num.top();
				Num.pop();
				a = Num.top();
				Num.pop();
				Num.push(operate(a, c, b));
			}
			if (ch != '#') {
				Opr.push(ch);
			}
		}
	}
	//printf("result: %.4lf\n", Num.top());
	sprintf(result, "%.2lf", (Num.top()));
	return result;
}

void Fraction::simplify()
{
	int m, n, r;
	m = abs(deno);
	n = abs(nume);
	if (n == 0)
		return;
	while (r = m % n)  // greatest common divisor
	{
		m = n;
		n = r;
	}
	deno /= n;
	nume /= n;
	if (deno<0)
	{
		deno = -deno;
		nume = -nume;
	}
}

string Fraction::display()
{
	string s = "";
	if (nume == 0)
	{
		s = "0";
	}
	else if (deno == 1)
	{
		s = to_string(nume);
	}
	else
	{
		s = to_string(nume) + "/" + to_string(deno);
	}
	return s;
}

void Fraction::setNume(int nu)
{
	nume = nu;
}
void Fraction::setDeno(int de)
{
	deno = de;
}
int Fraction::getNume()
{
	return nume;
}
int Fraction::getDeno()
{
	return deno;
}

Fraction operator+(const Fraction &c1, const Fraction &c2)
{
	Fraction t;
	t.nume = c1.nume*c2.deno + c2.nume*c1.deno;
	t.deno = c1.deno*c2.deno;
	t.simplify();
	return t;
}

Fraction operator-(const Fraction &c1, const Fraction &c2)
{
	Fraction t;
	t.nume = c1.nume*c2.deno - c2.nume*c1.deno;
	t.deno = c1.deno*c2.deno;
	t.simplify();
	return t;
}

Fraction operator*(const Fraction &c1, const Fraction &c2)
{
	Fraction t;
	t.nume = c1.nume*c2.nume;
	t.deno = c1.deno*c2.deno;
	t.simplify();
	return t;
}

Fraction operator/(const Fraction &c1, const Fraction &c2)
{
	Fraction t;
	if (!c2.nume) return c1;
	t.nume = c1.nume*c2.deno;
	t.deno = c1.deno*c2.nume;
	t.simplify();
	return t;
}

Fraction operator^(const Fraction &c1, const Fraction &c2)
{
	Fraction t;
	t.nume = (int)pow(c1.nume, c2.nume);
	t.deno = (int)pow(c1.deno, c2.nume);
	t.simplify();
	return t;

}

Fraction Fraction:: operator+()
{
	return *this;
}

Fraction Fraction:: operator-()
{
	Fraction c;
	c.nume = -nume;
	c.deno = -deno;
	return c;
}

bool operator>(const Fraction &c1, const Fraction &c2)
{
	int c1_nume, c2_nume, common_deno;
	c1_nume = c1.nume*c2.deno;
	c2_nume = c2.nume*c1.deno;
	common_deno = c1.deno*c2.deno;
	if (c1_nume - c2_nume>0) return true;
	return false;
}

bool operator<(const Fraction &c1, const Fraction &c2)
{
	int c1_nume, c2_nume, common_deno;
	c1_nume = c1.nume*c2.deno;
	c2_nume = c2.nume*c1.deno;
	common_deno = c1.deno*c2.deno;
	if (c1_nume - c2_nume<0) return true;
	return false;
}

bool operator==(const Fraction &c1, const Fraction &c2)
{
	if (c1 != c2) return false;
	return true;
}

bool operator!=(const Fraction &c1, const Fraction &c2)
{
	if (c1>c2 || c1<c2) return true;
	return false;
}

bool operator>=(const Fraction &c1, const Fraction &c2)
{
	if (c1<c2) return false;
	return true;
}

bool operator<=(const Fraction &c1, const Fraction &c2)
{
	if (c1>c2) return false;
	return true;
}

Fraction operate(const Fraction &a, char c, const Fraction &b)
{
	Fraction e;
	switch (c) {
	case '+': e = a + b; break;
	case '-': e = a - b; break;
	case '*': e = a * b; break;
	case '/': e = a / b; break;
	case '^': e = a ^ b; break;
	}
	return e;
}

string calc_frac(string s)
{
	int i = 0, k = 0;
	stack<char> Opr;
	stack<Fraction> Num;
	char ch, c;
	Fraction a, b, temp;
	int tempNume, tempDeno;
	string result;

	Opr.push('#');
	s += "#";

	while (!Opr.empty()) {
		ch = s[i++];
		if (ch >= '0' && ch <= '9')
		{
			tempNume = ch - '0';
			while (((ch = s[i]) >= '0') && (ch <= '9'))
			{
				tempNume = tempNume * 10 + ch - '0';
				i++;
			}
			temp.setNume(tempNume);
			if ((ch == '/') && s[i + 1] >= '0' && s[i + 1] <= '9')
			{
				i++;
				tempDeno = 0;
				while (((ch = s[i]) >= '0') && (ch <= '9'))
				{
					tempDeno = tempDeno * 10 + ch - '0';
					i++;
				}
				temp.setDeno(tempDeno);
			}
			else
			{
				//integers
				temp.setDeno(1);
			}
			Num.push(temp);
			continue;
		}
		if (ch == ' ')
		{
			continue;
		}
		switch (ch)
		{
		case '(': Opr.push(ch); break;
		case ')':
			while ((c = Opr.top()) && (c != '(')) {
				Opr.pop();
				b = Num.top();
				Num.pop();
				a = Num.top();
				Num.pop();
				Num.push(operate(a, c, b));
			}
			if (c == '(')
				Opr.pop();
			break;
		default:
			while (!Opr.empty() && (c = Opr.top()) && preop(c, ch)) {
				Opr.pop();
				if (c == '#')
					break;
				b = Num.top();
				Num.pop();
				a = Num.top();
				Num.pop();
				Num.push(operate(a, c, b));
			}
			if (ch != '#') {
				Opr.push(ch);
			}
		}
	}
	Num.top().simplify();
	result = Num.top().display();
	return result;
}

double randomInt(int min, int max) {
	return rand() % (max - min + 1) + min;
}

double randomDec(double min, double max, int k) {
	int minInt = (int)ceil(min*pow(10,k));
	int maxInt = (int)floor(max*pow(10, k));
	double randDec;
	int randInt;
	if (minInt <= maxInt) {
		randInt = rand() % (maxInt - minInt + 1) + minInt;
		randDec = (double)randInt / pow(10, k);
	}
	else {
		randDec = min;
	}
	return randDec;
}


string newExp(int oprNum, int oprType[], int min, int max, double &result) {

	if (!min) {
		min++;
	}
	string exp;
	int i, j = 0, oprMax = 0;
	char opr[5];
	int curOpr, lastOpr;
	double leftVal, rightVal, tempVal;
	int powerNum = 2;

	for (i = 0; i < 5; i++) {
		if (oprType[i]) {
			switch (i)
			{
			case 0: opr[j++] = '+'; break;
			case 1: opr[j++] = '-'; break;
			case 2: opr[j++] = '*'; break;
			case 3: opr[j++] = '/'; break;
			case 4: opr[j++] = '^'; break;
			default:
				break;
			}
		}
	}
	oprMax = j - 1;

	leftVal = randomInt(min, max);
	if (leftVal > 20 && opr[oprMax] == '^' && oprMax > 0)
		oprMax--;
	curOpr = (int)randomInt(0, oprMax);
	oprNum--;

	switch (opr[curOpr]) {
	case '+':
		rightVal = randomInt(min, max);
		break;
	case '-':
		rightVal = randomInt(min, (int)leftVal);
		break;
	case '*':
		rightVal = randomInt(min, max);
		break;
	case '/': 
		rightVal = randomInt(min, max);
		break;
	case '^':rightVal = randomInt(2, 3);
		powerNum--;
		break;
	}
	if (opr[curOpr] == '^')
		exp = to_string((int)leftVal) + opr[curOpr] + to_string((int)rightVal);
	else
		exp = to_string((int)leftVal) + " " + opr[curOpr] + " " + to_string((int)rightVal);
	tempVal = operate(leftVal, opr[curOpr], rightVal);

	while (oprNum) {
		lastOpr = curOpr;
		if ((powerNum == 0 || tempVal > 20) && opr[oprMax] == '^' && oprMax > 0)
			oprMax--;
		curOpr = (int)randomInt(0, oprMax);
		oprNum--;
		if (opr[curOpr] == '^') {
			powerNum--;
			leftVal = tempVal;
			rightVal = randomInt(2, 3);
			exp = "( " + exp + " )" + opr[curOpr] + "" + to_string((int)rightVal);
			tempVal = operate(leftVal, opr[curOpr], rightVal);
		}
		else {
			if (opr[curOpr] == '/' && tempVal == 0 || opr[curOpr] == '-' && tempVal >= max || (int)randomInt(0, 1) && (!(opr[curOpr] == '-' && tempVal < min))) {
				leftVal = tempVal;
				opr[curOpr] == '-' ? rightVal = randomInt(min, leftVal < max ? (int)leftVal : max) : rightVal = randomInt(min, max);
				if ((opr[curOpr] == '*' || opr[curOpr] == '/') && (opr[lastOpr] == '+' || opr[lastOpr] == '-')) {
					exp = "( " + exp + " ) " + opr[curOpr] + " " + to_string((int)rightVal);
					tempVal = operate(leftVal, opr[curOpr], rightVal);
				}
				else {
					exp = exp + " " + opr[curOpr] + " " + to_string((int)rightVal);
					tempVal = operate(leftVal, opr[curOpr], rightVal);
				}
			}
			else {
				rightVal = tempVal;
				opr[curOpr] == '-' ? leftVal = randomInt(rightVal > min ? (int)rightVal : min, max) : leftVal = randomInt(min, max);
				if ((opr[curOpr] == '*' || opr[curOpr] == '/') && (opr[lastOpr] == '+' || opr[lastOpr] == '-') || opr[curOpr] == '-' && (opr[lastOpr] == '+' || opr[lastOpr] == '-') || opr[curOpr] == '/' && (opr[lastOpr] == '*' || opr[lastOpr] == '/')) {
					exp = to_string((int)leftVal) + " " + opr[curOpr] + " ( " + exp + " )";
					tempVal = operate(leftVal, opr[curOpr], rightVal);
				}
				else {
					exp = to_string((int)leftVal) + " " + opr[curOpr] + " " + exp;
					tempVal = operate(leftVal, opr[curOpr], rightVal);
				}
			}
		}
	}
	result = tempVal;
	return exp;

}

int randomDivisor(int dividend, int min, int max) {

	int *divisor;
	divisor = new int[DIVISIONSIZE];
	divisor[0] = dividend;
	int count = 0;
	int i = min;
	while (i < dividend && i<max) {
		if (dividend%i == 0) {
			count++;
			divisor[count] = i;
		}
		i++;
	}
	int randDiv = 0;
	if (count > 0) {
		randDiv = (int)randomInt(0, count);
		return(divisor[randDiv]);
	}
	else {
		return dividend;
	}
}

int randomDividend(int divisor, int min, int max) {

	int *dividend;
	dividend = new int[DIVISIONSIZE];
	dividend[0] = divisor;
	int count = 0;
	int i = divisor + 1;
	while (i < max) {
		if (i%divisor == 0)
		{
			count++;
			dividend[count] = i;
		}
		i++;
	}
	int randDiv = 0;
	if (count > 0) {
		randDiv = (int)randomInt(0, count);
		return dividend[randDiv];
	}
	else {
		return divisor;
	}
}

string newExactDivExp(int oprNum, int oprType[], int min, int max, int &result) {

	if (!min) {
		min++;
	}

	string exp;
	//const char opr[5] = { '+','-','*','/','^' };
	int oprMax = 0, i, j = 0;
	char opr[5];
	int curOpr, lastOpr;
	int leftVal, rightVal, tempVal;
	int powerNum = 2;

	for (i = 0; i < 5; i++) {
		if (oprType[i]) {
			switch (i)
			{
			case 0: opr[j++] = '+'; break;
			case 1: opr[j++] = '-'; break;
			case 2: opr[j++] = '*'; break;
			case 3: opr[j++] = '/'; break;
			case 4: opr[j++] = '^'; break;
			default:
				break;
			}
		}
	}
	oprMax = j - 1;
	/*switch (oprType) {
	case 0:oprMax = 1; break;
	case 1:oprMax = 3; break;
	case 2:oprMax = 4; break;
	}*/

	leftVal = (int)randomInt(min, max);
	if (leftVal > 20 && opr[oprMax] == '^' && oprMax > 0)
		oprMax--;
	curOpr = (int)randomInt(0, oprMax);
	oprNum--;

	switch (opr[curOpr]) {
	case '+': 
		rightVal = (int)randomInt(min, max);
		break;
	case '-': 
		rightVal = (int)randomInt(min, leftVal);
		break;
	case '*': 
		rightVal = (int)randomInt(min, max);
		break;
	case '/': if (min == 0)min++;
		rightVal = randomDivisor(leftVal, min, leftVal);
		break;
	case '^':rightVal = (int)randomInt(2, 3);
		powerNum--;
		break;
	}
	if (opr[curOpr] == '^')
		exp = to_string(leftVal) + opr[curOpr] + to_string(rightVal);
	else
		exp = to_string(leftVal) + " " + opr[curOpr] + " " + to_string(rightVal);
	tempVal = (int)operate(leftVal, opr[curOpr], rightVal);
	while (oprNum) {
		lastOpr = curOpr;
		if ((powerNum == 0 || tempVal > 20) && opr[oprMax] == '^' && oprMax > 0)
			oprMax--;
		curOpr = (int)randomInt(0, oprMax);
		oprNum--;
		if (opr[curOpr] == '^') {
			powerNum--;
			leftVal = tempVal;
			rightVal = (int)randomInt(2, 3);
			exp = "( " + exp + " )" + opr[curOpr] + "" + to_string(rightVal);
			tempVal = (int)operate(leftVal, opr[curOpr], rightVal);
		}
		else {
			if (opr[curOpr] == '/' && tempVal == 0 || opr[curOpr] == '-' && tempVal >= max || (int)randomInt(0, 1) && (!(opr[curOpr] == '-' && tempVal < min))) {
				leftVal = tempVal;
				opr[curOpr] == '-' ? rightVal = (int)randomInt(min, leftVal < max ? leftVal : max) : rightVal = (int)randomInt(min, max);
				if (opr[curOpr] == '/') {
					if (!min)min++;
					rightVal = randomDivisor(leftVal, min, leftVal < max ? leftVal : max);
					if (rightVal == leftVal && (rightVal<min || rightVal>max)) {
						oprNum++;
						curOpr = lastOpr;
						continue;
					}
				}
				if ((opr[curOpr] == '*' || opr[curOpr] == '/') && (opr[lastOpr] == '+' || opr[lastOpr] == '-')) {
					exp = "( " + exp + " ) " + opr[curOpr] + " " + to_string(rightVal);
					tempVal = (int)operate(leftVal, opr[curOpr], rightVal);
				}
				else {
					exp = exp + " " + opr[curOpr] + " " + to_string(rightVal);
					tempVal = (int)operate(leftVal, opr[curOpr], rightVal);
				}
			}
			else {
				rightVal = tempVal;
				opr[curOpr] == '-' ? leftVal = (int)randomInt(rightVal > min ? rightVal : min, max) : leftVal = (int)randomInt(min, max);
				if (opr[curOpr] == '/') {
					leftVal = randomDividend(rightVal, rightVal > min ? rightVal : min, max);
					if (leftVal == rightVal && (leftVal<min || leftVal>max)) {
						oprNum++;
						curOpr = lastOpr;
						continue;
					}
				}
				if ((opr[curOpr] == '*' || opr[curOpr] == '/') && (opr[lastOpr] == '+' || opr[lastOpr] == '-') || opr[curOpr] == '-' && (opr[lastOpr] == '+' || opr[lastOpr] == '-') || opr[curOpr] == '/' && (opr[lastOpr] == '*' || opr[lastOpr] == '/')) {
					exp = to_string(leftVal) + " " + opr[curOpr] + " ( " + exp + " )";
					tempVal = (int)operate(leftVal, opr[curOpr], rightVal);
				}
				else {
					exp = to_string(leftVal) + " " + opr[curOpr] + " " + exp;
					tempVal = (int)operate(leftVal, opr[curOpr], rightVal);
				}
			}
		}
	}
	result = tempVal;
	return exp;

}

Fraction randomFrac(Fraction min, Fraction max, int denoMin, int denoMax) {

	int newDenoMin, newDenoMax;
	int nume, deno;
	if (min.getDeno() < max.getDeno())
	{
		newDenoMin = min.getDeno();
		newDenoMax = max.getDeno();
	}
	else
	{
		newDenoMin = max.getDeno();
		newDenoMax = min.getDeno();
	}
	if (newDenoMin < denoMin)
		newDenoMin = denoMin;
	if (newDenoMax > denoMax)
		newDenoMax = denoMax;
	deno = (int)randomInt(newDenoMin, newDenoMax);
	nume = (int)randomInt(1, deno);
	while (Fraction(nume, deno) > max || Fraction(nume, deno) < min)
	{
		nume = (int)randomInt(1, deno);
	}
	return Fraction(nume, deno);
}

//Fraction randomFrac(Fraction min, Fraction max, int a, int b) {
//
//	int deno = min.getDeno()*max.getDeno();
//	int numeMin = min.getNume()*max.getDeno();
//	int numeMax = min.getDeno()*max.getNume();
//	int nume = (int)randomInt(numeMin, numeMax);
//	Fraction frac(nume, deno);
//	return frac;
//}

string newFracExp(int oprNum, int oprType[], int min, int max, Fraction &result) {

	if (!min) {
		min++;
	}
	string exp;
	Fraction minFrac(1, max), maxFrac(1, 1);
	/*const char opr[5] = { '+','-','*','/','^' };*/
	char opr[5];
	int oprMax = 0, i, j = 0;

	for (i = 0; i < 5; i++) {
		if (oprType[i]) {
			switch (i)
			{
			case 0: opr[j++] = '+'; break;
			case 1: opr[j++] = '-'; break;
			case 2: opr[j++] = '*'; break;
			case 3: opr[j++] = '/'; break;
			case 4: opr[j++] = '^'; break;
			default:
				break;
			}
		}
	}
	oprMax = j - 1;
	/*switch (oprType) {
	case 0:oprMax = 1; break;
	case 1:oprMax = 3; break;
	case 2:oprMax = 4; break;
	}*/
	Fraction leftVal, rightVal, tempVal;
	int lastOpr, curOpr;
	int powerNum = 2;
	int tempIndex = 2;

	leftVal = randomFrac(minFrac, maxFrac, min, max);
	if ((leftVal.getDeno() > 20 || leftVal.getNume()> 20) && opr[oprMax] == '^' && oprMax > 0)
		oprMax--;
	curOpr = (int)randomInt(0, oprMax);
	oprNum--;

	switch (opr[curOpr]) {
	case '+':
		rightVal = randomFrac(minFrac, maxFrac, min, max);
		break;
	case '-': //leftVal = randomInt(min, max);
		rightVal = randomFrac(minFrac, leftVal, min, max);
		break;
	case '*': //leftVal = randomInt(min, max);
		rightVal = randomFrac(minFrac, maxFrac, min, max);
		break;
	case '/': //leftVal = randomInt(min, max);
		rightVal = randomFrac(minFrac, maxFrac, min, max);
		break;
	case '^':
		tempIndex = (int)randomInt(2, 3);
		rightVal = Fraction(tempIndex, 1);
		powerNum--;
		break;
	}

	leftVal.simplify();
	rightVal.simplify();
	if (opr[curOpr] == '^' && leftVal.getDeno() != 1) {
		exp = "( " + leftVal.display() + " )" + opr[curOpr] + rightVal.display();
	}
	else {
		exp = leftVal.display() + " " + opr[curOpr] + " " + rightVal.display();
	}
	tempVal = operate(leftVal, opr[curOpr], rightVal);

	while (oprNum) {
		lastOpr = curOpr;
		if ((powerNum == 0 || tempVal.getDeno() > 20 || tempVal.getNume()>20) && opr[oprMax] == '^' && oprMax > 0)
			oprMax--;
		curOpr = (int)randomInt(0, oprMax);
		oprNum--;
		if (opr[curOpr] == '^') {
			powerNum--;
			leftVal = tempVal;
			tempIndex = (int)randomInt(2, 3);
			rightVal = Fraction(tempIndex, 1);
			exp = "( " + exp + " )" + opr[curOpr] + "" + rightVal.display();
			tempVal = operate(leftVal, opr[curOpr], rightVal);
		}
		else {
			if (opr[curOpr] == '/' && tempVal == Fraction(0, 1) || opr[curOpr] == '-' && tempVal >= maxFrac || randomInt(0, 1) && (!(opr[curOpr] == '-' && tempVal < minFrac))) {
				leftVal = tempVal;
				opr[curOpr] == '-' ? rightVal = randomFrac(minFrac, leftVal < maxFrac ? leftVal : maxFrac, min, max) : rightVal = randomFrac(minFrac, maxFrac, min, max);

				leftVal.simplify();
				rightVal.simplify();
				if ((opr[curOpr] == '*' || opr[curOpr] == '/') && (opr[lastOpr] == '+' || opr[lastOpr] == '-')) {
					exp = "( " + exp + " ) " + opr[curOpr] + " " + rightVal.display();
					tempVal = operate(leftVal, opr[curOpr], rightVal);
				}
				else {
					exp = exp + " " + opr[curOpr] + " " + rightVal.display();
					tempVal = operate(leftVal, opr[curOpr], rightVal);
				}
			}
			else {
				rightVal = tempVal;
				opr[curOpr] == '-' ? leftVal = randomFrac(rightVal > minFrac ? rightVal : minFrac, maxFrac, min, max) : leftVal = randomFrac(minFrac, maxFrac, min, max);

				leftVal.simplify();
				rightVal.simplify();
				if ((opr[curOpr] == '*' || opr[curOpr] == '/') && (opr[lastOpr] == '+' || opr[lastOpr] == '-') || opr[curOpr] == '-' && (opr[lastOpr] == '+' || opr[lastOpr] == '-') || opr[curOpr] == '/' && (opr[lastOpr] == '*' || opr[lastOpr] == '/')) {
					exp = leftVal.display() + " " + opr[curOpr] + " ( " + exp + " )";
					tempVal = operate(leftVal, opr[curOpr], rightVal);
				}
				else {
					exp = leftVal.display() + " " + opr[curOpr] + " " + exp;
					tempVal = operate(leftVal, opr[curOpr], rightVal);
				}
			}
		}

	}
	result = tempVal;
	return exp;
}

void arithmetic::setExpNum(int n) {

	try {
		expNum = n;
		if (expNum < 0) {
			throw "The number of expressions must be an integer and at least one.";
		}
	}
	catch (const char* msg) {
		cout << msg << endl;
		setExpNum(0);
	}
}

void arithmetic::setExpType(int n) {
	try {
		expType = n;
		if (expType > 2 || expType < 0) {
			throw "Type of expressions must be an integer among 0, 1 and 2.";
		}
	}
	catch (const char* msg) {
		cout << msg << endl;
		expType = 0;
		setExpNum(0);
	}

}

void arithmetic::setOprNum(int n) {
	try {
		oprNum = n;
		if (oprNum <= 0) {
			throw "The number of operators must be an integer larger than zero.";
		}
	}
	catch (const char* msg) {
		cout << msg << endl;
		oprNum = 1;
		setExpNum(0);
	}

}

//void arithmetic::setOprType(int n) {
//	try {
//		oprType = n;
//		if (oprType < 0 || oprType>2) {
//			throw "Type of operators must be an integer among 0,1 and 2.";
//		}
//	}
//	catch (const char* msg) {
//		cout << msg << endl;
//		oprType = 0;
//		setExpNum(0);
//	}
//}

void arithmetic::setOprAdd(int n) {
	try {
		oprType[0] = n;
		if (n != 0 && n != 1 ) {
			throw "The parameter of function seOprAdd must be zero or one.";
		}
	}
	catch (const char* msg) {
		cout << msg << endl;
		oprType[0] = 1;
		setExpNum(0);
	}
}

void arithmetic::setOprSub(int n) {
	try {
		oprType[1] = n;
		if (n != 0 && n != 1) {
			throw "The parameter of function seOprSub must be zero or one.";
		}
	}
	catch (const char* msg) {
		cout << msg << endl;
		oprType[1] = 1;
		setExpNum(0);
	}
}

void arithmetic::setOprMul(int n) {
	try {
		oprType[2] = n;
		if (n != 0 && n != 1) {
			throw "The parameter of function seOprMul must be zero or one.";
		}
	}
	catch (const char* msg) {
		cout << msg << endl;
		oprType[2] = 0;
		setExpNum(0);
	}
}

void arithmetic::setOprDiv(int n) {
	try {
		oprType[3] = n;
		if (n != 0 && n != 1) {
			throw "The parameter of function seOprDiv must be zero or one.";
		}
	}
	catch (const char* msg) {
		cout << msg << endl;
		oprType[3] = 0;
		setExpNum(0);
	}
}

void arithmetic::setOprPow(int n) {
	try {
		oprType[4] = n;
		if (n != 0 && n != 1) {
			throw "The parameter of function seOprPow must be zero or one.";
		}
	}
	catch (const char* msg) {
		cout << msg << endl;
		oprType[4] = 0;
		setExpNum(0);
	}
}

void arithmetic::setOprAll(int a, int s, int m, int d, int p) {
	try {
		oprType[0] = a;
		oprType[1] = s;
		oprType[2] = m;
		oprType[3] = d;
		oprType[4] = p;
  		if (a != 0 && a != 1 || s != 0 && s != 1 || m != 0 && m != 1 || d != 0 && d != 1 || p != 0 && p != 1) {
			throw "The parameters of function seOprAll must be zero or one.";
		}
	}
	catch (const char* msg) {
		cout << msg << endl;
		oprType[0] = 0;
		oprType[1] = 0;
		oprType[2] = 1;
		oprType[3] = 1;
		oprType[4] = 1;
		setExpNum(0);
	}
}

void arithmetic::setOprByStr(string s) {
	int i, flag = 0;
	int len = (int)s.length();
	for (i = 0; i < len; i++) {
		try {
			switch (s[i]) {
			case '+': oprType[0] = 1; break;
			case '-': oprType[1] = 1; break;
			case '*': oprType[2] = 1; break;
			case '/': oprType[3] = 1; break;
			case '^': oprType[4] = 1; break;
			default: flag = 1;
			}
			if (flag) {
				throw "The string should contains '+','-','*','/','^' only.";
			}
		}
		catch (const char* msg) {
			cout << msg << endl;
			oprType[0] = 1;
			oprType[1] = 1;
			oprType[2] = 0;
			oprType[3] = 0;
			oprType[4] = 0;
			setExpNum(0);
		}
	}
}


void arithmetic::setBounds(int min, int max) {
	try {
		this->min = min;
		this->max = max;
		if (min < 0 || max < min || min == 0 && max == 0) {
			throw "The ceiling bound must be larger than floor bound and both are positive.";
		}
	}
	catch (const char* msg) {
		cout << msg << endl;
		this->min = 0;
		this->max = 10;
		setExpNum(0);
	}

}

void arithmetic::setAccuracy(int n) {

	try {
		accuracy = n;
		if (n < 0 || n > 6)throw"Acurracy index must be a non-negative integer less than or equal to 6.";
	}
	catch (const char* msg) {
		cout << msg << endl;
		n = 2;
		setExpNum(0);
	}

}

int arithmetic::getExpNum() {
	return expNum;
}

string* arithmetic::getExpSet() {
	string* expSet = new string[expNum];
	for (int i = 0; i<expNum; i++) {
		expSet[i] = p[i].exp;
	}
	return expSet;
}

string* arithmetic::getAnsSet() {
	string* ansSet = new string[expNum];
	for (int i = 0; i<expNum; i++) {
		ansSet[i] = p[i].ans;
	}
	return ansSet;
}

//string arithmetic::getAnswer(string exp) {
//	return bank[exp];
//}

void arithmetic::generate()
{
	srand((unsigned)(time(NULL)));

	if (expNum < 1 || expType < 0 || expType > 2 || oprNum < 1 || min < 0 || min > max || accuracy < 0)
		exit(0);

	int i;
	int resultI;
	double resultD;
	Fraction resultF;
	char result[100];
	p = new expNode[expNum];
	for (i = 0; i < expNum; i++)
	{
		switch (expType)
		{
		case 0:p[i].exp = newExactDivExp(oprNum, oprType, min, max, resultI);
			p[i].ans = to_string(resultI);
			break;
		case 1:p[i].exp = newExp(oprNum, oprType, min, max, resultD);
			switch (accuracy) {
			case 0: sprintf(result, "%.0lf", resultD); break;
			case 1: sprintf(result, "%.1lf", resultD); break;
			case 2: sprintf(result, "%.2lf", resultD); break;
			case 3: sprintf(result, "%.3lf", resultD); break;
			case 4: sprintf(result, "%.4lf", resultD); break;
			case 5: sprintf(result, "%.5lf", resultD); break;
			default: sprintf(result, "%lf", resultD);
			}
			p[i].ans = result;
			break;
		case 2:p[i].exp = newFracExp(oprNum, oprType, min, max, resultF);
			p[i].ans = resultF.display();
			break;
		default :
			break;
		}
	}
}



