// execution time: 1648ms

#include <iostream>
#include <cmath>
#include "Time.h"
using namespace std;

const int EXPONENT = 5;

void setSquareNum(int *dest) {
	for (int i = 0; i <= 9; i++)
		dest[i] = (int)pow(i, EXPONENT);
}

int countDigit(int num) {
	int count = 0;
	while (num > 0) {
		num /= 10;
		count++;
	}
	return count;
}

int getDigitNum(int num, int index) {
	for (int count = countDigit(num) - index; count > 0; count--)
		num /= 10;
	return num % 10;
}

int main() {
	Time t;
	int squareNum[10];
	int result = 0;
	// 초기화
	setSquareNum(squareNum);
	// 계산
	for (int num = 2; num < pow(10, EXPONENT + 1); num++) {
		int sum = 0;
		for (int base = 1; base <= countDigit(num); base++)
			sum += squareNum[getDigitNum(num, base)];
		if (sum == num)
			result += num;
	}
	// 출력
	cout << result << endl;
	t.printRunTime();
}
