// Solution 1

#include <iostream>
#include <cmath>
using namespace std;

int main(void) {
	__int64 Num          = 600851475143;
	int     LargestPrime = 0;
	bool    IsPrime      = false;

	for (int i = 2; i <= sqrt(Num); i++) {
		// is a divisor?
		if (Num % i == 0) {
			// is a prime number?
			for (int j = 2; j <= sqrt(i); j++) {
				if (i % j == 0) {
					IsPrime = false;
					break;
				}
				IsPrime = true;
			}
			if (IsPrime)
				LargestPrime = i;
		}
	}
	cout << LargestPrime << endl;
}

// Solution 2

#include <iostream>
using namespace std;

int main(void) {
	__int64 Num     = 600851475143;
	bool    IsPrime = false;

	while (!IsPrime) {
		// prime factorization
		for (int i = 2; i < Num; i++) {
			if (Num % i == 0) {
				Num /= i;
				IsPrime = false;
				break;
			}
			IsPrime = true;
		}
	}
	cout << Num << endl;
}
