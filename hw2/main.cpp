#include"arithmetic.h"

int main() {

	arithmetic test;
	test.setExpNum(20);
	test.setExpType(0);
	test.setBounds(1, 15);
	test.setOprNum(2);
	test.setOprType(1);
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