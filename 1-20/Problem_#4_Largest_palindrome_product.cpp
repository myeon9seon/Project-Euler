#include <iostream>
using namespace std;

bool IsPalindrome(int num) {
	int arr[6];    // array range is 5~6 because 100×100＝10000 and 999×999＝998001
	int index = 0;
	while (num > 0) {
		arr[index] = num % 10;
		num /= 10;
		index++;
	}
	for (int i = 0; i < index/2; i++) {
		if (arr[i] != arr[(index-1) - i]) {
			return false;
		}
	}
	return true;
}

int main(void) {
	int max = 0;
	for (int i = 100; i <= 999; i++) {
		for (int j = i; j <= 999; j++) {
			if (IsPalindrome(i * j)) {
				if ((i * j) > max)
					max = i * j;
			}
		}
	}
	cout << max << endl;
}
