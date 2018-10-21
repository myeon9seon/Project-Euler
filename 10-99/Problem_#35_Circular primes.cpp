// execution time: 299ms

#include <iostream>
#include <cmath>
#include "Time.h"
using namespace std;

const int MAX = 1000000;

void setPrime(bool *dest) {
	for (int i = 0; i <= MAX; i++)
		dest[i] = true;
	for (int i = 2; i * i <= MAX; i++) {
		if (dest[i])
			for (int k = i * i; k <= MAX; k += i)
				dest[k] = false;
	}
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

int getNumFromArr(int *arr, int digit) {
	int sum = 0;
	for (int i = 0; i < digit; i++)
		sum += arr[i] * (int)pow(10, digit - (i + 1));
	return sum;
}

bool isCircularPrime(bool *prime, int num) {
	int digitCount = countDigit(num);
	int *circle = new int[digitCount];
	for (int i = 0; i < digitCount; i++)
		circle[i] = getDigitNum(num, i + 1);
	for (int i = 0; i < digitCount; i++) {
		if (!prime[getNumFromArr(circle, digitCount)]) {
			delete[] circle;
			return false;
		}
		// 각 자릿수를 앞으로 한 칸씩 옮김
		int temp = circle[0];
		for (int k = 0; k <= digitCount - 1; k++)
			circle[k] = circle[k + 1];
		circle[digitCount - 1] = temp;
	}
	delete[] circle;
	return true;
}

int main() {
	Time t;
	bool *isPrime = new bool[MAX + 1];
	int resultCount = 0;
	// 초기화
	setPrime(isPrime);
	// 계산
	for (int i = 2; i <= MAX; i++)
		if (isPrime[i])
			if (isCircularPrime(isPrime, i))
				resultCount++;
	// 출력
	cout << resultCount << endl;
	t.printRunTime();
	delete[] isPrime;
}
