// execution time: 155350ms

#include <iostream>
#include "Time.h"
using namespace std;

const int MAX = 1000000;

void setPrime(bool *dest) {
	for (int i = 0; i <= MAX; i++)
		dest[i] = true;
	for (int i = 2; i * i <= MAX; i++)
		if (dest[i])
			for (int k = i * i; k <= MAX; k += i)
				dest[k] = false;
}

int main() {
	Time t;
	bool *isPrime = new bool[MAX + 1];
	int *primeNum, primeCnt = 0;
	int maxLen = 0, maxSum = 0;
	// 초기화
	setPrime(isPrime);
	int *temp = new int[MAX + 1];
	for (int i = 2; i <= MAX; i++)
		if (isPrime[i])
			temp[primeCnt++] = i;
	primeNum = new int[primeCnt];
	for (int i = 0; i < primeCnt; i++)
		primeNum[i] = temp[i];
	delete[] temp;
	// 계산
	for (int len = 2; len < primeCnt; len++) {
		for (int i = 0; i < primeCnt - len; i++) {
			int sum = 0;
			for (int k = 0; k < len; k++) {
				sum += primeNum[i + k];
				if (sum > MAX) break;
			}
			if (sum <= MAX && isPrime[sum]) { // 소수의 합이 소수라면
				if (len > maxLen) {
					maxLen = len;
					maxSum = sum;
				}
			}
		}
	}
	// 출력
	cout << maxSum << endl;
	t.printRunTime();
	// 해제
	delete[] isPrime;
	delete[] primeNum;
}
