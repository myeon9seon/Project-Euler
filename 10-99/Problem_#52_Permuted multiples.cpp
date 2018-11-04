// execution time: 11ms

#include <iostream>
#include "Time.h"
using namespace std;

#define MULTIPLE(num, count) num * count
typedef struct _range { int min, max; } Range;

bool isPermuted(int target, int num) {
	int count[10] = { 0, };
	for (int i = 0; target > 0; i++) {
		count[target % 10]++;
		count[num % 10]++;
		target /= 10;
		num /= 10;
	}
	for (int i = 0; i <= 9; i++)
		if (count[i] != 0 && count[i] != 2)
			return false;
	return true;
}

void printPermutedMultiple() {
	const Range NUM = { 100000, 300000 };
	const Range COUNT = { 2, 6 };

	for (int num = NUM.min; num <= NUM.max; num++) {
		for (int count = COUNT.min; count <= COUNT.max; count++) {
			if (!isPermuted(num, MULTIPLE(num, count)))
				break;
			else if (count == COUNT.max) {
				cout << num << endl;
				return;
			}
		}
	}
}

int main() {
	Time t;
	printPermutedMultiple();
	t.printRunTime();
}
