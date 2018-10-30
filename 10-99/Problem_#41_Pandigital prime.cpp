// execution time: 8176ms

#include <iostream>
#include <cmath>
#include "Time.h"
using namespace std;

const int PAN_LEN = 7;

int getDigitCount(int num) {
	int count = 0;
	while (num > 0) {
		num /= 10;
		count++;
	}
	return count;
}

void setPrime(bool *dest) {
	int len = (int)pow(10, PAN_LEN);
	for (int i = 0; i < len; i++)
		dest[i] = true;
	dest[0] = false, dest[1] = false;
	for (int i = 2; i * i <= len - 1; i++)
		if (dest[i])
			for (int k = i * i; k <= len - 1; k += i)
				dest[k] = false;
}

bool isPandigital(int num) {
	int temp = num;
	int len = getDigitCount(num);
	bool *isExist = new bool[len + 1];

	for (int i = 1; i <= len; i++)
		isExist[i] = false;
	for (int i = 1; i <= len; i++) {
		int indexNum = temp % 10;
		if (indexNum <= len)
			isExist[indexNum] = true;
		else {
			delete[] isExist;
			return false;
		}
		temp /= 10;
	}
	for (int i = 1; i <= len; i++)  {
		if (!isExist[i]) {
			delete[] isExist;
			return false;
		}
	}
	delete[] isExist;
	return true;
}

int main() {
	Time t;
	bool *isPrime = new bool[(int)pow(10, PAN_LEN)];
	int max = 0;

	setPrime(isPrime);
	for (int num = 1; getDigitCount(num) <= PAN_LEN; num++)
		if (isPandigital(num) && isPrime[num])
			if (num > max)
				max = num;
	cout << max << endl;

	t.printRunTime();
	delete[] isPrime;
}
