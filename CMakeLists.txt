cmake_minimum_required(VERSION 3.16)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "/opt/homebrew/opt/sfml@2/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(Snake_Game
        main.cpp
        game.cpp game.h
        Snake.h
        Food.h
        SpecialFood.h
        LevelManager.h
        InputHandler.cpp InputHandler.h
        Shared.h
)

target_link_libraries(Snake_Game sfml-graphics sfml-window sfml-system)
