cmake_minimum_required(VERSION 3.31)
project(cpp-budget-manager)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(cpp-budget-manager
        budget_manager.cpp
        budget_manager.h
        date.h
        main.cpp
        parser.cpp
        parser.h)
