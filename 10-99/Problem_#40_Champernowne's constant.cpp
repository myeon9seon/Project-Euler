// Solution 1: 문자열 이어붙이기
// execution time: 125170ms

#include <iostream>
#include <cstring>
#include <cmath>
#include "Time.h"
using namespace std;

const int MAX = 1000000;

int charToInt(char ch) {
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

int main() {
	Time t;
	char *strNum = new char[MAX + 10];
	int count = 0, result = 1;
	strNum[0] = '\0';
	for (int num = 1; strlen(strNum) <= MAX; num++)
		sprintf(strNum, "%s%d", strNum, num);
	for (int i = 1; i <= MAX; i++) {
		if (i == (int)pow(10, count)) {
			result *= charToInt(strNum[i - 1]);
			count++;
		}
	}
	cout << result << endl;
	t.printRunTime();
	delete[] strNum;
}

// Solution 2: 자릿수를 활용한 계산
// execution time: 38ms

#include <iostream>
#include <cmath>
#include "Time.h"
using namespace std;

const int MAX = 1000000;

int getDigitCount(int num) {
	int count = 0;
	while (num > 0) {
		num /= 10;
		count++;
	}
	return count;
}

int getDigitNum(int num, int index) {
	for (int count = getDigitCount(num) - index; count > 0; count--)
		num /= 10;
	return num % 10;
}

int main() {
	Time t;
	int decimalCount = 0, resultCount = 0, result = 1;
	for (int num = 1; decimalCount <= MAX; num++) {
		decimalCount += getDigitCount(num);
		if (decimalCount >= (int)pow(10, resultCount))
			result *= getDigitNum(num, getDigitCount(num) - (decimalCount - (int)pow(10, resultCount++)));
	}
	cout << result << endl;
	t.printRunTime();
}
