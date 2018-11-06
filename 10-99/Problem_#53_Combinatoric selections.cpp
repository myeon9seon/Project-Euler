// execution time: 56ms

#include <iostream>
#include <cmath>
#include "Time.h"
using namespace std;

void setPrimeFactorization(int *divCount, int num) {
	for (int div = 2; div <= num; div++) {
		if (num % div == 0) {
			divCount[div]++;
			num /= div;
			div = 1;
		}
	}
}

bool isOverCombination(int n, int r) {
	const int OVER = 1000000;
	int *divNum = new int[n + 1];
	int *divDenom = new int[n + 1];
	int combination = 1;

	for (int i = 0; i <= n; i++) {
		divNum[i] = 0;
		divDenom[i] = 0;
	}
	for (int i = 0; i < r; i++) {
		setPrimeFactorization(divNum, n - i);
		setPrimeFactorization(divDenom, r - i);
	}
	for (int i = 2; i <= n; i++)
		divNum[i] -= divDenom[i];
	for (int i = n; i > 1; i--) {
		if (divNum[i] > 0) {
			combination *= (int)pow(i, divNum[i]);
			if (combination > OVER) {
				delete[] divNum, divDenom;
				return true;
			}
		}
	}
	delete[] divNum, divDenom;
	return false;
}

int getOverCombiCount() {
	const int MAX_N = 100;
	int count = 0;
	for (int n = 1; n <= MAX_N; n++)
		for (int r = 1; r <= n; r++)
			if (isOverCombination(n, r))
				count++;
	return count;
}

int main() {
	Time t;
	cout << getOverCombiCount() << endl;
	t.printRunTime();
}
