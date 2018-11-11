// 미완 메모리를 너무 많이 먹어서 계산 실패

#include <iostream>
#include "Time.h"
#include "LargeNumber.h"
using namespace std;

void printSelfPowersSum() {
	const int MAX = 1000;
	const int NUM_LEN = 1000000;
	Calculator base(NUM_LEN, 0), result(NUM_LEN, 0);
	Number num(NUM_LEN, 0);

	for (int i = 1; i <= MAX; i++) {
		base.setNumber(i);
		num.init(i);
		for (int k = 1; k < i; k++)
			base.multiply(num);
		result.sum(base.getNumber());
	}
	result.print(); cout << endl;
}

int main() {
	Time t;
	printSelfPowersSum();
	t.printRunTime();
}
