#ifndef __TIME_H__
#define __TIME_H__

#include <iostream>
#include <ctime>

using std::cout;
using std::endl;

class Time {
private:
	clock_t creTime;
public:
	Time();
	clock_t getRunTime();
	void printRunTime();
};

#endif
