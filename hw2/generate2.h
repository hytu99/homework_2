#pragma once
#include<iostream>
#include<math.h>
#include<random>
#include<ctime>
#include<string>
#include"calc.h"
#define epsilon 1e-8
using namespace std;

double randomInt(int min, int max);
string newExp(int oprNum, int oprType, int min, int max, double &result);
Fraction randomFrac(Fraction min, Fraction max);
string newFracExp(int oprNum, int oprType, Fraction &result);