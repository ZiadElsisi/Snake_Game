cmake_minimum_required(VERSION 3.16)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)

# ── Auto-download SFML (no manual install needed) ─────────────────────────────
include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        2.6.1
)
set(SFML_BUILD_AUDIO    OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK  OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SFML)

# ── Executable ────────────────────────────────────────────────────────────────
add_executable(SnakeGame
        main.cpp
        Game.cpp
        InputHandler.cpp
)

# ── Project headers ───────────────────────────────────────────────────────────
target_include_directories(SnakeGame PRIVATE ${CMAKE_SOURCE_DIR})

# ── Link SFML ─────────────────────────────────────────────────────────────────
target_link_libraries(SnakeGame PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
)