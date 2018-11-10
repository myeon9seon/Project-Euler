#include "LargeNumber.h"
using namespace std;

Number::Number(int range, int num) : m_range(range) {
	m_arr = new int[range];
	for (int i = 0; i < m_range; i++)
		m_arr[i] = 0;
	m_isAvailable = false;
	init(num);
}

Number::Number(const Number& copy) {
	m_range = copy.getRange();
	m_len = copy.getLength();
	m_isAvailable = copy.isAvailable();
	m_arr = new int[m_range];
	for (int i = 0; i < m_range; i++)
		m_arr[i] = copy.getNumber(i);
}

Number::~Number() { delete[] m_arr; }

bool Number::isAvailable() const { return m_isAvailable; }

void Number::setAvailable(bool isAvaiable) { m_isAvailable = isAvaiable; }

int Number::getRange() const { return m_range; }

int Number::getLength() const {	return m_len; }

void Number::setLength(int len) { m_len = len; }

int Number::getNumber(int index) const { return m_arr[index]; }

void Number::setNumber(int index, int num) { m_arr[index] = num; }

void Number::init(int num) {
	int temp = num;
	for (m_len = 0; temp > 0; m_len++) {
		if (m_len >= m_range) {
			cout << "error: " << num << " is out of range for parameter (range: " << m_range << ")" << endl;
			m_isAvailable = false;
			return;
		}
		m_arr[m_len] = temp % 10;
		temp /= 10;
	}
	m_isAvailable = true;
}

void Number::print() const {
	if (m_isAvailable) {
		for (int i = m_len - 1; i >= 0; i--)
			cout << m_arr[i];
	}
	else
		cout << "error: out of range for parameter" << endl;
}

Calculator::Calculator(int range, int num) : m_dest(range, num) {}

Number& Calculator::getNumber() { return m_dest; }

void Calculator::setNumber(int num) { m_dest.init(num); }

void Calculator::setNumber(const Number& num) { m_dest = num; }

void Calculator::sum(Number num) {
	if (m_dest.isAvailable()) {
		int carry = 0;
		if (num.getLength() > m_dest.getLength())
			m_dest.setLength(num.getLength());
		for (int i = 0; i < m_dest.getLength(); i++) {
			int result = m_dest.getNumber(i) + num.getNumber(i) + carry;
			if (i == m_dest.getLength() - 1 && result >= 10) {
				m_dest.setNumber(i, result % 10);
				if (m_dest.getLength() + 1 > m_dest.getRange()) {
					cout << "error: out of range for parameter" << endl;
					m_dest.setAvailable(false);
					break;
				}
				m_dest.setLength(m_dest.getLength() + 1);
				m_dest.setNumber(i + 1, result / 10);
				break;
			}
			else {
				carry = result / 10;
				m_dest.setNumber(i, result % 10);
			}
		}
	}
	else
		cout << "error: out of range for parameter" << endl;
}

void Calculator::print() const {
	if (m_dest.isAvailable())
		m_dest.print();
	else
		cout << "error: out of range for parameter" << endl;
}
