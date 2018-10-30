// execution time: 5ms

#include <iostream>
#include "Time.h"
using namespace std;

enum Pence { _1, _2, _5, _10, _20, _50, _100, _200 };
const int PRICE[8] = { 1, 2, 5, 10, 20, 50, 100, 200 };

int get1Pence(int *pence) {
	int sum = 0;
	for (int i = Pence::_5; i <= Pence::_200; i++)
		sum += pence[i] * PRICE[i];
	return 200 - sum;
}

void sumHigherPence(int *pence) {
	for (int i = Pence::_5; i < Pence::_200; i++) {
		if (pence[i] * PRICE[i] >= 200) {
			pence[i + 1]++;
			for (int k = Pence::_2; k <= i; k++)
				pence[k] = 0;
			pence[Pence::_1] = get1Pence(pence);
			return;
		}
	}
	for (int i = Pence::_5; i < Pence::_200; i++) {
		if (pence[i] != 0) {
			int k = i;
			do {
				pence[k + 1]++;
				pence[k++] = 0;
			} while (get1Pence(pence) < 0);
			pence[Pence::_1] = get1Pence(pence);
			return;
		}
	}
}

void make2Pound(int *pence) {
	if (pence[Pence::_1] < 2) {
		if (get1Pence(pence) <= 0)
			sumHigherPence(pence);
		else { // 5펜스 교환
			pence[Pence::_5]++;
			pence[Pence::_2] = 0;
			pence[Pence::_1] = get1Pence(pence);
		}
	}
	else { // 2펜스 교환
		pence[Pence::_2]++;
		pence[Pence::_1] -= 2;
	}
}

int main() {
	Time t;
	int pence[8] = { 200, 0, };
	int result = 1;
	while (pence[Pence::_200] < 1) {
		make2Pound(pence);
		result++;
	}
	cout << result << endl;
	t.printRunTime();
}
