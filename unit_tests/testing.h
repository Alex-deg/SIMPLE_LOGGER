#include <gtest/gtest.h>
#include "../liblogger/Logger.h"
#include <fstream>
#include <filesystem>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>

namespace fs = std::filesystem;
using namespace liblog;

// Функция для чтения файла
std::string read_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return "";
    }
    return std::string(std::istreambuf_iterator<char>(file),
                      std::istreambuf_iterator<char>());
}

// Функция для подсчета количества строк в файле
size_t count_lines(const std::string& filename) {
    std::ifstream file(filename);
    return std::count(std::istreambuf_iterator<char>(file),
                      std::istreambuf_iterator<char>(), '\n');
}

// Класс для тестирования FileLogger'a
class FileLoggerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Создание временного файла
        temp_file = "test_log.txt";
        // Если он уже существует -> удаляем
        if (fs::exists(temp_file)) {
            fs::remove(temp_file);
        }
    }

    void TearDown() override {
        // Чистим файл
        if (fs::exists(temp_file)) {
            fs::remove(temp_file);
        }
    }

    std::string temp_file;
};

// FileLogger tests

// Проверка конструктора, а именно его функциональности по открытию/созданию файла журнала
TEST_F(FileLoggerTest, ConstructorCreatesFile) {
    FileLogger logger(temp_file);
    EXPECT_TRUE(fs::exists(temp_file));
}

// Проверка на то, выбросит ли конструктор исключение, что файл не существует
TEST_F(FileLoggerTest, ConstructorThrowsOnInvalidPath) {
    EXPECT_THROW(FileLogger logger("/invalid/path/to/file.log"), std::invalid_argument);
}

// Проверка записи логов
TEST_F(FileLoggerTest, WriteLogCreatesContent) {
    {
        FileLogger logger(temp_file);
        logger.write_log("Test message"); // Напрямую пишем без уровней логирования, чтобы не делать лишнего
    }
    
    std::string content = read_file(temp_file); // Читаем файл
    EXPECT_FALSE(content.empty()); // И проверяем есть ли наше сообщение или нет
    EXPECT_NE(content.find("Test message"), std::string::npos);
}

// Проверка на фильтрацию логов по уровню логирования
TEST_F(FileLoggerTest, LogLevelFilteringWorks) {
    {
        FileLogger logger(temp_file, Levels::WARNING); // уровень логирования по умолчанию - WARNING
        logger.debug("Debug message");                 // то есть сообщения с уровнем ниже (DEBUG, INFO)
        logger.info("Info message");                   // печататься не должны
        logger.warning("Warning message");
        logger.error("Error message");
        logger.fatal("Fatal message");
    }
    
    std::string content = read_file(temp_file); // читаем файл
    EXPECT_EQ(count_lines(temp_file), 3); // должно выйти 3 записи с уровнями: WARNING, ERROR, FATAL
    EXPECT_EQ(content.find("Debug message"), std::string::npos);
    EXPECT_EQ(content.find("Info message"), std::string::npos);
    EXPECT_NE(content.find("Warning message"), std::string::npos);
    EXPECT_NE(content.find("Error message"), std::string::npos);
    EXPECT_NE(content.find("Fatal message"), std::string::npos);
}

// Проверка на то, содержит ли лог информацию о времени записи в журнал
TEST_F(FileLoggerTest, LogMessagesContainTimestamp) { 
    std::string test_message = "Timestamp test message";
    {
        FileLogger logger(temp_file);
        logger.fatal(test_message); // что-то записали в логи
    }
    
    std::string content = read_file(temp_file);

    EXPECT_TRUE(content.find("2025") == 0); // Проверяем на то есть ли год например
    EXPECT_NE(content.find(test_message), std::string::npos);
}

// Проверка на то, корректно ли присваивается новый уровень логирования по умолчанию
TEST_F(FileLoggerTest, SetLevelChangesLoggingBehavior) {
    {
        FileLogger logger(temp_file);
        logger.set_level(Levels::WARNING); // присваиваем новый уровень

        logger.info("This should not be logged"); // сообщение с INFO не должно записаться
        logger.error("This should be logged"); // сообщение с ERROR должно записаться
    }    
    std::string content = read_file(temp_file);
    EXPECT_EQ(content.find("This should not be logged"), std::string::npos);
    EXPECT_NE(content.find("This should be logged"), std::string::npos);
}