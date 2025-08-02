cmake_minimum_required(VERSION 3.10)

project(testing_client)

set(SOURCES
    sending_main.cpp
    ../../liblogger/Logger.cpp
    ../../Functions_for_testing/functions.cpp
)

set(HEADERS
    ../../liblogger/Logger.h
    ../../Functions_for_testing/functions.h
)

add_executable(testing_client ${SOURCES} ${HEADERS})