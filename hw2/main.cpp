#include"arithmetic.h"

int main() {

	arithmetic test;
	test.setExpNum(20);
	test.setExpType(2);
	test.setBounds(5, 10);
	test.setOprNum(4);
	test.setOprType(2);
	test.setAccuracy(4);

	test.generate();

	string* expSet;
	string* ansSet;
	expSet = test.getExpSet();
	ansSet = test.getAnsSet();
	for (int i = 0; i < 20; i++) {
		cout << i << " "<< expSet[i] << " = " << ansSet[i] << endl;
	}

	system("pause");
}