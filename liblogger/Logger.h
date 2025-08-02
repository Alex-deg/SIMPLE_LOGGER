#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

// ANSI коды для форматирования цвета при выводе в консоль
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define ORANGE  "\033[91m"
#define RESET   "\033[0m"

namespace liblog {

enum Levels {DEBUG, INFO, WARNING, ERROR, FATAL};           // уровни логирования

class ILogger{
public:
    void virtual debug(const std::string &message)     = 0; // запись лога с уровнем debug
    void virtual info(const std::string &message)      = 0; // запись лога с уровнем info
    void virtual warning(const std::string &message)   = 0; // запись лога с уровнем warning
    void virtual error(const std::string &message)     = 0; // запись лога с уровнем error
    void virtual fatal(const std::string &message)     = 0; // запись лога с уровнем fatal
    void virtual set_level(Levels level)               = 0; // сеттер для текущего уровня логирования 
                                                            // (сообщения с уровнем логирования < чем текущий
                                                            // не записываются)
    std::string virtual now()                          = 0; // функция для получения текущей даты и времени
    void virtual write_log(const std::string &message) = 0; // функция записи лога в журнал
};

class Logger : public ILogger {
public:
    Logger(Levels level = Levels::INFO);
    void debug(const std::string &message) override;
    void info(const std::string &message) override;
    void warning(const std::string &message) override;
    void error(const std::string &message) override;
    void fatal(const std::string &message) override;
    void set_level(Levels level) override;
    Levels get_level();                                     // геттер для текущего уровня логирования
protected:
    std::string now() override;
    void write_log(const std::string &message) override;
    Levels _level;                                          // текущий уровень логирования
};

// Мб сделать write_log private и тогда в тестах придется поменять

class FileLogger : public Logger {
public:
    FileLogger(const std::string &path, Levels level = Levels::INFO);
    void write_log(const std::string &message) override;
private:
    std::fstream log_file;                                  // объект файла, который представляет собой журнал логов
};

class SocketLogger : public Logger { // Работает локально
public:
    SocketLogger(int port, Levels level = Levels::INFO);
    ~SocketLogger();
    void write_log(const std::string &message) override;
    //int get_client_fd();
private:
    int set_nonblocking(int fd);                            // функция для задания флагов неблокирующего сокета
    int client_socket;                                      // файловый дескриптор сокета
    int _port;                                              // порт на котором слушаются сообщения
}; 


}