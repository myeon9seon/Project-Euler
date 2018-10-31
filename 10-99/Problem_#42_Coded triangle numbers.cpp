// execution time: 4ms

#include <iostream>
#include <fstream>
#include <cstring>
#include "Time.h"
using namespace std;

const int MAX_WORD = 2000;
const int MAX_STRING = 20;

class Word {
private:
	char **m_words;
	int m_count;
	int m_maxWordLen;
public:
	Word() { m_words = getWords(); }
	~Word() {
		for (int i = 0; i < m_count; i++)
			delete[] m_words[i];
		delete[] m_words;
	}
	int getWordCount() { return m_count; }
	int getMaxWordLen() { return m_maxWordLen; }
	int getWordValue(int index) {
		int value = 0;
		for (int i = 0; m_words[index][i] != '\0'; i++)
			value += m_words[index][i] - 'A' + 1;
		return value;
	}
private:
	char* loadWordsFromTxtFile() {
		ifstream txtFile("words.txt");
		if (txtFile.is_open()) {
			char *words = new char[MAX_WORD * MAX_STRING];
			txtFile >> words; txtFile.close();
			return words;
		}
		else {
			cout << "error: words.txt file does not exist" << endl;
			exit(EXIT_SUCCESS);
		}
	}
	char** getWords() {
		char **dest = new char*[MAX_WORD];
		char *str = loadWordsFromTxtFile();
		char *temp = new char[MAX_STRING];
		int wordLen = 0;

		m_count = 0;
		for (int i = 0; i < MAX_WORD; i++)
			dest[i] = new char[MAX_STRING];

		for (int i = 0; str[i] != '\0'; i++) {
			if (str[i] == ',') {
				temp[wordLen] = '\0';
				if (wordLen > m_maxWordLen)
					m_maxWordLen = wordLen;
				strcpy(dest[m_count++], temp);
				temp[0] = '\0';
				wordLen = 0;
			}
			if (str[i] >= 'A' && str[i] <= 'Z')
				temp[wordLen++] = str[i];
		}
		// 마지막 단어는 ','가 없으므로 따로 저장
		temp[wordLen] = '\0';
		if (wordLen > m_maxWordLen)
			m_maxWordLen = wordLen;
		strcpy(dest[m_count++], temp);
		temp[0] = '\0';
		wordLen = 0;

		delete[] str, temp;
		return dest;
	}
};

class Triangular {
private:
	int *m_tri;
	int m_count;
public:
	~Triangular() { delete[] m_tri; }
	void setTriangularNum(int max) {
		int *temp = new int[max];
		m_count = 0;
		for (int num = 1; ; num++) {
			temp[num - 1] = (num * num + num) / 2;
			if (temp[num - 1] >= max)
				break;
			m_count++;
		}
		m_tri = new int[m_count];
		for (int i = 0; i < m_count; i++)
			m_tri[i] = temp[i];
		delete[] temp;
	}
	bool isTriangular(int num) {
		for (int i = 0; i < m_count; i++)
			if (m_tri[i] == num)
				return true;
		return false;
	}
};

int main() {
	Time t;
	Word w;
	Triangular tri;
	const int MAX_TRIANGLE = 26 * w.getMaxWordLen();
	int triWordCount = 0;

	tri.setTriangularNum(MAX_TRIANGLE);
	for (int i = 0; i < w.getWordCount(); i++)
		if (tri.isTriangular(w.getWordValue(i)))
			triWordCount++;
	cout << triWordCount << endl;
	t.printRunTime();
}
