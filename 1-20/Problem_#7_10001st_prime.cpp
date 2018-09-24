// execution time: 104ms

#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

const int MAX = 10001;

int main(void) {
	clock_t begin = clock(), end;

	for (int i = 2, cnt = 1; cnt <= MAX; i++) {
		bool isPrime = true;
		for (int k = 2; k <= sqrt(i); k++) {
			if (i % k == 0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime) {
			if (cnt == MAX)
				cout << i << endl;
			cnt++;
		}
	}

	end = clock();
	cout << "execution time: " << end - begin << "ms" << endl;
}
