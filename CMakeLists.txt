cmake_minimum_required(VERSION 3.24)
project(CPP2_s21_containers_2)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(CPP2_s21_containers_2
        src/s21_list.tpp
        src/s21_list.h
        ##src/main.cpp
        src/test_list.cc
        src/s21_array.h
        src/test_array.cc)

target_link_libraries(CPP2_s21_containers_2 gtest)
