#include <iostream>
using namespace std;

int main(void) {
	int FiboNum[2] = { 1, 2 };
	int Sum = FiboNum[1];

	while (FiboNum[1] < 4000000) {
		int Temp = FiboNum[1];
		FiboNum[1] = FiboNum[0] + FiboNum[1];
		FiboNum[0] = Temp;
		
		if (FiboNum[1] % 2 == 0)
			Sum += FiboNum[1];
	}
	cout << Sum << endl;
}
