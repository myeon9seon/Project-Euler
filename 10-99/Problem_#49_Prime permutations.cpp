// execution time: 168ms

#include <iostream>
#include "Time.h"
using namespace std;

const int MAX = 10000;

void setPrime(bool *dest) {
	for (int i = 0; i < MAX; i++)
		dest[i] = true;
	for (int i = 2; i * i < MAX; i++)
		if (dest[i])
			for (int k = i * i; k < MAX; k += i)
				dest[k] = false;
}

int getDigitCount(int num) {
	int count = 0;
	while (num > 0) {
		num /= 10;
		count++;
	}
	return count;
}

bool isPermuted(int base, int comp) {
	int baseCount[10] = { 0, };
	int compCount[10] = { 0, };
	int baseDigit = getDigitCount(base);

	for (int i = 0; i < baseDigit; i++) {
		baseCount[base % 10]++;
		compCount[comp % 10]++;
		base /= 10;
		comp /= 10;
	}
	for (int i = 0; i < 10; i++)
		if (baseCount[i] != compCount[i])
			return false;
	return true;
}

int main() {
	Time t;
	bool isPrime[MAX];

	setPrime(isPrime);
	for (int num = 1000; num < MAX; num++) {
		if (isPrime[num]) {
			int permuteNum[MAX], permuteCount = 0;
			// 소수이면서 num과 자릿수를 바꿔서 만들 수 있는 순열 i를 permuteNum에 저장
			for (int i = num + 1; i < MAX; i++)
				if (isPrime[i] && isPermuted(num, i))
					permuteNum[permuteCount++] = i;
			// permuteNum에서 둘째 항과 셋째 항을 골라 num(첫항)과 등차수열을 이룬다면 세 항을 나란히 출력
			for (int secTerm = 0; secTerm < permuteCount; secTerm++)
				for (int thirdTerm = secTerm + 1; thirdTerm < permuteCount; thirdTerm++)
					if (permuteNum[thirdTerm] - permuteNum[secTerm] == permuteNum[secTerm] - num)
						cout << num << permuteNum[secTerm] << permuteNum[thirdTerm] << endl;
		}
	}
	t.printRunTime();
}
