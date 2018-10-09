#include <iostream>
using namespace std;

void splitCarryToArray(int *dest, int index, int num) {
	int count = 0;
	while (num > 0) {
		dest[index + count] = num % 10;
		num /= 10;
		count++;
	}
	dest[index + count] = -1;
}

void multiplyByArray(int *dest, int num) {
	int carry = 0;
	for (int i = 0; dest[i] != -1; i++) {
		dest[i] = (dest[i] * num) + carry;
		if (dest[i] >= 10) { // 올림수 발생
			if (dest[i + 1] == -1) { // dest[i]가 배열의 마지막 요소일 때
				splitCarryToArray(dest, i, dest[i]);
				break;
			}
			else {
				carry = dest[i] / 10;
				dest[i] %= 10;
			}
		}
		else
			carry = 0;
	}
}

int main() {
	int result[200] = { 1, -1, };
	int sum = 0;
	for (int num = 1; num <= 100; num++)
		multiplyByArray(result, num);
	for (int i = 0; result[i] != -1; i++)
		sum += result[i];
	cout << sum << endl;
}
