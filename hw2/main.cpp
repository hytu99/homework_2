#include"arithmetic.h"

int main() {

	arithmetic test;
	test.setExpNum(20);
	test.setExpType(1);
	test.setBounds(1, 20);
	test.setOprNum(4);
	test.setOprType(2);
	test.setAccuracy(5);

	test.generate();

	string* expSet;
	string* ansSet;
	expSet = test.getExpSet();
	ansSet = test.getAnsSet();
	for (int i = 0; i < test.getExpNum(); i++) {
		cout << i << " "<< expSet[i] << " = " << ansSet[i] << endl;
	}

	//cout << calc_double("abc") <<endl;

 	system("pause");
}