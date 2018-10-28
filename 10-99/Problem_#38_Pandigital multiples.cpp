// execution time: 37ms

#include <iostream>
#include <cstdio>
#include <cstring>
#include "Time.h"
using namespace std;

const int MAX = 9;

int getDigitCount(int num) {
	int count = 0;
	while (num > 0) {
		num /= 10;
		count++;
	}
	return count;
}

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

int strToInt(char *str) {
	int result = 0;
	int len = strlen(str);
	for (int i = 0; str[i] != 0; i++)
		result += charToInt(str[i]) * (int)pow(10, len - (i + 1));
	return result;
}

bool isPandigital(char *strNum) {
	bool isExist[MAX + 1] = { true, false, };
	for (int i = 0; i < MAX; i++)
		isExist[charToInt(strNum[i])] = true;
	for (int i = 1; i <= MAX; i++)
		if (!isExist[i])
			return false;
	return true;
}

int main() {
	Time t;
	int max = 0;
	for (int num = 1; getDigitCount(num) <= MAX / 2; num++) {
		char strNum[MAX + 1] = { "\0" };
		for (int i = 1; ; i++) {
			sprintf(strNum, "%s%d", strNum, num * i);
			if (strlen(strNum) == MAX)
				if (isPandigital(strNum))
					if (strToInt(strNum) > max)
						max = strToInt(strNum);
			if (strlen(strNum) >= MAX)
				break;
		}
	}
	cout << max << endl;
	t.printRunTime();
}
