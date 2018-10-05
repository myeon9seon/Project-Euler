#include <iostream>
using namespace std;

int numOfDigit(int *num) {
	int count = 0;
	while (num[count] != -1)
		count++;
	return count;
}

int main(void) {
	const int MAX = 1000;
	int num[MAX] = { 2, -1, };
	int sum = 0;

	for (int exponent = 2; exponent <= MAX; exponent++) {
		int digit = numOfDigit(num);
		int carry = 0;

		for (int i = 0; i < digit; i++) {
			num[i] = (num[i] * 2) + carry;

			if (num[i] >= 10) {
				carry = num[i] / 10;
				num[i] %= 10;

				if (i == digit - 1) {
					num[i + 1] = carry;
					num[i + 2] = -1;
				}
			}
			else
				carry = 0;
		}
	}
	for (int i = 0; i < numOfDigit(num); i++)
		sum += num[i];
	cout << sum << endl;
}
