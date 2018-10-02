// Solution 1
// execution time: 11241ms

#include <iostream>
#include <ctime>
using namespace std;

__int64 collatzSequence(__int64 num) {
	if (num % 2 == 0)
		return num / 2;
	else
		return (3 * num) + 1;
}

int main(void) {
	clock_t begin = clock(), end;
	int maxCount = 0, maxNum = 0;

	for (int num = 1; num <= 1000000; num++) {
		__int64 collatz = num;
		int count = 0;
		while (collatz != 1) {
			collatz = collatzSequence(collatz);
			count++;
		}
		if (count > maxCount) {
			maxCount = count;
			maxNum = num;
		}
	}
	cout << maxNum << endl;

	end = clock();
	cout << "execution time: " << end - begin << "ms" << endl;
}
