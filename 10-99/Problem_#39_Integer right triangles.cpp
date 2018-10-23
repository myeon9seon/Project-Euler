// execution time: 3564ms

#include <iostream>
#include "Time.h"
using namespace std;

const int MAX = 1000;

bool isRightAngled(int a, int b, int c) {
	if (a * a + b * b == c * c)
		return true;
	else
		return false;
}

int main() {
	Time t;
	int triLen[MAX + 1] = { 0, };
	int maxCnt = 0, maxLen = 0;
	for (int a = 1; a <= MAX; a++) {
		for (int b = 1; b <= MAX; b++) {
			if (b > a) { // 두 번 이상 계산하지 않기 위함
				for (int c = 1; c <= MAX; c++) {
					int len = a + b + c;
					if (len > MAX) break;
					if (isRightAngled(a, b, c))
						triLen[len]++;
				}
			}
		}
	}
	for (int i = 0; i < MAX; i++) {
		if (triLen[i] > maxCnt) {
			maxCnt = triLen[i];
			maxLen = i;
		}
	}
	cout << maxLen << endl;
	t.printRunTime();
}
