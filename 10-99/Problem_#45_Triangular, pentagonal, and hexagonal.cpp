// execution time: 11ms

#include <iostream>
#include <cmath>
#include "Time.h"
using namespace std;

#define TRIANGLE(n) n * (n + 1) / 2

bool isInteger(double num) {
	double decimal = num - (__int64)num;
	if (decimal <= 0)
		return true;
	else
		return false;
}

bool isPentagon(__int64 num) {
	double index = (sqrt(24 * num + 1) + 1) / 6;
	if (isInteger(index))
		return true;
	else
		return false;
}

bool isHexagon(__int64 num) {
	double index = (sqrt(8 * num + 1) + 1) / 4;
	if (isInteger(index))
		return true;
	else
		return false;
}

int main() {
	Time t;
	const __int64 MAX = 10000000;
	int resultCount = 0;
	for (__int64 index = 2; index <= MAX; index++) {
		__int64 tri = TRIANGLE(index);
		if (isPentagon(tri) && isHexagon(tri)) {
			if (resultCount++ > 0) {
				cout << tri << endl;
				break;
			}
		}
	}
	t.printRunTime();
}
