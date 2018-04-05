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
	map<char, int> ch = { { '+', 1}, { '-', 1}, { '*', 3},{ '/', 3},{ '(', 0 },{ '#', -1 } };
	return ch[c1] >= ch[c2] ? 1 : 0;
}

int isoperator(char c)
{
	if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' || c == '#')
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
	}
	return e;
}

void Calculate(string s)
{
	int i = 0, k = 0;
	stack<char> Opr;
	stack<double> Num;
	char ch, c;
	double a, b, temp;

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
	printf("result: %.4lf\n", Num.top());
}
int main() {
	string exp;
	cout << "input:" << endl;
	getline(cin, exp);
	//cin >> exp;
	Calculate(exp);
	getchar();
	return 0;
}


