#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stack>
#include<string>
#include<iostream>
#include<map>
using namespace std;

int preop(char c1, char c2)
{
	map<char, int> ch = {{'+', 1}, {'-', 1}, {'*', 3}, {'/', 3}, {'^', 4}, {'(', 0}, {'#', -1}};
	return ch[c1] >= ch[c2] ? 1 : 0;
}

int isoperator(char c)
{
	if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' || c == '#' || c == '^' )
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

//*********************************************

class Fraction
{
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

void Fraction::simplify()
{
	int m, n, r, temp;
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

Fraction operator^(const Fraction &c1, const int &c2)
{
	Fraction t;
	t.nume = (int)pow(c1.nume, c2);
	t.deno = (int)pow(c1.deno, c2);
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
	if ((c1_nume - c2_nume)*common_deno>0) return true;
	return false;
}

bool operator<(const Fraction &c1, const Fraction &c2)
{
	int c1_nume, c2_nume, common_deno;
	c1_nume = c1.nume*c2.deno;
	c2_nume = c2.nume*c1.deno;
	common_deno = c1.deno*c2.deno;
	if ((c1_nume - c2_nume)*common_deno<0) return true;
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
	//case '^': e = pow(a, b); break;
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

//int main() {
//	string exp;
//	cout << "input:" << endl;
//	getline(cin, exp);
//	//cin >> exp;
//	Calculate(exp);
//	getchar();
//	return 0;
//}


