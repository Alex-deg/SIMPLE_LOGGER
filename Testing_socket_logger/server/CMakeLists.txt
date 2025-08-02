cmake_minimum_required(VERSION 3.10)

project(testing_server)

set(SOURCES
    reading_main.cpp
    server.cpp
    ../../liblogger/Logger.cpp
    ../libstatistics/statistic.cpp
)

set(HEADERS
    server.h
    ../../liblogger/Logger.h
    ../libstatistics/statistic.h
)

add_executable(testing_server ${SOURCES} ${HEADERS})