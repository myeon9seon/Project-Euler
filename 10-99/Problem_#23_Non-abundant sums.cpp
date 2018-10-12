// execution time: 47ms

#include <iostream>
#include "Time.h"
using namespace std;

bool isAbundantNumber(int num) {
	int sum = 1;
	for (int i = 2; i * i <= num; i++) {
		if (num % i == 0) {
			if (i * i == num)
				sum += i;
			else
				sum += i + (num / i);
		}
	}
	if (sum > num)
		return true;
	else
		return false;
}

int main() {
	Time t;
	const int MAX = 28123;
	int abundantNum[MAX], abundantCount = 0;
	bool isDuplicate[MAX] = { false, };
	int sumOfAll = 0, abundantSum = 0;

	for (int i = 1; i <= MAX; i++) {
		if (isAbundantNumber(i))
			abundantNum[abundantCount++] = i;
		sumOfAll += i;
	}
	for (int i = 0; i < abundantCount; i++) {
		for (int k = i; k < abundantCount; k++) {
			int sum = abundantNum[i] + abundantNum[k];
			if (sum > MAX)
				break; // 두 초과수의 합으로 나타낼 수 있는 MAX 이하 자연수만 더함
			else {
				if (!isDuplicate[sum - 1]) { // 이미 더한 수(true)는 더하지 않음
					abundantSum += sum;
					isDuplicate[sum - 1] = true;
				}
			}
		}
	}
	cout << sumOfAll - abundantSum << endl;
	t.printRunTime();
}
