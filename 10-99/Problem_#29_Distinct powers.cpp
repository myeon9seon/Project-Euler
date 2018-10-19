// execution time: 3467ms

#include <iostream>
#include "Time.h"
using namespace std;

const int MAX = 100;

bool isSame(bool *prime, int *a, int *b) {
	for (int i = 0; i <= MAX; i++)
		if (prime[i])
			if (a[i] != b[i])
				return false;
	return true;
}

void setPrime(bool *dest) {
	dest[2] = true;
	for (int i = 3; i <= MAX; i++) {
		bool isPrime = true;
		for (int k = 2; k * k <= i; k++) {
			if (i % k == 0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime)
			dest[i] = true;
	}
}

void primeFactorization(int *dest, bool *prime, int base, int exponent) {
	for (int num = 2; num <= MAX; num++) {
		if (prime[num]) { // num이라는 소수로
			if (base % num == 0) { // 나누어 떨어진다면
				dest[num] += exponent; // num은 base의 소인수, 지수 법칙 적용
				base /= num; num = 1; // 계산을 계속하기 위한 초기화
				if (base == 1) return; // 더 이상 계산할 수 없다면 함수 종료
			}
		}
	}
}

int main() {
	Time t;
	bool isPrime[MAX + 1] = { false, };
	bool isDuplicate[(MAX - 1) * (MAX - 1)] = { false, };
	int **numOfPrimeFactor = new int*[(MAX - 1) * (MAX - 1)];
	int resultCount = 0, result = 0;
	// 초기화
	setPrime(isPrime);
	for (int i = 0; i < (MAX - 1) * (MAX - 1); i++) {
		numOfPrimeFactor[i] = new int[MAX + 1];
		for (int k = 0; k <= MAX; k++)
			numOfPrimeFactor[i][k] = 0;
	}
	// 계산
	for (int a = 2; a <= MAX; a++)
		for (int b = 2; b <= MAX; b++)
			primeFactorization(numOfPrimeFactor[resultCount++], isPrime, a, b);
	// 중복되는 결과를 정답에서 제외시킴
	result = resultCount;
	for (int i = 0; i < resultCount; i++) {
		for (int k = i + 1; k < resultCount; k++) {
			if (!isDuplicate[k] && isSame(isPrime, numOfPrimeFactor[i], numOfPrimeFactor[k])) {
				result--;
				isDuplicate[k] = true;
			}
		}
	}			
	// 출력
	cout << result << endl;
	t.printRunTime();
	for (int i = 0; i < (MAX - 1) * (MAX - 1); i++)
		delete[] numOfPrimeFactor[i];
	delete[] numOfPrimeFactor;
}
