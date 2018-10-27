// execution time: 105487ms

#include <iostream>
#include "Time.h"
using namespace std;

int factorial(int num) {
	if (num == 0) return 1;
	return num * factorial(num - 1);
}

int getDigitCount(int num) {
	int count = 0;
	while (num > 0) {
		num /= 10;
		count++;
	}
	return count;
}

int getDigitNum(int num, int index) {
	for (int count = getDigitCount(num) - index; count > 0; count--)
		num /= 10;
	return num % 10;
}

int getMaxRange() {
	for (int count = 1; ; count++) {
		int num = factorial(9) * count;
		if (num == getDigitCount(num))
			return count;
	}
	return -1;
}

int sumFactorial() {
	const int MAX = getMaxRange();
	int factorialNum[10], result = 0;

	for (int i = 0; i <= 9; i++)
		factorialNum[i] = factorial(i);
	for (int num = 10; num <= MAX; num++) {
		int sum = 0;
		for (int digit = 1; digit <= getDigitCount(num); digit++)
			sum += factorialNum[getDigitNum(num, digit)];
		if (sum == num)
			result += num;
	}
	return result;
}

int main() {
	Time t;
	cout << sumFactorial() << endl;
	t.printRunTime();
}
