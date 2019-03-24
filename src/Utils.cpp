#include "Utils.h"

time_t Utils::rawtime;
struct tm* Utils::timeinfo = new tm;
char Utils::buffer[32];

char* Utils::getTimeStr() {
	time(&rawtime);
	localtime_s(timeinfo, &rawtime);
	strftime(buffer, 32, "[%T] ", timeinfo);
	return buffer;
}
