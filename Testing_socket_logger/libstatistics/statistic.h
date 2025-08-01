#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <chrono>

struct statistics{
    unsigned int total = 0;
    std::unordered_map<std::string, int> importance_level;
    unsigned int in_hour = 0;
    size_t min_size, max_size;
    double avg_size = 0;
};

class Stats {
public:
    Stats(int n, int t);
    void update_statistics(const std::string &msg);
    void print_statistics();
private:
    bool compare_structs();
    void handle_time();
    std::string parse_logger_level(const std::string &s);

    int _n, _t;
    std::chrono::steady_clock::time_point timeout;
    std::chrono::steady_clock::time_point last_check; 
    statistics stat{};
    statistics timeout_stat{};
};
