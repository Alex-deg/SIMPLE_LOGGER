cmake_minimum_required(VERSION 3.14)
project(logger_tests)

# Устанавливаем стандарт C++ (C++17 или новее)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -g -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
    add_custom_target(coverage
        COMMAND lcov --capture --directory . --output-file coverage.info
        COMMAND genhtml coverage.info --output-directory coverage_report
        DEPENDS logger_tests
    )
endif()

# Включаем автоматическое скачивание и настройку Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Добавляем наш основной проект (если нужно)
# add_subdirectory(../src ${CMAKE_CURRENT_BINARY_DIR}/src)

# Создаем исполняемый файл для тестов
add_executable(
  logger_tests
  main_test.cpp  # Файл с тестами, который мы написали
  ../liblogger/Logger.cpp  # Путь к исходникам тестируемых классов
)

# Подключаем зависимости
target_include_directories(logger_tests PRIVATE 
  ${CMAKE_SOURCE_DIR}/liblogger  # Путь к заголовочным файлам
  ${gtest_SOURCE_DIR}/include
  ${gmock_SOURCE_DIR}/include
)

# Подключаем системные библиотеки для работы с сокетами
if(UNIX)
  target_link_libraries(logger_tests PRIVATE pthread)
endif()

# Подключаем Google Test
target_link_libraries(
  logger_tests
  PRIVATE
  gtest_main
  gmock
)

# Добавляем цель для запуска тестов
enable_testing()
add_test(
  NAME logger_tests
  COMMAND logger_tests
)