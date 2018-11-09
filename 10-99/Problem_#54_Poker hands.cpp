// execution time: 48ms

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include "Time.h"
using namespace std;

class Rule {
private:
	enum Card { _2 = 2, _3, _4, _5, _6, _7, _8, _9, _10, _J, _Q, _K, _A };
	enum Score { HIGH_CARD, ONE_PAIR, TWO_PAIRS, TRIPLE, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_CARD, STRAIGHT_FLUSH, ROYAL_FLUSH };
private:
	int charToInt(char ch) {
		switch (ch) {
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case 'T': return 10;
		case 'J': return 11;
		case 'Q': return 12;
		case 'K': return 13;
		case 'A': return 14;
		default: return -1;
		}
	}
	// 1: 무늬가 같은 10, J, Q, K, A
	bool RoyalFlush(char *card) {
		char shape = card[1];
		int cardCount[Card::_A + 1] = { 0, };
		for (int i = 0; i < 5 * 2; i++) {
			if (i % 2 == 0)
				cardCount[charToInt(card[i])]++;
			else
				if (card[i] != shape)
					return false;
		}
		if (cardCount[Card::_10] && cardCount[Card::_J] && cardCount[Card::_Q] && cardCount[Card::_K] && cardCount[Card::_A])
			return true;
		else
			return false;
	}
	// 2: 무늬가 같은 연속된 숫자
	int StraightFlush(char *card) {
		char shape = card[1];
		int cardCount[Card::_A + 1] = { 0, };
		for (int i = 0; i < 5 * 2; i++) {
			if (i % 2 == 0)
				cardCount[charToInt(card[i])]++;
			else
				if (card[i] != shape)
					return 0;
		}
		for (int i = Card::_2; i <= Card::_A - 4; i++) {
			int continuity = 0;
			for (int k = 0; k < 5; k++) {
				if (cardCount[i + k] > 0)
					continuity++;
			}
			if (continuity == 5)
				return i + 5;
		}
		return 0;
	}
	// 3: 네 장이 같은 숫자
	int FourCard(char *card) {
		int cardCount[Card::_A + 1] = { 0, };
		for (int i = 0; i < 5 * 2; i++) {
			if (i % 2 == 0)
				cardCount[charToInt(card[i])]++;
		}
		for (int i = Card::_2; i <= Card::_A; i++)
			if (cardCount[i] == 4)
				return i;
		return 0;
	}
	// 4: 트리플 + 원 페어
	int FullHouse(char *card) {
		int cardCount[Card::_A + 1] = { 0, };
		int triple = 0, pair = 0;
		for (int i = 0; i < 5 * 2; i++)
			if (i % 2 == 0)
				cardCount[charToInt(card[i])]++;
		for (int i = Card::_2; i <= Card::_A; i++)
			if (cardCount[i] >= 3)
				triple = i;
			else if (cardCount[i] >= 2)
				pair++;
		if (triple > 0 && pair > 0)
			return triple;
		else
			return 0;
	}
	// 5: 무늬가 모두 같음
	int Flush(char *card) {
		int top = 0;
		char shape = card[1];
		for (int i = 0; i < 5 * 2; i++) {
			if (i % 2 == 0)
				if (i > top)
					top = i;
			else
				if (card[i] != shape)
					return 0;
		}
		return top;
	}
	// 6: 연속된 숫자
	int Straight(char *card) {
		int cardCount[Card::_A + 1] = { 0, };
		for (int i = 0; i < 5 * 2; i++)
			if (i % 2 == 0)
				cardCount[charToInt(card[i])]++;
		for (int i = Card::_2; i <= Card::_A - 4; i++) {
			int continuity = 0;
			for (int k = 0; k < 5; k++) {
				if (cardCount[i + k] > 0)
					continuity++;
			}
			if (continuity == 5)
				return i + 5;
		}
		return 0;
	}
	// 7: 세 장이 같은 숫자
	int Triple(char *card) {
		int cardCount[Card::_A + 1] = { 0, };
		for (int i = 0; i < 5 * 2; i++)
			if (i % 2 == 0)
				cardCount[charToInt(card[i])]++;
		for (int i = Card::_2; i <= Card::_A; i++)
			if (cardCount[i] >= 3)
				return i;
		return 0;
	}
	// 8: 원 페어 2쌍
	int TwoPairs(char *card) {
		int cardCount[Card::_A + 1] = { 0, };
		int pairTop = 0, pairCount = 0;
		for (int i = 0; i < 5 * 2; i++)
			if (i % 2 == 0)
				cardCount[charToInt(card[i])]++;
		for (int i = Card::_2; i <= Card::_A; i++) {
			if (cardCount[i] >= 2) {
				pairTop = i;
				pairCount++;
			}
		}
		if (pairCount == 2)
			return pairTop;
		else
			return 0;
	}
	// 9: 두 장이 같은 숫자
	int OnePair(char *card) {
		int cardCount[Card::_A + 1] = { 0, };
		for (int i = 0; i < 5 * 2; i++)
			if (i % 2 == 0)
				cardCount[charToInt(card[i])]++;
		for (int i = Card::_2; i <= Card::_A; i++)
			if (cardCount[i] >= 2)
				return i;
		return 0;
	}
	// 10: 가장 높은 숫자
	int HighCard(char *card) {
		int top = 0;
		for (int i = 0; i < 5 * 2; i++)
			if (charToInt(card[i]) > top)
				top = charToInt(card[i]);
		return top;
	}
public:
	int getCardScore(char *card) {
		int score = 0, top = 0;
		// 9: 로얄 플러시
		if (RoyalFlush(card)) {
			score = Card::_A * 10 + Score::ROYAL_FLUSH;
			return score;
		}
		// 8: 스트레이트 플러시
		top = StraightFlush(card);
		if (top > 0) {
			score = top * 10 + Score::STRAIGHT_FLUSH;
			return score;
		}
		// 7: 포 카드
		top = FourCard(card);
		if (top > 0) {
			score = top * 10 + Score::FOUR_CARD;
			return score;
		}
		// 6: 풀 하우스
		top = FullHouse(card);
		if (top > 0) {
			score = top * 10 + Score::FULL_HOUSE;
			return score;
		}
		// 5: 플러시
		top = Flush(card);
		if (top > 0) {
			score = top * 10 + Score::FLUSH;
			return score;
		}
		// 4: 스트레이트
		top = Straight(card);
		if (top > 0) {
			score = top * 10 + Score::STRAIGHT;
			return score;
		}
		// 3: 트리플
		top = Triple(card);
		if (top > 0) {
			score = top * 10 + Score::TRIPLE;
			return score;
		}
		// 2: 투 페어
		top = TwoPairs(card);
		if (top > 0) {
			score = top * 10 + Score::TWO_PAIRS;
			return score;
		}
		// 1: 원 페어
		top = OnePair(card);
		if (top > 0) {
			score = top * 10 + Score::ONE_PAIR;
			return score;
		}
		// 0: 하이 카드
		return HighCard(card) * 10 + Score::HIGH_CARD;
	}
};

