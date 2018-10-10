#include <iostream>
using namespace std;

class Date {
private:
	int year, month, day;
	int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
public:
	Date(int year, int month, int day) {
		this->year = year;
		this->month = month;
		this->day = day;
		setLeapYear();
	}
private:
	void setLeapYear() {
		if (year % 4 == 0 || (year % 100 != 0 && year % 400 == 0))
			days[2 - 1] = 29;
		else
			days[2 - 1] = 28;
	}
public:
	int getYear() { return year; }
	int getMonth() { return month; }
	int getDay() { return day; }
	void setNextDay() {
		day++; // 다음 날
		if (day > days[month - 1]) { // 다음 달
			month++;
			day = 1;
			if (month > 12) { // 다음 해
				year++;
				month = 1;
				setLeapYear();
			}
		}
	}
	bool isDate(int year, int month, int day) {
		if (year == this->year) {
			if (month == this->month) {
				if (day == this->day) {
					return true;
				}
			}
		}
		return false;
	}
};

int main() {
	int count = 0;
	Date date(1900, 1, 1); // 1900년 1월 1일
	for (int day = 1; ; day++) { // 월요일(1)부터 시작
		if (date.getYear() >= 1901) { // 1901년부터
			if (date.getDay() == 1) { // 매월 1일인
				if (day % 7 == 0) // 일요일(7의 배수)의
					count++; // 개수
			}
		}
		if (date.isDate(2000, 12, 31))
			break;
		date.setNextDay();
	}
	cout << count << endl;
}
