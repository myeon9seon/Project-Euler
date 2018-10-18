// Solution 1
// execution time: 156967ms

#include <iostream>
#include "Time.h"
using namespace std;

const int MAX_NUM = 1000;
const int MAX_LEN = 2000;

bool isSame(int *a, int *b, int len) {
	for (int i = 0; i < len; i++)
		if (a[i] != b[i])
			return false;
	return true;
}

bool isReciprocal(int *num, int *subset, int len, int index) {
	int adjust = 2; // subset이 몇 번 반복되어야 순환 마디로 간주할 것인지
	int cycle = 0;
	for (int i = index + len; num[i] != -1 && i < MAX_LEN - len; i += len) {
		if (isSame(&num[i], subset, len))
			cycle++;
		else
			return false;
		if (cycle == adjust)
			return true;
	}
	return true;
}

int countReciprocalCycle(int *num) {
	int *subset, *target;
	int len = 0; // 소수점 아래 자리의 개수
	for (len = 0; num[len] != -1 && len < MAX_LEN; len++);
	// 부분 집합이 가질 수 있는 원소의 개수
	for (int subCnt = 1; subCnt <= len; subCnt++) {
		subset = new int[subCnt]; target = new int[subCnt];
		for (int i = 0; i < len - subCnt; i++) {
			// 부분 집합 초기화
			for (int k = 0; k < subCnt; k++)
				subset[k] = num[i + k];
			// 자신을 제외하고(k = i + subCnt) 같은 원소를 가지지 않으며(k += subCnt)
			// 내용(isSame)과 크기(subCnt)가 같은 부분 집합이 연속되는지 확인 
			for (int k = i + subCnt; k < len; k += subCnt) {
				// 비교할 부분 집합 초기화
				for (int m = 0; m < subCnt; m++)
					target[m] = num[k + m];
				// 같은 부분 집합이 연속된다면 부분 집합의 크기(순환 마디의 길이)를 리턴
				if (isSame(subset, target, subCnt))
					if (isReciprocal(num, subset, subCnt, k)) {
						delete[] subset, target;
						return subCnt;
					}
					else
						break;
				else
					break;
			}
		}
	}
	delete[] subset, target;
	return 0;
}

int main() {
	Time t;
	int *decimalPlace = new int[MAX_LEN];
	int cycleLen, maxLen = 0, result;
	for (int num = 2; num <= MAX_NUM; num++) {
		int rest = 1;
		// 초기화
		for (int i = 0; i < MAX_LEN; i++)
			decimalPlace[i] = -1;
		for (int i = 0; i < MAX_LEN; i++) {
			decimalPlace[i] = (rest * 10) / num; // num은 단위 분수의 분모
			rest = (rest * 10) % num;
			if (rest == 0) break; // 나누어 떨어지면 루프 탈출
		}
		cycleLen = countReciprocalCycle(decimalPlace);
		if (cycleLen > maxLen) {
			maxLen = cycleLen;
			result = num;
		}
	}
	cout << result << endl;
	t.printRunTime();
}
