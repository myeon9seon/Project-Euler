// execution time: 376ms

#include <iostream>
#include "Time.h"
#include "LargeNumber.h"
using namespace std;

void reverseNumber(Number& dest, const Number& num) {
	int len = num.getLength() - 1;
	for (int i = len; i >= 0; i--)
		dest.setNumber(i, num.getNumber(len - i));
}

bool isPalindrome(const Number& num) {
	int len = num.getLength() - 1;
	for (int i = 0; i <= len / 2; i++)
		if (num.getNumber(i) != num.getNumber(len - i))
			return false;
	return true;
}

int countLychrelNumber() {
	const int MAX = 10000;
	const int NUM_LEN = 100;
	Calculator base(NUM_LEN, 0);
	Number reverse(NUM_LEN, 0);
	int lychrelCount = MAX - 9;

	for (int num = 10; num <= MAX; num++) {
		base.setNumber(num);
		for (int repeat = 1; repeat < 50; repeat++) {
			reverseNumber(reverse, base.getNumber());
			base.sum(reverse);
			if (isPalindrome(base.getNumber())) {
				lychrelCount--;
				break;
			}
		}
	}
	return lychrelCount;
}

int main() {
	Time t;
	cout << countLychrelNumber() << endl;
	t.printRunTime();
}
