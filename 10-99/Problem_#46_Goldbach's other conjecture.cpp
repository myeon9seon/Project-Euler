// execution time: 1175ms

#include <iostream>
#include <cmath>
#include "Time.h"
using namespace std;

void setPrime(bool *dest, int range) {
	for (int i = 0; i <= range; i++)
		dest[i] = true;
	for (int i = 2; i * i <= range; i++)
		if (dest[i])
			for (int k = i * i; k <= range; k += i)
				dest[k] = false;
}

bool isGoldbachConjecture(bool *isPrime, int num) {
	for (int prime = 2; prime <= num - 2; prime++)
		if (isPrime[prime])
			for (int base = 1; prime + 2 * (int)pow(base, 2) <= num; base++)
				if (prime + 2 * (int)pow(base, 2) == num)
					return true;
	return false;
}

int main() {
	Time t;
	const int MAX = 10000;
	bool isPrime[MAX + 1];

	setPrime(isPrime, MAX);
	for (int num = 2; num <= MAX; num++) {
		if (num % 2 == 1 && !isPrime[num]) {
			if (!isGoldbachConjecture(isPrime, num)) {
				cout << num << endl;
				t.printRunTime();
				return 0;
			}
		}
	}
}
