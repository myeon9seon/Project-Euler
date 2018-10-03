// Solution 1-1: sequence function
// execution time: 11241ms

#include <iostream>
#include <ctime>
using namespace std;

__int64 collatzSequence(__int64 num) {
	if (num % 2 == 0)
		return num / 2;
	else
		return (3 * num) + 1;
}

int main(void) {
	clock_t begin = clock(), end;
	int maxCount = 0, maxNum = 0;

	for (int num = 1; num <= 1000000; num++) {
		__int64 collatz = num;
		int count = 0;
		while (collatz != 1) {
			collatz = collatzSequence(collatz);
			count++;
		}
		if (count > maxCount) {
			maxCount = count;
			maxNum = num;
		}
	}
	cout << maxNum << endl;

	end = clock();
	cout << "execution time: " << end - begin << "ms" << endl;
}

// Solution 1-2: function to line
// execution time: 5827ms
// 함수 호출 비용이 생각보다 크다는 것을 직접 확인할 수 있어 좋았음

#include <iostream>
#include <ctime>
using namespace std;

int main(void) {
	clock_t begin = clock(), end;
	int maxCount = 0, maxNum = 0;

	for (int num = 1; num <= 1000000; num++) {
		__int64 collatz = num;
		int count = 0;
		while (collatz != 1) {
			(collatz % 2 == 0) ? collatz /= 2 : collatz = (collatz * 3) + 1;
			count++;
		}
		if (count > maxCount) {
			maxCount = count;
			maxNum = num;
		}
	}
	cout << maxNum << endl;

	end = clock();
	cout << "execution time: " << end - begin << "ms" << endl;
}

// 이하는 실행 시간을 줄이기 위한 여러 가지 시행착오 기록

// execution time: 63139ms
// unordered_map을 사용해보았으나 1-2번 방법보다 10배 느림
// 처음 써봐서 사용을 잘못한 것일지도 모르겠음 알고리즘이 잘못되었을 수도 있고
// map보다 unordered_map이 수행 속도가 빠름

#include <iostream>
#include <unordered_map>
#include <ctime>
using namespace std;

int main(void) {
	clock_t begin = clock(), end;
	unordered_map<__int64, int> map;
	int maxCount = 0, maxNum = 0;

	for (int num = 1; num <= 1000000; num++) {
		__int64 collatz = num;
		int count = 0;
		while (collatz > 1) {
			if (map.find(collatz) != map.end()) {
				count += map.at(collatz);
				map[num] = count;
				break;
			}
			else {
				(collatz % 2 == 0) ? collatz /= 2 : collatz = (collatz * 3) + 1;
				count++;
				if (collatz == 1) {
					map[num] = count;
					break;
				}
			}
		}
		if (count > maxCount) {
			maxCount = count;
			maxNum = num;
		}
	}
	cout << maxNum << endl;

	end = clock();
	cout << "execution time: " << end - begin << "ms" << endl;
}
