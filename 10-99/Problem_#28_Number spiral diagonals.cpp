#include <iostream>
#include "Time.h"
using namespace std;

const int MAX = 1001; // 행렬의 크기는 반드시 홀수여야 함

void setMatrix(int **dest) {
	// 초기화
	for (int col = 0; col < MAX; col++)
		for (int row = 0; row < MAX; row++)
			dest[col][row] = 0;
	// 나선 행렬
	int col = MAX / 2, row = MAX / 2;
	for (int num = 1; num <= MAX * MAX; num++) {
		// 중앙(num = 1)을 먼저 찍은 후 나선을 그림 
		if (num > 1) {
			if (col > 0 && dest[col - 1][row] != 0) // 위쪽에 값이 있으면 (A)
				if (row > 0 && dest[col][row - 1] != 0) col++; // 왼쪽에도 값이 있으면 아래쪽으로 이동
				else row--; // (A) 왼쪽으로 이동
			else if (row < MAX - 1 && dest[col][row + 1] != 0) col--; // 오른쪽에 값이 있으면 위쪽으로 이동
			else if (col < MAX - 1 && dest[col + 1][row] != 0) row++; // 아래쪽에 값이 있으면 오른쪽으로 이동
			else if (row > 0 && dest[col][row - 1] != 0) col++; // 왼쪽에 값이 있으면 아래쪽으로 이동
			else row++; // 4방향에 아무런 값도 없으면(처음 팔을 뻗을 때) 오른쪽으로 이동
		}
		dest[col][row] = num;
	}
}

int sumXLineOfMatrix(int **dest) {
	int sum = 0;
	for (int i = 0; i < MAX; i++) {
		sum += dest[i][i]; // 왼쪽 위 ~ 오른쪽 아래 대각선
		sum += dest[(MAX - 1) - i][i]; // 왼쪽 아래 ~ 오른쪽 위 대각선
	}
	return sum - dest[MAX / 2][MAX / 2]; // 중앙 값이 두 번 더해졌으므로 빼고 리턴
}

int main() {
	Time t;
	int **matrix = new int*[MAX];
	for (int i = 0; i < MAX; i++)
		matrix[i] = new int[MAX];

	setMatrix(matrix);
	cout << sumXLineOfMatrix(matrix) << endl;

	t.printRunTime();
	for (int i = 0; i < MAX; i++)
		delete[] matrix[i];
	delete[] matrix;
}
