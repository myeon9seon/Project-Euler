// 미완 3분 51초

#include <iostream>
#include "Time.h"
using namespace std;

const int INT_ARR_LEN = 4000;

// int형 배열을 -1로 초기화
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

// dest에 num을 곱한 값을 dest에 저장
void multiplyByIntArr(int *dest, int *num) {
	int *result = new int[INT_ARR_LEN];
	int numIndex, multi = 0;

	initIntArr(result);
	for (numIndex = 0; num[numIndex] != -1 && numIndex < INT_ARR_LEN; numIndex++) {
		int *temp = new int[INT_ARR_LEN];
		int destIndex, carry = 0;

		initIntArr(temp);
		for (destIndex = 0; dest[destIndex] != -1 && destIndex < INT_ARR_LEN; destIndex++) {
			multi = dest[destIndex] * num[numIndex] + carry;
			temp[numIndex + destIndex] = multi % 10;
			carry = multi / 10;
		}
		if (carry > 0)
			temp[numIndex + destIndex] = negativeToZero(temp[numIndex + destIndex]) + carry;
		sumByIntArr(result, temp);
		delete[] temp;
	}
	for (int i = 0; i < INT_ARR_LEN; i++)
		dest[i] = result[i];
	delete[] result;
}

// num을 num으로 제곱한 결과가 저장된 int형 배열의 주소를 리턴
int* getSelfPower(int num) {
	int *destArr = new int[INT_ARR_LEN]; // 리턴할 결과를 저장하는 배열
	int *numArr = new int[INT_ARR_LEN]; // num을 int형 배열로 저장
	int temp = num, count = 0;
	// dest와 num 배열을 같은 값으로 초기화
	for (int i = 0; i < INT_ARR_LEN; i++) {
		if (temp > 0) {
			destArr[i] = numArr[i] = temp % 10;
			temp /= 10; count++;
		}
		else
			destArr[i] = numArr[i] = -1;
	}
	for (int i = 2; i <= num; i++)
		multiplyByIntArr(destArr, numArr);
	delete[] numArr;
	return destArr;
}

// max까지의 자기 자신의 제곱의 합의 마지막 10자리를 출력
void printSelfPowerSum(int max) {
	int *result = new int[INT_ARR_LEN];
	int *square; // 제곱 배열의 주소를 저장하는 포인터

	initIntArr(result);
	for (int num = 1; num <= max; num++) {
		square = getSelfPower(num);
		sumByIntArr(result, square);
	}
	for (int i = 9; i >= 0; i--)
		cout << result[i];
	cout << endl;
	delete[] result, square;
}

int main() {
	Time t;
	printSelfPowerSum(1000);
	t.printRunTime();
}
