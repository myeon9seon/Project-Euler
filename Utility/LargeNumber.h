#pragma once
#include <iostream>

class Number {
private:
	int *m_arr;
	int m_range, m_len;
	bool m_isAvailable;
public:
	Number(int len, int num);
	Number(const Number& copy);
	~Number();
	bool isAvailable() const;
	void setAvailable(bool isAvailable);
	int getRange() const;
	int getLength() const;
	void setLength(int len);
	int getNumber(int index) const;
	void setNumber(int index, int num);
public:
	void init(int num);
	void print() const;
};

class Calculator {
private:
	Number m_dest;
public:
	Calculator(int range, int num);
	Number& getNumber();
	void setNumber(int num);
	void setNumber(const Number& num);
public:
	void sum(Number num);
	void print() const;
};
