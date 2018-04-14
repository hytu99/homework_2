#include"arithmetic.h"

int main() {

	arithmetic test;
	test.setExpNum(20);
	test.setExpType(1);
	test.setBounds(1, 20);
	test.setOprNum(4);
	//test.setOprType(2);
	//test.setOprAdd(0);
	//test.setOprSub(0);
	//test.setOprMul(0);
	//test.setOprDiv(0);
	//test.setOprPow(1);
	//test.setOprAll(1, 1, 1, 1, 1);
	test.setOprByStr("/");
	test.setAccuracy(2);

	test.generate();

	string* expSet;
	string* ansSet;
	expSet = test.getExpSet();
	ansSet = test.getAnsSet();
	for (int i = 0; i < test.getExpNum(); i++) {
		cout << i+1 << "    "<< expSet[i] << " = " << ansSet[i] << endl;
	}

 	system("pause");
}