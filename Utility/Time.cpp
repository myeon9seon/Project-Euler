#include "Time.h"

Time::Time() : creTime(clock()) {}

clock_t Time::getRunTime() {
	clock_t curTime = clock();
	return curTime - creTime;
}

void Time::printRunTime() {
	cout << "execution time: " << getRunTime() << "ms" <<endl;
}
