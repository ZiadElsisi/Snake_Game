cmake_minimum_required(VERSION 3.1)
project(Snake_Game_)

set(CMAKE_CXX_STANDARD 20)

add_executable(Snake_Game_ main.cpp
        Shared.h
        Food.cpp
        Food.h
        SpecialFood.cpp
        SpecialFood.h)

add_executable(FoodTest FoodTest.cpp
        Food.cpp
        Food.h
        SpecialFood.cpp
        SpecialFood.h
        Shared.h)
