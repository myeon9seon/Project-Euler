#include <iostream>
#include <cmath>
using namespace std;

bool IsNatural(double dNum) {
	int nNum = dNum;
	if (dNum - nNum <= 0) return true;
	return false;
}

int main(void) {
	const int MAX = 1000;
	for (int a = 1; a < MAX; a++) {
		for (int b = a + 1; b < MAX; b++) {
			double c = sqrt(pow(a, 2.0) + pow(b, 2.0));
			if (IsNatural(c)) {
				if (a + b + c == 1000) {
					cout << a << "＋" << b << "＋" << c << "＝" << a + b + c << endl;
					cout << a << "×" << b << "×" << c << "＝" << (int)(a * b * c) << endl;
				}
			}
		}
	}
}
