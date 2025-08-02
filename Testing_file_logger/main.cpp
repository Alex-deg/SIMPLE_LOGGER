#include "../Functions_for_testing/functions.h"

int main(int argc, char* argv[]) {

    auto settings = parse_command_line_filelog(argc, argv); // получаем настройки из командной строки

    system("bash ../scripts/clear_log_journal.sh"); // запускаем скрипт очистки журнала логов

    std::shared_ptr<FileLogger> file_log = std::make_shared<FileLogger>(settings.first, settings.second);

    start_testing(file_log); // ручное тестирование 
}