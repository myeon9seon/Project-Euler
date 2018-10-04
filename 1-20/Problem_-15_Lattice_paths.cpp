#include <iostream>
using namespace std;

int main(void) {
	const int WIDTH = 21;
	const int HEIGHT = 21;
	__int64 path[WIDTH][HEIGHT] = { 0, };

	for (int w = 0; w < WIDTH; w++) {
		for (int h = 0; h < HEIGHT; h++) {
			if (w == 0 || h == 0)
				path[w][h] = 1;
			else
				path[w][h] = path[w - 1][h] + path[w][h - 1];
		}
	}
	cout << path[WIDTH - 1][HEIGHT - 1] << endl;
}
