#include "statistic.h"

Stats::Stats(int n, int t) : _n(n), _t(t) {
    last_check = std::chrono::steady_clock::now();
    timeout = std::chrono::steady_clock::now();
}

void Stats::update_statistics(const std::string &msg)
{
    stat.total++; // увеличение общего числа сообщений на 1
    stat.importance_level[parse_logger_level(msg)]++; // определяем какой уровень логирования у сообщения
                                                      // и увеличиваем количество его появлений на 1
    handle_time(); // проверка не прошел ли час и увеличение или сброс поля statistics::in_hour
    if(stat.total < 2){ // если первое сообщение инициализируем им
        stat.min_size = msg.size();
        stat.max_size = msg.size();
        stat.avg_size = msg.size();
    }
    else{ // иначе вычисляем
        stat.min_size = std::min(stat.min_size, msg.size());
        stat.max_size = std::max(stat.max_size, msg.size());
        // вычисление средней длины сообщения без накопления общей длины всех сообщений (для избежания переполнения типов)
        stat.avg_size += ((stat.total - 1) * msg.size() - (stat.total - 1) * stat.avg_size)/((stat.total - 1) * stat.total);
    }
    if(stat.total % _n == 0){
        std::cout << "Вывод статистики после N-ого сообщения" << "(" << stat.total << ")" << std::endl;
        print_statistics();
        return;
    }
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::steady_clock::now() - timeout
    ).count();
    if(duration >= _t && !compare_structs()){
        std::cout << "Вывод статистики после таймаута T секунд" << std::endl;
        timeout = std::chrono::steady_clock::now();
        timeout_stat = stat;
        print_statistics();
    }
}

void Stats::print_statistics()
{
    std::cout << "====================STATISTICS====================" << std::endl;
    std::cout << "Сообщений всего = " << stat.total << std::endl;
    std::cout << "Сообщений по уровню важности:" << std::endl;
    for(auto &x : stat.importance_level){
        std::cout << x.first << " = " << std::to_string(x.second) << std::endl;
    }
    std::cout << "Сообщений за последний час = " << stat.in_hour << std::endl;
    std::cout << "Минимальная длина сообщения = " << stat.min_size << std::endl;
    std::cout << "Максимальная длина сообщения = " << stat.max_size << std::endl;
    std::cout << "Средняя длина сообщения = " << stat.avg_size << std::endl;
    std::cout << "===================================================" << std::endl;
}

bool Stats::compare_structs(){
    for(auto &x : stat.importance_level){
        auto it = timeout_stat.importance_level.find(x.first);
        if(it == timeout_stat.importance_level.end())
            return false;
        if(x.second != it->second)
            return false;
    }
    return stat.total == timeout_stat.total &&
           stat.in_hour == timeout_stat.in_hour &&
           stat.min_size == timeout_stat.min_size && 
           stat.max_size == timeout_stat.max_size &&
           std::abs(stat.avg_size - timeout_stat.avg_size) < 1e-6;
}

void Stats::handle_time()
{
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::steady_clock::now() - last_check
    ).count();
    if(duration >= 60*60){                                  // если час прошел 
        stat.in_hour = 0;                                   // сбрасываем количество сообщений за час
        last_check = std::chrono::steady_clock::now();      // засекаем время
    }
    else stat.in_hour++;                                    // если час не прошел -> увеличиваем на 1
}

std::string Stats::parse_logger_level(const std::string &s)
{
    std::string lvl = "";
    auto it = s.find('[') + 6;
    while(s[it] != '['){
        lvl += s[it];
        it++;
    }
    return lvl; 
}
