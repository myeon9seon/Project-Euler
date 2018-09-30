// execution time: 401ms

#include <iostream>
#include <ctime>
using namespace std;

int main(void) {
	clock_t begin = clock(), end;

	for (int i = 1; ; i++) {
		int tri = 0, divCount = 0;
		// triangular numbers
		for (int k = 1; k <= i; k++)
			tri += k;
		// search for divisors
		for (int k = 1; k * k <= tri; k++) {
			if (tri % k == 0)
				divCount += 2;
			if (k * k == tri)
				divCount--;
		}
		if (divCount >= 500) {
			cout << tri << endl;
			break;
		}
	}

	end = clock();
	cout << "execution time: " << end - begin << "ms" << endl;
}
