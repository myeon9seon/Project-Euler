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

// 배열 길이를 아무렇게나 지정한 것이 아쉬워서
// 배열에 저장할 요소가 늘어날 때마다 자동으로 배열이 커지도록 만들어 보았음

#include <iostream>
using namespace std;

class List {
private:
	int *arr;
	int end = 2;
public:
	List() { arr = new int[end]; }
	~List() { delete[] arr;	}
	int getElement(int index) const { return arr[index]; }
	void setElement(int index, int num) {
		if (index >= end - 1)
			expandArray(index - (end - 1));
		arr[index] = num;
	}
private:
	void expandArray(int count) {
		int *temp = new int[end];
		for (int i = 0; i < end; i++)
			temp[i] = arr[i];
		end += count;
		arr = new int[end];
		for (int i = 0; i < end - count; i++)
			arr[i] = temp[i];
		delete[] temp;
	}
};

void splitCarryToArray(List *dest, int index, int num) {
	int count = 0;
	while (num > 0) {
		dest->setElement(index + count, num % 10);
		num /= 10;
		count++;
	}
	dest->setElement(index + count, -1);
}

void multiplyByArray(List *dest, int num) {
	int carry = 0;
	for (int i = 0; dest->getElement(i) != -1; i++) {
		dest->setElement(i, (dest->getElement(i) * num) + carry);
		if (dest->getElement(i) >= 10) { // 올림수 발생
			if (dest->getElement(i + 1) == -1) { // dest[i]가 배열의 마지막 요소일 때
				splitCarryToArray(dest, i, dest->getElement(i));
				break;
			}
			else {
				carry = dest->getElement(i) / 10;
				dest->setElement(i, dest->getElement(i) % 10);
			}
		}
		else
			carry = 0;
	}
}

int main() {
	List result;
	int sum = 0;
	result.setElement(0, 1);
	result.setElement(1, -1);
	for (int num = 1; num <= 100; num++)
		multiplyByArray(&result, num);
	for (int i = 0; result.getElement(i) != -1; i++)
		sum += result.getElement(i);
	cout << sum << endl;
}
