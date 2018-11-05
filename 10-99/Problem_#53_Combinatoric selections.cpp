// 미완

#include <iostream>
#include "Time.h"
using namespace std;

int getCombination(int n, int r) {
	int *numerator = new int[r];
	int *denominator = new int[r];
	int num = 1, denom = 1;
	
	for (int i = 0; i < r; i++) {
		numerator[i] = n - i;
		denominator[i] = r - i;
	}
	for (int i = r - 1; i >= 0; i--) {
		for (int k = r - 1; k >= 0; k--) {
			if (numerator[i] % denominator[i] == 0) {
				numerator[i] /= denominator[i];
				denominator[i] = 1;
			}
		}
	}
	for (int i = 0; i < r; i++) {
		num *= numerator[i];
		denom *= denominator[i];
	}
	delete[] numerator, denominator;
	return num / denom;
}

int main() {
	Time t;
	int count = 0;
	for (int n = 1; n <= 100; n++) {
		for (int r = 1; r <= n / 2; r++) {
			int combination = getCombination(n, r);
			if (combination >= 1000000)
				count++;
		}
	}
	cout << count << endl;
	t.printRunTime();
}
