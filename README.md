# Logger Library & Demo Applications

## Описание
Проект состоит из следующих компонентов:
- Библиотека liblogger для логирования
- Приложения для тестирования библиотеки:
  - file_logger_app - для тестирования класса FileLogger
  - logger_tests - unit тесты для класса FileLogger
  - socket_client_app и socket_server_app - для тестирования класса SocketLogger

Иерархия классов выглядит следующим образом:

classDiagram
    direction BT
    class ILogger {
        <<interface>>
        +debug(message: string)
        +info(message: string)
        +warning(message: string)
        +error(message: string)
        +fatal(message: string)
        +set_level(level: Levels)
        +now() string
        +write_log(message: string)
    }
    
    class Logger {
        -_level: Levels
        +debug(message: string)
        +info(message: string)
        +warning(message: string)
        +error(message: string)
        +fatal(message: string)
        +set_level(level: Levels)
        +get_level() Levels
        +now() string
        +write_log(message: string)
    }
    
    class FileLogger {
        -log_file: fstream
        +write_log(message: string)
    }
    
    class SocketLogger {
        -client_socket: int
        -_port: int
        +write_log(message: string)
        +set_nonblocking(fd: int) int
    }
    
    ILogger <|.. Logger : implements
    Logger <|-- FileLogger : extends
    Logger <|-- SocketLogger : extends


## Особенности
- Поддержка 5 уровней логирования: DEBUG, INFO, WARNING, ERROR, FATAL
- Два типа логгеров:
  - **FileLogger**: запись в текстовый файл
  - **SocketLogger**: отправка логов через TCP-сокет
- Формат логов: `[ВРЕМЯ] [УРОВЕНЬ] Сообщение`
- Цветное форматирование для консоли (ANSI-коды)
- Потокобезопасная обработка сообщений
- Система сбора статистики для SocketLogger:
  - Количество сообщений по уровням
  - Длина сообщений (мин/макс/средняя)
  - Фильтрация по времени (за последний час)
- Ежедневная очистка файловых логов (скрипт)
- Юнит-тесты для FileLogger

## Требования
- Компилятор с поддержкой C++17 (gcc 9+)
- CMake 3.12+
- Linux (тестировалось на Ubuntu/Debian)
- Библиотеки: pthread, rt

## Сборка проекта
```bash
git clone https://github.com/Alex-deg/SIMPLE_LOGGER.git
cd SIMPLE_LOGGER
mkdir build && cd build
cmake ..
make 
```

## Запуск приложений
