cmake_minimum_required(VERSION 3.27)
project(Lotto_Program)

set(CMAKE_CXX_STANDARD 23)

add_executable(Lotto_Program main.cpp
        lottoclasses.h
        lottologic.cpp)
