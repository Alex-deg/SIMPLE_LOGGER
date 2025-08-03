#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <cerrno>
#include <stdexcept>
#include <memory>
#include <fcntl.h>
#include <stack>
#include "../libstatistics/statistic.h"

class TCPServer {
public:
    TCPServer(int port);
    void run();
    ~TCPServer();
    
private:
    static const int MAX_EVENTS = 10;                       // количество сессий одновременно
    static const int BUF_SIZE = 1024;                       // размер буфера
    
    int port_;                                              // порт сервера
    int epoll_fd_;
    int server_fd_;
    std::vector<struct epoll_event> events_{MAX_EVENTS};    // массив с событиями

    std::shared_ptr<Stats> stat;                            // объект для счета статистики

    void createSocket();                                    // создание сокета
    void setupEpoll();                                      // натсройка epoll
    void handleNewConnection();                             // обработка нового подключения
    void handleClientData(int fd);                          // обрботка данных пользователя

    int set_nonblocking(int fd);
};