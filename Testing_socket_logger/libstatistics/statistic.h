#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <chrono>

struct statistics{                                          // структура, хранящая все требуемые характеристики
    unsigned int total = 0;                                 // сообщений всего
    std::unordered_map<std::string, int> importance_level;  // сортировка по уровню логирования
    unsigned int in_hour = 0;                               // сообщений за час
    size_t min_size, max_size;                              // максимальная и минимальная длина лога
    double avg_size = 0;                                    // средняя длина лога
};

class Stats {
public:
    Stats(int n, int t);
    void update_statistics(const std::string &msg);         // метод обновления статистики
    void print_statistics();                                // метод вывода статистики 
private:
    bool compare_structs();                                 // метод сравнения структур 
    void handle_time();                                     // метод который контролирует прошел ли час
    std::string parse_logger_level(const std::string &s);   // метод для получения уровня логирования из всего лога

    int _n, _t;                                             // параметры вывода статистики
                                                            // _n - каждое N-ое сообщение
                                                            // _t - каждые T секунд
    std::chrono::steady_clock::time_point timeout;          // объект, для контролирования таймаута, по которому 
                                                            // выводится статистика 
    std::chrono::steady_clock::time_point last_check;       // объект, для контролирования прошел ли час
    statistics stat{};                                      // объект для ведения статистики
    statistics timeout_stat{};                              // объект для сверки поменялась ли статистика за T секунд или нет
};
