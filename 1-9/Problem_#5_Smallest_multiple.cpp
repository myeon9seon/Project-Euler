// Solution 1: simply calculating
// execution time: 3356ms

#include <iostream>
#include <ctime>
using namespace std;

const int MAX = 20;

int main(void) {
	clock_t begin = clock(), end;
	bool IsDivided = false;
  
	for (int i = MAX; ; i++) {
		for (int j = 1; j <= MAX; j++) {
			if (i % j != 0) {
				IsDivided = false;
				break;
			}
			IsDivided = true;
		}
		if (IsDivided) {
			cout << i << endl;
			end = clock();
			cout << "execution time: " << end - begin << "ms" << endl;
			return 0;
		}
	}
}

// Solution 2: using prime numbers
// execution time: 1ms

#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

const int MAX = 20;

int main(void) {
	clock_t begin = clock(), end;
	int  PrimeNum[MAX] = { 2, };
	int  *NumOfPrime, *PrimeFactor;
	int  PrimeCnt = 0, Result = 1;
	bool IsPrime  = true;
	// search for prime numbers from 2 to MAX
	for (int i = 2; i <= MAX; i++) {
		for (int k = 0; PrimeNum[k] <= sqrt(i); k++) {
			if (i % PrimeNum[k] == 0) {
				IsPrime = false;
				break;
			}
			IsPrime = true;
		}
		if (IsPrime)
			PrimeNum[PrimeCnt++] = i;
	}
	// initialization
	NumOfPrime = new int[PrimeCnt];
	memset(NumOfPrime, 0, sizeof(int)*PrimeCnt);
	PrimeFactor = new int[PrimeCnt];

	for (int i = 2; i <= MAX; i++) {
		int num = i;
		memset(PrimeFactor, 0, sizeof(int)*PrimeCnt);
		// prime factorization
		for (int k = 0; PrimeNum[k] <= num; ) {
			if (num % PrimeNum[k] == 0) {
				PrimeFactor[k]++;
				num /= PrimeNum[k];
			}
			else k++;
		}
		// save the number of each prime factors
		for (int k = 0; k < PrimeCnt; k++) {
			if (PrimeFactor[k] > NumOfPrime[k])
				NumOfPrime[k] = PrimeFactor[k];
		}
	}
	// calculate a least common multiple
	for (int i = 0; i < PrimeCnt; i++)
		Result *= pow(PrimeNum[i], NumOfPrime[i]);
	cout << Result << endl;
	// delete a pointer
	delete[] NumOfPrime;
	delete[] PrimeFactor;

	end = clock();
	cout << "execution time: " << end - begin << "ms" << endl;
}

// Solution 3: using Euclidean algorithm
// execution time: 1ms

#include <iostream>
#include <ctime>
using namespace std;

const int MAX = 20;

int GCD(int a, int b) {
	return b ? GCD(b, a % b) : a;
}

// parameters must have __int64 type because of overflow
int LCM(__int64 a, __int64 b) {
	return (a * b / GCD(a, b));
}

int main(void) {
	clock_t begin = clock(), end;
	int result = 1;
	for (int i = 2; i <= MAX; i++)
		result = LCM(result, i);
	cout << result << endl;

	end = clock();
	cout << "execution time: " << end - begin << "ms" << endl;
}
