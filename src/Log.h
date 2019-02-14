#pragma once
#include "../stdafx.h"
#include <time.h>
#include <string>
#include <fstream>

class Log {
public:
	static void createLogFile(const char* fileName, bool timeEnabled);
	static void logPath(vector<int>& path);
	static void logString(const char* str);
	static void logFloat(float num);
	static void setTimeEnable(bool enable);
	
	~Log();
protected:
	static Log* instance;

	static bool timeEnable;
	static time_t rawtime;
	static struct tm* timeinfo;
	static char buffer[32];

	Log(const char* fileName);
	ofstream file;

	static void defaultCreate();
	//Prints time, assumes instance is already checked.
	static void printTime();
 };