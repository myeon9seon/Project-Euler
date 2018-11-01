// Solution 1
// execution time: 5357ms

#include <iostream>
#include "Time.h"
using namespace std;

#define PENTAGON(n) n * (3 * n - 1) / 2

const int MIN = 1000;
const int MAX = 10000;

bool isPentagon(int num) {
	for (int i = 1; PENTAGON(i) <= num; i++)
		if (PENTAGON(i) == num)
			return true;
	return false;
}

int main() {
	Time t;
	for (int i = MIN; i <= MAX; i++) {
		for (int k = i + 1; k <= MAX; k++) {
			if (isPentagon(PENTAGON(k) + PENTAGON(i)) && isPentagon(PENTAGON(k) - PENTAGON(i))) {
				cout << PENTAGON(k) - PENTAGON(i) << endl;
				t.printRunTime();
				exit(EXIT_SUCCESS);
			}
		}
	}
}
