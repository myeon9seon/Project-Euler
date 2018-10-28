// execution time: 72ms

#include <iostream>
#include <ctime>
#include "Time.h"
using namespace std;

const int MAX = 1000000;

void setPrime(bool *dest) {
	for (int i = 0; i <= MAX; i++)
		dest[i] = true;
	dest[0] = false, dest[1] = false;
	for (int i = 2; i * i <= MAX; i++) {
		if (dest[i])
			for (int k = i * i; k <= MAX; k += i)
				dest[k] = false;
	}
}

int getDigitCount(int num) {
	int count = 0;
	while (num > 0) {
		num /= 10;
		count++;
	}
	return count;
}

bool isTruncatable(bool *prime, int num) {
	int temp = num;
	if (!prime[num]) // num이 소수가 아니라면 해당하지 않음
		return false;
	while (num > 9) { // 오른쪽에서부터 하나씩 지움
		num /= 10;
		if (!prime[num])
			return false;
	}
	num = temp;
	while (num > 9) { // 왼쪽에서부터 하나씩 지움
		num %= (int)pow(10, getDigitCount(num) - 1);
		if (!prime[num])
			return false;
	}
	return true;
}

int main() {
	Time t;
	bool *isPrime = new bool[MAX + 1];
	int sum = 0;
	setPrime(isPrime);
	for (int num = 10; num <= MAX; num++)
		if (isTruncatable(isPrime, num))
			sum += num;
	cout << sum << endl;
	t.printRunTime();
	delete[] isPrime;
}
