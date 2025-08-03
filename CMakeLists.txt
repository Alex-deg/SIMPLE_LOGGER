cmake_minimum_required(VERSION 3.12)
project(simple_logger
    VERSION 1.0
    DESCRIPTION "C++ logging library with file and socket support"
    LANGUAGES CXX
)

# Настройки компилятора
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Поиск зависимостей
find_package(Threads REQUIRED)  # Добавлено здесь!

# Политики CMake
if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()

# Настройка выходных директорий
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Опция для выбора типа библиотеки
option(BUILD_SHARED_LIBS "Build shared libraries instead of static" OFF)

# Последовательная сборка всех компонентов
add_subdirectory(liblogger)
add_subdirectory(Functions_for_testing)
add_subdirectory(Testing_file_logger)
add_subdirectory(Testing_socket_logger)
add_subdirectory(unit_tests)