class Poker {
private:
	const int GAME_COUNT = 1000;
	bool m_isDataExist = false;
	char **m_player1, **m_player2;
public:
	Poker() {
		m_player1 = new char*[GAME_COUNT];
		m_player2 = new char*[GAME_COUNT];
		for (int i = 0; i < GAME_COUNT; i++) {
			m_player1[i] = new char[3 * 5 + 1];
			m_player2[i] = new char[3 * 5 + 1];
		}
		m_isDataExist = loadDataFromTxtFile();
	}
	~Poker() {
		for (int i = 0; i < GAME_COUNT; i++)
			delete[] m_player1[i], m_player2[i];
		delete[] m_player1, m_player2;
	}
private:
	bool loadDataFromTxtFile() {
		ifstream file("poker.txt");
		if (file.is_open()) {
			char temp[3], *set = new char[3 * 5 + 1];
			set[0] = '\0';
			for (int i = 0; i < GAME_COUNT; i++) {
				for (int k = 0; k < 5; k++) {
					file >> temp;
					sprintf(set, "%s%s", set, temp);
				}
				strcpy(m_player1[i], set);
				set[0] = '\0';
				for (int k = 0; k < 5; k++) {
					file >> temp;
					sprintf(set, "%s%s", set, temp);
				}
				strcpy(m_player2[i], set);
				set[0] = '\0';
			}
			file.close();
			delete[] set;
			return true;
		}
		else {
			cout << "error: poker.txt file does not exist" << endl;
			return false;
		}
	}
	int getGameResult(int index) {
		typedef struct _score { int rank, top; } Score;
		Rule r;
		Score player1, player2;
		int temp;

		temp = r.getCardScore(m_player1[index]);
		player1.rank = temp % 10; player1.top = temp / 10;
		temp = r.getCardScore(m_player2[index]);
		player2.rank = temp % 10; player2.top = temp / 10;

		if (player1.rank > player2.rank)
			return 1;
		else if (player1.rank == player2.rank)
			if (player1.top > player2.top)
				return 1;
			else
				return 2;
		else
			return 2;
	}
public:
	void printGameData() {
		int countPlayer1 = 0;
		for (int i = 0; i < GAME_COUNT; i++)
			if (getGameResult(i) == 1)
				countPlayer1++;
		cout << countPlayer1 << endl;
	}
};

int main() {
	Time t;
	Poker p;
	p.printGameData();
	t.printRunTime();
}
