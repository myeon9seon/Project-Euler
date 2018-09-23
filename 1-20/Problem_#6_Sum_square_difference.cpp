#include <iostream>
using namespace std;

int pow(int base, int exponent) {
	return exponent ? base * pow(base, exponent - 1) : 1;
}

int sumOfSquare(int num) {
	int sum = 0;
	for (int i = 1; i <= num; i++)
		sum += pow(i, 2);
	return sum;
}

int squareOfSum(int num) {
	int sum = 0;
	for (int i = 1; i <= num; i++)
		sum += i;
	return pow(sum, 2);
}

int main(void) {
	cout << squareOfSum(100) - sumOfSquare(100) << endl;
}
