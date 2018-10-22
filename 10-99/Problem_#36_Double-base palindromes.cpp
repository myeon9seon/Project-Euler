// execution time: 52342ms

#include <iostream>
#include <cmath>
#include "Time.h"

const int MAX = 1000000;

int countDigit(int num) {
	int count = 0;
	while (num > 0) {
		num /= 10;
		count++;
	}
	return count;
}

int countBinaryDigit(int num) {
	int digit;
	for (digit = 0; pow(2, digit) <= num; digit++);
	return digit;
}

int getDigitNum(int num, int index) {
	for (int count = countDigit(num) - index; count > 0; count--)
		num /= 10;
	return num % 10;
}

void convertDecimalToBinary(int *dest, int num) {
	int len = countBinaryDigit(num);
	for (int digit = 0; num >= 1; digit++) {
		if (num % 2)
			dest[(len - 1) - digit] = 1;
		else
			dest[(len - 1) - digit] = 0;
		num /= 2;
	}
}

void setDecimalNum(int **dest) {
	for (int i = 0; i < MAX; i++)
		for (int k = 0; k < countDigit(MAX); k++)
			dest[i][k] = -1;
	for (int num = 1; num <= MAX; num++)
		for (int digit = 1; digit <= countDigit(num); digit++)
			dest[num - 1][digit - 1] = getDigitNum(num, digit);
}

void setBinaryNum(int **dest) {
	for (int i = 0; i < MAX; i++)
		for (int k = 0; k < countBinaryDigit(MAX); k++)
			dest[i][k] = -1;
	for (int num = 1; num <= MAX; num++)
		convertDecimalToBinary(dest[num - 1], num);
}

bool isPalindrome(int *target, int len) {
	for (int i = 0; i < len / 2; i++)
		if (target[i] != target[(len - 1) - i])
			return false;
	return true;
}

int main() {
	Time t;
	int **decimalNum = new int*[MAX];
	int **binaryNum = new int*[MAX];
	int sum = 0;
	// 초기화
	int decimalDigit = countDigit(MAX);
	int binaryDigit = countBinaryDigit(MAX);
	for (int i = 0; i < MAX; i++) {
		decimalNum[i] = new int[decimalDigit];
		binaryNum[i] = new int[binaryDigit];
	}
	setDecimalNum(decimalNum);
	setBinaryNum(binaryNum);
	// 계산
	for (int num = 1; num <= MAX; num++)
		if (isPalindrome(decimalNum[num - 1], countDigit(num)))
			if (isPalindrome(binaryNum[num - 1], countBinaryDigit(num)))
				sum += num;
	// 출력
	cout << sum << endl;
	t.printRunTime();
	// 해제
	for (int i = 0; i < MAX; i++) {
		delete[] decimalNum[i];
		delete[] binaryNum[i];
	}
	delete[] decimalNum;
	delete[] binaryNum;
}
