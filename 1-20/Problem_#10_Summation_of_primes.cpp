// Solution 1
// execution time: 6136ms

#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

int main(void) {
	clock_t begin = clock(), end;
	const int MAX = 2000000;
	unsigned __int64 sum = 0;
	
	for (int num = 2; num <= MAX; num++) {
		bool IsPrime = true;
		for (int i = 2; i <= sqrt(num); i++) {
			if (num % i == 0) {
				IsPrime = false;
				break;
			}
		}
		if (IsPrime) sum += num;
	}
	cout << sum << endl;

	end = clock();
	cout << "execution time: " << end - begin << "ms" << endl;
}
