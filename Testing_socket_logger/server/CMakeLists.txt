cmake_minimum_required(VERSION 3.10)

project(simple_logger)

set(SOURCES
    reading_main.cpp
    server.cpp
    ../../liblogger/Logger.cpp
)

set(HEADERS
    server.h
    ../../liblogger/Logger.h
)

add_executable(simple_logger ${SOURCES} ${HEADERS})