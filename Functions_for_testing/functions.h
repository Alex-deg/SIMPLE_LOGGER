#pragma once

#include <iostream>
#include <memory>
#include "../liblogger/Logger.h"
#include <thread>
#include <mutex>

using namespace liblog;

void cinFlush(); // функция для очистки потока ввода
Levels parseStringToLoggerLevel(const std::string &data); // функция для получения уровня логирования по умолчанию
                                                          // из строки, полученной из командной строки
std::pair<std::string, Levels> parse_command_line_filelog(int argc, char* argv[]); // функция для получения параметров 
                                                                                   // из командной строки (для логировния в файл)
std::pair<int, Levels> parse_command_line_socketlog(int argc, char* argv[]); // функция дляполучения параметров из командной
                                                                             // строки (для логирования в сокет)
void test_logger_writing(std::shared_ptr<Logger> &file_log, const std::string &msg, Levels lvl); // логирование полученных сообщений
void start_testing(std::shared_ptr<Logger> log); // функция которая реализует небольшое консольное меню