#pragma once

#include <string>
#include <sstream>
#include <vector>

enum LogType
{
	INFO,
	WARNING,
	ERROR
};

struct LogEntry
{
	LogType type;
	std::string message;
};

class Logger
{
public:
	static std::vector<LogEntry> logEntries;

	static void Info(const std::string& message);
	static void Warning(const std::string& message);
	static void Error(const std::string& message);
};



