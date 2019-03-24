#pragma once
#include <ctime>

class Utils {
public:
	static char* getTimeStr();

private:
	static time_t rawtime;
	static struct tm* timeinfo;
	static char buffer[32];
};