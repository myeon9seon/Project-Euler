// execution time: 458ms

#include <iostream>
#include <fstream>
#include "Time.h"
using namespace std;

const int MAX_NAME = 10000; // names.txt에 저장된 이름의 최대 개수
const int MAX_STRING = 20; // names.txt에 저장된 이름의 최대 길이

// A:1 ~ Z:26이라 했을 때 이름에 쓰인 알파벳 숫자의 합을 반환
int sumNameStr(char *name) {
	int sum = 0;
	for (int i = 0; name[i] != '\0'; i++)
		sum += name[i] - 64; // 아스키 코드 A:65 ~ Z:90
	return sum;
}

// 알파벳 숫자의 합 × 정렬 번호 ＝ 점수 총합 반환
int sumNameScore(char **name, int count) {
	int sum = 0;
	for (int i = 0; i < count; i++)
		sum += sumNameStr(name[i]) * (i + 1);
	return sum;
}

// 사전 순서로 *a가 더 빠르면 true를 반환
bool compareDicOrder(char *a, char *b) {
	for (int i = 0; a[i] != '\0' && b[i] != '\0'; i++) {
		if (a[i] < b[i]) // 전부 대문자로 저장되어 있으므로 아스키 코드 비교
			return true;
		else if (b[i] < a[i])
			return false;
	}
	// a, b 중 짧은 이름이 끝날 때까지 모든 글자가 같으면 짧은 이름이 먼저
	if (strlen(a) < strlen(b))
		return true;
	else
		return false;
}

// 선택 정렬 알고리즘을 사용하여 이름을 사전 순서로 정렬
void sortName(char **name, int count) {
	int indexMin;
	for (int i = 0; i < count - 1; i++) {
		indexMin = i;
		for (int k = i + 1; k < count; k++) {
			if (compareDicOrder(name[k], name[indexMin]))
				indexMin = k;
		}
		char temp[MAX_STRING];
		strcpy(temp, name[indexMin]);
		strcpy(name[indexMin], name[i]);
		strcpy(name[i], temp);
	}
}

// 텍스트를 이름 단위로 잘라 dest에 저장 후 이름의 개수를 반환
int splitNameTxt(char **dest, char *txt) {
	int nameCount = 1, nameIndex = 0;
	for (int i = 0; txt[i] != EOF; i++) {
		if (txt[i] == ',') {
			dest[nameCount - 1][nameIndex] = '\0';
			nameCount++; nameIndex = 0;
		}
		else if (txt[i] != '\"')
			dest[nameCount - 1][nameIndex++] = txt[i];
		if (nameIndex > MAX_STRING) break;
	}
	return nameCount;
}

// names.txt에 저장된 이름을 성공적으로 로드하면 true를 반환
bool loadNameFromTxtFile(char **dest, int *count) {
	ifstream nameFile("names.txt");
	if (nameFile.is_open()) {
		char *names = new char[MAX_NAME * MAX_STRING];
		nameFile >> names; nameFile.close();

		*count = splitNameTxt(dest, names);
		sortName(dest, *count);
		
		delete[] names;
		return true;
	}
	else {
		cout << "error: names.txt file does not exist" << endl;
		return false;
	}
}

int main() {
	Time t;
	int count = 0; // names.txt에 저장된 이름의 개수
	char **name = new char*[MAX_NAME];
	for (int i = 0; i < MAX_NAME; i++)
		name[i] = new char[MAX_STRING];
	
	loadNameFromTxtFile(name, &count);
	cout << sumNameScore(name, count) << endl;

	t.printRunTime();
	for (int i = 0; i < MAX_NAME; i++)
		delete[] name[i];
	delete[] name;
}
