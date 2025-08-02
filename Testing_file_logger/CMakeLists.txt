cmake_minimum_required(VERSION 3.10)

project(simple_logger)

set(SOURCES
    main.cpp
    ../liblogger/Logger.cpp
    ../Functions_for_testing/functions.cpp
)

set(HEADERS
    ../liblogger/Logger.h
    ../Functions_for_testing/functions.cpp
)

add_executable(simple_logger ${SOURCES} ${HEADERS})