#pragma once

#include <iostream>
#include <memory>
#include "../liblogger/Logger.h"
#include <thread>
#include <mutex>

using namespace liblog;

void cinFlush();
Levels parseStringToLoggerLevel(const std::string &data);
std::pair<std::string, Levels> parse_command_line_filelog(int argc, char* argv[]);
std::pair<int, Levels> parse_command_line_socketlog(int argc, char* argv[]);
void test_logger_writing(std::shared_ptr<Logger> &file_log, const std::string &msg, Levels lvl);
void start_testing(std::shared_ptr<Logger> log);