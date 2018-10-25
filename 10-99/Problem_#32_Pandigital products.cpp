// execution time: 112ms

#include <iostream>
#include <cmath>
#include <cstdio>
#include "Time.h"
using namespace std;

typedef struct _equation { int a, b, c; } Equation;
const int MAX = 9;

int countDigit(int num) {
	int count = 0;
	while (num > 0) {
		num /= 10;
		count++;
	}
	return count;
}

int getCharToInt(char ch) {
	switch (ch) {
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	default: return -1;
	}
}

// eqDigit이 가능한 자릿수 조합일 때 true를 리턴
bool isAvailableDigit(Equation eqDigit) {
	Equation eqMin, eqMax;
	int minDigit, maxDigit;

	eqMin = { 0, 0, 0 };
	eqMax = { 0, 0, 0 };
	for (int i = 0; i < eqDigit.a; i++) {
		eqMin.a += 1 * (int)pow(10, i);
		eqMax.a += 9 * (int)pow(10, i);
	}
	for (int i = 0; i < eqDigit.b; i++) {
		eqMin.b += 1 * (int)pow(10, i);
		eqMax.b += 9 * (int)pow(10, i);
	}
	eqMin.c = eqMin.a * eqMin.b;
	eqMax.c = eqMax.a * eqMax.b;
	minDigit = countDigit(eqMin.c);
	maxDigit = countDigit(eqMax.c);

	if (eqDigit.c >= minDigit && eqDigit.c <= maxDigit)
		return true;
	else
		return false;
}

// 계산 가능한 자릿수 조합을 dest에 저장
int setEquationDigit(Equation *dest) {
	Equation eq;
	int eqCount = 0;

	for (eq.a = 1; eq.a < MAX; eq.a++) {
		for (eq.b = eq.a; MAX - (eq.a + eq.b) > 0; eq.b++) {
			eq.c = MAX - (eq.a + eq.b);
			if (isAvailableDigit(eq))
				dest[eqCount++] = eq;
		}
	}
	return eqCount;
}

// a * b = c가 팬디지털 곱셈식이면 true를 리턴
bool isPandigital(int a, int b, int c) {
	char strNum[MAX * 3];
	bool isExist[MAX + 1] = { true, false, }; // 1~MAX만 사용

	sprintf(strNum, "%d%d%d", a, b, c);
	for (int i = 0; strNum[i] != '\0'; i++)
		if (getCharToInt(strNum[i]) <= MAX)
			isExist[getCharToInt(strNum[i])] = true;

	for (int i = 1; i <= MAX; i++)
		if (!isExist[i])
			return false;
	return true;
}

// 계산 가능한 조합의 팬디지털 곱셈식 결과를 dest에 저장
int setPandigitalNum(int *dest, Equation *eq, int eqCount) {
	int panCount = 0;
	for (int i = 0; i < eqCount; i++) {
		for (int a = (int)pow(10, eq[i].a - 1); countDigit(a) <= eq[i].a; a++) {
			for (int b = (int)pow(10, eq[i].b - 1); countDigit(b) <= eq[i].b; b++) {
				int c = a * b;
				if (countDigit(c) == eq[i].c)
					if (isPandigital(a, b, c))
						dest[panCount++] = c;
			}
		}
	}
	return panCount;
}

void printPandigitalSum(int *pan, int panCount) {
	int sum = 0;
	for (int i = 0; i < panCount; i++)
		sum += pan[i];
	for (int i = 0; i < panCount; i++)
		for (int k = i + 1; k < panCount; k++)
			if (pan[i] == pan[k])
				sum -= pan[k]; // 중복되는 결과 제외
	cout << sum << endl;
}

int main() {
	Time t;
	Equation eqDigit[(MAX * MAX + MAX) / 2];
	int panNum[(MAX * MAX + MAX) / 2];
	int eqCount, panCount;

	eqCount = setEquationDigit(eqDigit);
	panCount = setPandigitalNum(panNum, eqDigit, eqCount);
	printPandigitalSum(panNum, panCount);
	t.printRunTime();
}
