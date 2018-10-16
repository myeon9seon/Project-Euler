// 미완성: 2부터 MAX_NUM까지를 분모로 가지는 단위 분수의 소수점 아래 부분을 MAX_LEN번째 자리만큼 보여주는 코드

#include <iostream>
using namespace std;

const int MAX_NUM = 29;
const int MAX_LEN = 40;

int main() {
	int *decimalPlace = new int[MAX_LEN];
	for (int num = 2; num <= MAX_NUM; num++) {
		int rest = 1;
		// 초기화
		for (int i = 0; i < MAX_LEN; i++)
			decimalPlace[i] = -1;
		for (int i = 0; i < MAX_LEN; i++) {
			decimalPlace[i] = (rest * 10) / num; // num은 단위 분수의 분모
			rest = (rest * 10) % num;
			if (rest == 0) break; // 나누어 떨어지면 루프 탈출
		}
		// 결과 확인용
		cout << "0.";
		for (int i = 0; decimalPlace[i] != -1 && i < MAX_LEN; i++)
			cout << decimalPlace[i];
		cout << endl;
	}
}
