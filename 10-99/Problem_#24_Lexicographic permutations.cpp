// Solution 1
// execution time: 5918ms

// 지금 당장은 모르겠는데 RESULT - 2 해야 정답이 나옴 다음에 이유 꼭 알아보고
// 가능하면 다른 방법으로도 짤 수 있게 해보기

#include <iostream>
#include "Time.h"
using namespace std;

const int MAX = 9;
const int RESULT = 1000000;

int factorial(int num) {
	return (num > 1) ? num * factorial(num - 1) : 1;
}

bool isLargerThanMAX(int num) {
	if (num > MAX)
		return true;
	else
		return false;
}

bool isExistSameNum(int index, int *target) {
	if (target[index] > MAX)
		return false;
	for (int i = 0; i <= MAX; i++)
		if (i != index && target[index] == target[i])
			return true;
	return false;
}

void increase(int *dest, int index) {
	if (index > MAX)
		return;

	dest[MAX - index]++;
	
	if(isLargerThanMAX(dest[MAX - index]))
		increase(dest, index + 1);
	if(isExistSameNum(MAX - index, dest))
		increase(dest, index);
}

void lexicographicOrder(int **dest) {
	// 초기 값
	for (int i = 0; i <= MAX; i++)
		dest[0][i] = i;
	
	for (int cnt = 0; cnt < RESULT; cnt++) {
		bool isOn[MAX + 1] = { false, };
		increase(dest[cnt], 0);
		// 현재 순열에 있는 수는 true, 없는 수는 false를 가짐
		for (int i = 0; i <= MAX; i++) {
			if (dest[cnt][i] > MAX)
				dest[cnt][i] = -1;
			else
				isOn[dest[cnt][i]] = true;
		}
		// MAX보다 커진 수를 현재 순열에 없는 수로 교체
		for (int i = 0; i <= MAX; i++) {
			if (dest[cnt][i] == -1) {
				for (int k = 0; k <= MAX; k++) {
					if (!isOn[k]) {
						dest[cnt][i] = k;
						isOn[k] = true;
						break;
					}
				}
			}
		}
		// 계산을 위해 다음 배열에 저장
		for (int i = 0; cnt < factorial(MAX + 1) - 1 && i <= MAX; i++)
			dest[cnt + 1][i] = dest[cnt][i];
	}
}

int main() {
	Time t;
	int **num = new int*[factorial(MAX + 1)];
	for (int i = 0; i < factorial(MAX + 1); i++)
		num[i] = new int[MAX + 1];
	
	lexicographicOrder(num);

	for (int i = 0; i <= MAX; i++)
		cout << num[RESULT - 2][i];
	cout << endl;

	t.printRunTime();
	for (int i = 0; i < factorial(MAX + 1); i++)
		delete[] num[i];
	delete[] num;
}
