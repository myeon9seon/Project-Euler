#include <iostream>
using namespace std;

const int MAX = 10000; // 피보나치 수열의 항 개수
const int DIGIT = 1000; // 피보나치 수열의 항이 가질 수 있는 자릿수

// 피보나치 수열의 항을 배열 요소의 합으로 구하는 함수 (a > b)
// i가 DIGIT - 1 이상의 값을 가지면 계산을 중단하고 true를 반환
bool sumArrNum(int *dest, int *a, int *b) {
	int carry = 0;
	for (int i = 0; a[i] != -1; i++) {
		dest[i] = a[i] + ((b[i] == -1) ? 0 : b[i]) + carry;
		if (dest[i] >= 10) {
			carry = dest[i] / 10;
			dest[i] %= 10;
			if (a[i + 1] == -1) {
				dest[i + 1] = carry;
				break;
			}
		}
		else
			carry = 0;
		if (i == DIGIT - 1)
			return true;
	}
	return false;
}

// 피보나치 수열에서 처음으로 DIGIT 자릿수가 되는 항이 몇 번째인지 반환
int fiboSequence() {
	int result = -1;
	int **num = new int*[MAX];
	for (int i = 0; i < MAX; i++) {
		num[i] = new int[DIGIT];
		for (int k = 0; k < DIGIT; k++)
			num[i][k] = -1;
	}
	// 피보나치 수열의 초기 값 지정
	num[0][0] = 1; num[1][0] = 1;

	for (int i = 2; i < MAX; i++) {
		if (sumArrNum(num[i], num[i - 1], num[i - 2])) {
			result = (i - 1) + 1;
			break;
		}
	}
	for (int i = 0; i < MAX; i++)
		delete[] num[i];
	delete[] num;
	return result;
}

int main() {
	cout << fiboSequence() << endl;
}
