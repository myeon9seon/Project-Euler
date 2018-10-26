#include <iostream>
#include <cmath>
#include "Time.h"
using namespace std;

typedef struct _fraction { int denom, num; } Fraction;
const int MAX = 2;

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

int delIndexNum(int num, int index) {
	int len = countDigit(num);
	int isDel = 0, result = 0;
	for (int i = 0; i < len; i++) {
		if (len - i == index) {
			isDel = 1;
			continue;
		}
		result += getDigitNum(num, len - i) * (int)pow(10, i - isDel);
	}
	return result;
}

Fraction divideCorrectly(Fraction fr) {
	for (int div = 2; div < fr.denom; div++) {
		if (fr.denom % div == 0 && fr.num % div == 0) {
			fr.denom /= div;
			fr.num /= div;
			div = 2; // 나누어 떨어지면 다시 2부터 약분 가능한지 확인
		}
	}
	return fr;
}

double divideIncorrectly(Fraction fr, Fraction frIndex) {
	fr.denom = delIndexNum(fr.denom, frIndex.denom);
	fr.num = delIndexNum(fr.num, frIndex.num);
	return (double)fr.num / (double)fr.denom;
}

void divideFraction(Fraction *dest, Fraction fr) {
	Fraction frIndex;
	double oriResult = (double)fr.num / (double)fr.denom;
	if (fr.denom % 10 == 0 && fr.num % 10 == 0)
		return; // 진부한 방법으로 약분 가능하다면 계산하지 않음
	for (frIndex.denom = 1; frIndex.denom <= MAX; frIndex.denom++) {
		for (frIndex.num = 1; frIndex.num <= MAX; frIndex.num++) {
			// 해당 인덱스(자릿수)가 약분 가능하다면 이상한 방법으로 약분
			if (getDigitNum(fr.denom, frIndex.denom) == getDigitNum(fr.num, frIndex.num)) {
				double curiousResult = divideIncorrectly(fr, frIndex);
				if (curiousResult == oriResult) {
					dest->denom *= fr.denom;
					dest->num *= fr.num;
				}
			}
		}
	}
}

int main() {
	Time t;
	Fraction fr, result = { 1, 1 };
	for (fr.denom = (int)pow(10, MAX - 1); countDigit(fr.denom) <= MAX; fr.denom++)
		for (fr.num = (int)pow(10, MAX - 1); fr.num < fr.denom; fr.num++)
			divideFraction(&result, fr);
	cout << divideCorrectly(result).denom << endl;
	t.printRunTime();
}
