// Solution 1
// execution time: 6136ms

#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

int main(void) {
	clock_t begin = clock(), end;
	unsigned __int64 sum = 0;
	
	for (int num = 2; num <= 2000000; num++) {
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

// Solution 2: divison by primes
// execution time: 1252ms

#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

int main(void) {
	clock_t begin = clock(), end;
	int prime[200000] = { 2, };
	int count = 1;
	unsigned __int64 sum = 0;
	
	for (int num = 2; num <= 2000000; num++) {
		bool IsPrime = true;
		for (int i = 0; prime[i] <= sqrt(num); i++) {
			if (num % prime[i] == 0) {
				IsPrime = false;
				break;
			}
		}
		if (IsPrime) {
			prime[count++] = num;
			sum += num;
		}
	}
	cout << sum << endl;

	end = clock();
	cout << "execution time: " << end - begin << "ms" << endl;
}

// Solution 3: Sieve of Eratosthenes
// execution time: 30ms

#include <iostream>
#include <ctime>
using namespace std;

int main(void) {
	clock_t begin = clock(), end;
	const int MAX = 2000000;
	bool             *prime;
	unsigned __int64 sum    = 0;
	// init
	prime = new bool[MAX + 1];
	for (int i = 2; i <= MAX; i++)
		prime[i] = true;
	// Sieve of Eratosthenes
	for (int i = 2; i * i <= MAX; i++) {
		if (prime[i])
			for (int k = i * i; k <= MAX; k += i)
				prime[k] = false;
	}
	// sum
	for (int i = 2; i <= MAX; i++)
		if (prime[i])
			sum += i;
	cout << sum << endl;
	delete[] prime;

	end = clock();
	cout << "execution time: " << end - begin << "ms" << endl;
}
