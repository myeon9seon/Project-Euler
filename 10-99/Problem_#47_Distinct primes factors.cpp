// execution time: 30134ms

#include <iostream>
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

int getPrimeDivisorCount(bool *prime, int num) {
	int oriNum = num;
	int *primeFactor = new int[oriNum + 1];
	int primeCount = 0;

	for (int i = 2; i <= oriNum; i++)
		primeFactor[i] = 0;
	for (int div = 2; div < num; div++) {
		if (prime[div]) {
			if (num % div == 0) {
				num /= div;
				primeFactor[div]++;
				div = 1;
			}
		}
	}
	primeFactor[num]++;
	for (int i = 2; i <= oriNum; i++)
		if (primeFactor[i] > 0)
			primeCount++;
	delete[] primeFactor;
	return primeCount;
}

int main() {
	Time t;
	const int PRIME_DIV_COUNT = 4;
	const int NUM_RANGE_MIN = 100000;
	const int NUM_RANGE_MAX = 1000000;
	bool isPrime[NUM_RANGE_MAX + 1];
	int continuityCount = 0;

	setPrime(isPrime, NUM_RANGE_MAX);
	for (int num = NUM_RANGE_MIN; num <= NUM_RANGE_MAX; num++) {
		int primeCount = getPrimeDivisorCount(isPrime, num);
		if (primeCount == PRIME_DIV_COUNT) {
			continuityCount++;
			if (continuityCount == PRIME_DIV_COUNT) {
				cout << num - (PRIME_DIV_COUNT - 1) << endl;
				break;
			}
		}
		else
			continuityCount = 0;
	}
	t.printRunTime();
}
