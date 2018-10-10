// execution time: 1367ms

#include <iostream>
#include "Time.h"
using namespace std;

int sumOfDivisor(int num) {
	int sum = 1;
	for (int i = 2; i * i <= num; i++) {
		if (num % i == 0) {
			if (i * i == num)
				sum += i;
			else
				sum += i + (num / i);
		}
	}
	if (num < 2)
		return 0;
	return sum;
}

bool isAmicable(int *sum, int a, int b) {
	if (sum[a - 1] == b && sum[b - 1] == a)
		return true;
	return false;
}

int main() {
	Time t;
	const int MAX = 10000;
	int *divSum = new int[MAX];
	int sum = 0;
	// MAX 이하 자연수의 약수 합을 배열에 저장
	// (약수 합을 여러 번 계산하지 않기 위함임)
	for (int i = 1; i <= MAX; i++)
		divSum[i - 1] = sumOfDivisor(i);
	// MAX 이하 자연수 a, b가 친화쌍이면 sum에 a, b를 더함
	for (int i = 2; i <= MAX; i++) {
		for (int k = i + 1; k <= MAX; k++) {
			if (isAmicable(divSum, i, k))
				sum += i + k;
		}
	}
	cout << sum << endl;
	t.printRunTime();
	delete[] divSum;
}
