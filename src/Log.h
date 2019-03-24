#pragma once
#include "../stdafx.h"
#include "Utils.h"
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

	Log(const char* fileName);
	ofstream file;

	static void defaultCreate();
	//Prints time, assumes instance is already checked.
	static void printTime();
 };