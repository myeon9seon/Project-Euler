// execution time: 21ms

#include <iostream>
#include "Time.h"
using namespace std;

typedef struct _quadratic { int a, b, n = 0; } Quadratic;

const int MAX = 999;
const int PRIME_MAX = 20000;

void setPrime(bool *dest) {
	dest[2] = true;
	for (int i = 3; i < PRIME_MAX; i++) {
		bool isPrime = true;
		for (int k = 2; k * k <= i; k++) {
			if (i % k == 0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime)
			dest[i] = true;
	}
}

int main() {
	Time t;
	Quadratic q, max;
	bool isPrime[PRIME_MAX] = { false, };

	setPrime(isPrime);
	for (q.a = -1 * MAX; q.a <= MAX; q.a++) {
		for (q.b = -1 * MAX; q.b <= MAX; q.b++) {
			for (q.n = 0; ; q.n++) {
				int result = q.n * (q.n + q.a) + q.b;
				if (result < 2) { // 결과 값이 2보다 작으면 소수가 아님
					if (q.n > max.n)
						max = q;
					break;
				}
				else if (!isPrime[result]) { // 2와 같거나 큰 경우에만 소수인지 확인
					if (q.n > max.n)
						max = q;
					break;
				}
			}
		}
	}
	cout << max.a * max.b << endl;
	t.printRunTime();
}
