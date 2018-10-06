#include <iostream>
#include <cstring>
using namespace std;

namespace EngNum { enum { HUNDRED = 8 }; }

void getEngNumLen(int *num1_19, int *num20_100, int *num_and) {
	char str1_19[19][10] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
		"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
	char str20_100[9][8] = { "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety", "hundred" };
	char str_and[4] = { "and" };

	for (int i = 0; i < 19; i++) {
		num1_19[i] = strlen(str1_19[i]);
		if (i < 9)
			num20_100[i] = strlen(str20_100[i]);
	}
	*num_and = strlen(str_and);
}

int main(void) {
	int num1_19[19], num20_100[9], num_and;
	int sum = 0;

	getEngNumLen(num1_19, num20_100, &num_and);
	for (int i = 1; i <= 1000; i++) {
		// 1~19
		if (i >= 1 && i <= 19)
			sum += num1_19[i - 1];
		// 20~99
		if (i >= 20 && i <= 99) {
			sum += num20_100[(i / 10) - 2];
			if (i % 10 != 0)
				sum += num1_19[(i % 10) - 1];
		}
		// 100~999
		if (i >= 100 && i <= 999) {
			sum += num1_19[(i / 100) - 1];
			sum += num20_100[EngNum::HUNDRED];
			// NN1~N19
			if (i % 100 >= 1 && i % 100 <= 19) {
				sum += num_and;
				sum += num1_19[(i % 100) - 1];
			}
			// N20~N99
			if (i % 100 >= 20 && i % 100 <= 99) {
				sum += num_and;
				sum += num20_100[((i / 10) % 10) - 2];
				if (i % 10 != 0)
					sum += num1_19[(i % 10) - 1];
			}
		}
		// 1000
		if (i == 1000)
			sum += strlen("onethousand");
	}
	cout << sum << endl;
}
