#pragma once
#include <fstream>
#include <ctime>
#include <chrono>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

enum Log_type { INFO, WARNING, LOG_ERROR };
class Logger
{
public:
	Logger();
	void print(int log_type, std::string text);
private:
	void update_time();
	std::tm* time = new tm;
	std::ofstream log_file;
};