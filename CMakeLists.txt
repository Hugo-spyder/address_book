cmake_minimum_required(VERSION 3.15)
project(address_book)

set(CMAKE_CXX_STANDARD 14)

add_executable(address_book main.cpp people.h people.cpp User.h User.cpp)
