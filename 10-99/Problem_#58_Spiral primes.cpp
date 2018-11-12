// 어떻게든 답은 냈는데 마음에 들지 않음, 수행 시간 6분

#include <iostream>
#include <cstdio>
#include "Time.h"
using namespace std;

class Prime {
private:
	bool *m_isPrime;
	int m_range;
public:
	Prime(int range) : m_range(range) {
		m_isPrime = new bool[m_range + 1];
		for (int i = 0; i <= m_range; i++)
			m_isPrime[i] = true;
		init();
	}
	~Prime() { delete[] m_isPrime; }
	bool isPrime(int num) { return m_isPrime[num]; }
private:
	void init() {
		m_isPrime[0] = false, m_isPrime[1] = false;
		for (int i = 2; i * i <= m_range; i++)
			if (m_isPrime[i])
				for (int k = i * i; k <= m_range; k += i)
					m_isPrime[k] = false;
	}	
};

class Matrix {
private:
	enum Diagonal { LEFT_TOP, RIGHT_TOP, LEFT_BOTTOM };
	int m_diagonal[3];
	int m_len;
public:
	Matrix(int len) : m_len(len) {
		for (int i = 0; i < 3; i++)
			m_diagonal[i] = 1;
	}
	double diagonalPrimeRate() {
		Prime p(m_len * m_len);
		int primeCount = 0;
		for (int i = 0; i < m_len / 2; i++) {
			m_diagonal[LEFT_TOP] += 4 * (i * 2 + 1);
			m_diagonal[RIGHT_TOP] += 2 * (i * 4 + 1);
			m_diagonal[LEFT_BOTTOM] += 2 * (i * 4 + 3);
			// RIGHT_BOTTOM은 모두 제곱수라서 계산하지 않음
			if (p.isPrime(m_diagonal[LEFT_TOP])) primeCount++;
			if (p.isPrime(m_diagonal[RIGHT_TOP])) primeCount++;
			if (p.isPrime(m_diagonal[LEFT_BOTTOM])) primeCount++;
		}
		return (double)primeCount / (double)(m_len * 2 - 1);
	}
};

int main() {
	const int MIN_RANGE = 26201;
	const int MAX_RANGE = 26251;
	Time t;
	for (int len = MIN_RANGE; len < MAX_RANGE; len += 2) {
		Matrix m(len); // 반드시 홀수여야 함
		if (m.diagonalPrimeRate() < 0.1) {
			cout << len << endl;
			break;
		}
	}
	t.printRunTime();
}

// 28번을 풀었던 것과 같은 방법을 적용해보았으나 메모리가 모자라서 실패

#include <iostream>
#include <cstdio>
#include "Time.h"
using namespace std;

class Prime {
private:
	bool *m_isPrime;
	int m_range;
public:
	Prime(int range) : m_range(range) {
		m_isPrime = new bool[m_range + 1];
		for (int i = 0; i <= m_range; i++)
			m_isPrime[i] = true;
		init();
	}
	~Prime() { delete[] m_isPrime; }
private:
	void init() {
		m_isPrime[0] = false, m_isPrime[1] = false;
		for (int i = 2; i * i <= m_range; i++)
			if (m_isPrime[i])
				for (int k = i * i; k <= m_range; k += i)
					m_isPrime[k] = false;
	}
public:
	bool isPrime(int num) { return m_isPrime[num]; }
};

class Matrix {
private:
	int **m_matrix;
	int m_len;
public:
	Matrix(int len) : m_len(len) {
		m_matrix = new int*[m_len];
		for (int i = 0; i < m_len; i++)
			m_matrix[i] = new int[m_len];
		init();
	}
	~Matrix() {
		for (int i = 0; i < m_len; i++)
			delete[] m_matrix[i];
		delete[] m_matrix;
	}
private:
	void init() {
		// 초기화
		for (int col = 0; col < m_len; col++)
			for (int row = 0; row < m_len; row++)
				m_matrix[col][row] = 0;
		// 나선 행렬
		int col = m_len / 2, row = m_len / 2;
		for (int num = 1; num <= m_len * m_len; num++) {
			// 중앙(num = 1)을 먼저 찍은 후 나선을 그림 
			if (num > 1) {
				if (col < m_len - 1 && m_matrix[col + 1][row] != 0) // 아래쪽에 값이 있으면
					if (row > 0 && m_matrix[col][row - 1] != 0) col--; // 왼쪽에도 값이 있으면 위쪽으로 이동
					else row--; // 왼쪽으로 이동
				else if (row < m_len - 1 && m_matrix[col][row + 1] != 0) col++; // 오른쪽에 값이 있으면 아래쪽으로 이동
				else if (col > 0 && m_matrix[col - 1][row] != 0) row++; // 위쪽에 값이 있으면 오른쪽으로 이동
				else if (row > 0 && m_matrix[col][row - 1] != 0) col--; // 왼쪽에 값이 있으면 위쪽으로 이동
				else row++; // 4방향에 아무런 값도 없으면(처음 팔을 뻗을 때) 오른쪽으로 이동
			}
			m_matrix[col][row] = num;
		}
	}
public:
	double diagonalPrimeRate() {
		Prime p(m_len * m_len);
		int primeCount = 0;
		for (int i = 0; i < m_len; i++) {
			if (p.isPrime(m_matrix[i][i])) primeCount++;
			if (p.isPrime(m_matrix[(m_len - 1) - i][i])) primeCount++;
		}
		return (double)primeCount / (double)(m_len * 2 - 1);
	}
};

int main() {
	Time t;
	Matrix m(18001);
	cout << m.diagonalPrimeRate() << endl;
	t.printRunTime();
}
