#include "Log.h"
#include <string>

#define CHECK_INSTANCE if (instance == nullptr) defaultCreate();

Log* Log::instance;
bool Log::timeEnable;

void Log::createLogFile(const char* fileName, bool timeEnabled) {
	if (instance != nullptr) {
		delete instance;
	}

	instance = new Log(fileName);
	instance->timeEnable = timeEnabled;
}

void Log::logPath(vector<int>& path) {
	CHECK_INSTANCE;
	if (timeEnable)
		printTime();

	for (int node : path) {
		instance->file << node << ", ";
	}
	instance->file << endl;
}

void Log::logString(const char* str) {
	CHECK_INSTANCE;
	if (timeEnable)
		printTime();

	instance->file << str << endl;
}

void Log::logFloat(float num) {
	CHECK_INSTANCE;
	if (timeEnable)
		printTime();

	instance->file << to_string(num) << endl;
}

void Log::setTimeEnable(bool enable) {
	timeEnable = enable;
}

Log::~Log() {
	if (timeEnable)
		printTime();
	file << "Closing log file.";
	file.close();
}

Log::Log(const char* fileName) {
	file = ofstream(fileName, ios::out | ios::trunc);
	if (timeEnable)
		printTime();
	file << "GraphPathGen log opened." << endl;
}

void Log::defaultCreate() {
	instance = new Log("log.txt");
}

void Log::printTime() {
	instance->file << Utils::getTimeStr();
}