#include <iostream>
#include <cstring>
using namespace std;

typedef struct _LetterOfNum { int _1_19[19], _20_90[8], _100, and; } Letter;

void setEngNumLen(Letter *num) {
	char str1_19[19][10] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
		"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
	char str20_90[8][8] = { "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };
	char str_100[8] = { "hundred" };
	char str_and[4] = { "and" };

	for (int i = 0; i < 19; i++) {
		num->_1_19[i] = strlen(str1_19[i]);
		if (i < 9)
			num->_20_90[i] = strlen(str20_90[i]);
	}
	num->_100 = strlen(str_100);
	num->and = strlen(str_and);
}

int main(void) {
	Letter num;
	int sum = 0;

	setEngNumLen(&num);
	for (int i = 1; i <= 1000; i++) {
		// 1~19
		if (i >= 1 && i <= 19)
			sum += num._1_19[i - 1];
		// 20~99
		if (i >= 20 && i <= 99) {
			sum += num._20_90[(i / 10) - 2];
			if (i % 10 != 0)
				sum += num._1_19[(i % 10) - 1];
		}
		// 100~999
		if (i >= 100 && i <= 999) {
			sum += num._1_19[(i / 100) - 1];
			sum += num._100;
			// NN1~N19
			if (i % 100 >= 1 && i % 100 <= 19) {
				sum += num.and;
				sum += num._1_19[(i % 100) - 1];
			}
			// N20~N99
			if (i % 100 >= 20 && i % 100 <= 99) {
				sum += num.and;
				sum += num._20_90[((i / 10) % 10) - 2];
				if (i % 10 != 0)
					sum += num._1_19[(i % 10) - 1];
			}
		}
		// 1000
		if (i == 1000)
			sum += strlen("onethousand");
	}
	cout << sum << endl;
}
