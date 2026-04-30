cmake_minimum_required(VERSION 3.16)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(Snake_Game
        main.cpp
        game.cpp game.h
        Snake.h
        Food.h
        SpecialFood.h
        LevelManager.h
        InputHandler.cpp InputHandler.h
        Shared.h
         Food.cpp
        SpecialFood.cpp
)
