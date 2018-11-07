// 미완 3분 51초

#include <iostream>
#include "Time.h"
using namespace std;

const int INT_ARR_LEN = 10000;

void initIntArr(int *arr) {
	for (int i = 0; i < INT_ARR_LEN; i++)
		arr[i] = -1;
}

int negativeToZero(int num) {
	if (num < 0)
		return 0;
	else
		return num;
}

void sumByIntArr(int *dest, int *num) {
	int i, sum = 0, carry = 0;
	for (i = 0; (dest[i] != -1 || num[i] != -1) && i < INT_ARR_LEN; i++) {
		sum = negativeToZero(dest[i]) + negativeToZero(num[i]) + carry;
		dest[i] = sum % 10;
		carry = sum / 10;
	}
	if (carry > 0)
		dest[i - 1] = negativeToZero(dest[i - 1]) + carry;
}

void multiplyByIntArr(int *dest, int *num) {
	int *result = new int[INT_ARR_LEN];
	int i, multi = 0;

	initIntArr(result);
	for (i = 0; num[i] != -1 && i < INT_ARR_LEN; i++) {
		int *temp = new int[INT_ARR_LEN];
		int k, carry = 0;

		initIntArr(temp);
		for (k = 0; dest[k] != -1 && k < INT_ARR_LEN; k++) {
			multi = dest[k] * num[i] + carry;
			temp[i + k] = multi % 10;
			carry = multi / 10;
		}
		if (carry > 0)
			temp[i + k] = negativeToZero(temp[i + k]) + carry;
		sumByIntArr(result, temp);
		delete[] temp;
	}
	for (int i = 0; i < INT_ARR_LEN; i++)
		dest[i] = result[i];
	delete[] result;
}

int* numSquareOfNum(int num) {
	int *destArr = new int[INT_ARR_LEN];
	int *numArr = new int[INT_ARR_LEN];
	int temp = num, count = 0;

	for (int i = 0; i < INT_ARR_LEN; i++) {
		if (temp > 0) {
			destArr[i] = numArr[i] = temp % 10;
			temp /= 10; count++;
		}
		else
			destArr[i] = numArr[i] = -1;
	}
	for (int i = 1; i < num; i++)
		multiplyByIntArr(destArr, numArr);
	delete[] numArr;
	return destArr;
}

void printSquareSum() {
	int *result = new int[INT_ARR_LEN];
	int *square;

	initIntArr(result);
	for (int num = 1; num <= 1000; num++) {
		square = numSquareOfNum(num);
		sumByIntArr(result, square);
	}
	for (int i = 0; result[i] != -1 && i < INT_ARR_LEN; i++)
		cout << result[i];
	cout << endl;
	delete[] result, square;
}

int main() {
	Time t;
	printSquareSum();
	t.printRunTime();
}
