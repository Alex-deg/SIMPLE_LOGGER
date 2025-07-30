cmake_minimum_required(VERSION 3.10)

project(simple_logger)

set(SOURCES
    Testing_app/main.cpp
    liblogger/Logger.cpp
)

set(HEADERS
    liblogger/Logger.h
)

add_executable(simple_logger ${SOURCES} ${HEADERS})