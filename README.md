# Snake Game

## Course

CSE333 - Data Structures and Algorithms  
Faculty of Engineering - Specialized Programs - Spring 2026

## Group Members

| Name | ID |
| --- | --- |
| Ziad Elsisi | TODO |
| TODO | TODO |
| TODO | TODO |
| TODO | TODO |
| TODO | TODO |

## Project Description

This project is a playable Snake Game implemented in C++ using SFML. The player controls a snake on a grid, collects food to increase the score, grows the snake body, and avoids collisions with the wall, obstacles, and itself.

The game includes a menu, pause state, game-over screen, score tracking, high-score saving, levels, normal food, and special food with a limited lifetime.

## Main Data Structures

### `deque<pair<int, int>>`

The snake body is stored as a `deque` of grid cells.

This data structure was chosen because the snake movement needs:

- fast insertion at the front for the new head position,
- fast removal from the back for the tail,
- ordered storage of all body segments.

This makes `deque` a suitable choice for modeling the snake body.

### `pair<int, int>`

Each grid location is represented as a pair of integers:

- `first` = x-coordinate
- `second` = y-coordinate

This is used for the snake, food, special food, and obstacles.

### `vector<Cell>`

Vectors are used to store obstacle positions and blocked cells when spawning food. This helps prevent food from appearing on the snake body, active special food, or obstacles.

## Core Features

- Main menu with start and exit options.
- Snake movement using keyboard controls.
- Food collection and snake growth.
- Score and high-score system.
- High score saved in `data/highscore.txt`.
- Special food that appears temporarily and gives extra points.
- Collision detection with walls, obstacles, and the snake body.
- Pause and resume support.
- Game-over screen with restart option.
- Level system with increasing speed.

## Controls

| Key | Action |
| --- | --- |
| `W` / `Up Arrow` | Move up |
| `S` / `Down Arrow` | Move down |
| `A` / `Left Arrow` | Move left |
| `D` / `Right Arrow` | Move right |
| `P` | Pause / resume |
| `Escape` | Return to menu |
| `Enter` | Select menu option |
| `R` | Reset after game over |

## System Design

The project is divided into multiple classes:

| Class | Responsibility |
| --- | --- |
| `Game` | Controls game state, score, movement, food collection, and collision detection. |
| `Snake` | Stores and updates the snake body. |
| `Food` | Handles normal food spawning. |
| `SpecialFood` | Handles timed special food spawning and expiration. |
| `Renderer` | Draws the grid, snake, food, menu, and overlays. |
| `InputHandler` | Handles keyboard input. |
| `LevelManager` | Manages level and movement speed. |
| `ScoreManager` | Loads and saves the high score. |
| `Menu` | Displays and handles the game menu. |

## Important Algorithms and Operations

### Snake Movement

For each move:

1. Compute the next head cell based on direction.
2. Insert the new head at the front of the deque.
3. Remove the tail if the snake did not eat food.
4. Keep the tail if food was eaten, which makes the snake grow.

Time complexity:

- Insert head: `O(1)`
- Remove tail: `O(1)`

### Collision Detection

The game checks:

- boundary collision,
- obstacle collision,
- self-collision.

Self-collision is checked by scanning the snake body.

Time complexity:

- Self-collision: `O(n)`, where `n` is the snake length.

### Food Respawn

Food is randomly generated on the grid, then checked against blocked cells. If the position is blocked, another random position is generated.

Blocked cells include:

- snake body,
- active special food,
- obstacles.

## Requirements

- C++17 or later
- CMake 3.16 or later
- SFML 2.5 or later

On this machine, the project is configured for Homebrew SFML:

```cmake
set(SFML_DIR "/opt/homebrew/opt/sfml@2/lib/cmake/SFML")
```

If SFML is installed in a different location, update `SFML_DIR` in `CMakeLists.txt`.

## How to Compile and Run

From the project folder:

```bash
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug
./cmake-build-debug/Snake_Game
```

If using an IDE such as CLion, open the project folder and run the `Snake_Game` target.

## Project Files

- `main.cpp` - program entry point and main game loop.
- `Game.cpp` / `Game.h` - game logic and state management.
- `Snake.cpp` / `Snake.h` - snake body and movement.
- `Food.cpp` / `Food.h` - normal food behavior.
- `SpecialFood.cpp` / `SpecialFood.h` - special food behavior.
- `Renderer.cpp` / `Renderer.h` - drawing and UI rendering.
- `InputHandler.cpp` / `InputHandler.h` - keyboard input.
- `Levelmanager.cpp` / `LevelManager.h` - level and speed management.
- `ScoreManager.cpp` / `ScoreManager.h` - high-score file handling.
- `Menu.cpp` / `Menu.h` - menu display and navigation.
- `Shared.h` - constants, enums, and shared type aliases.
- `data/highscore.txt` - saved high score.
- `assets/` - font files.

## AI Usage Declaration

AI tools were used during the project for:

- brainstorming project structure,
- debugging game behavior,
- improving code organization,
- fixing menu, speed, food spawning, and special food timing issues,
- preparing README and presentation content.

The group reviewed and modified AI suggestions before using them. Some AI suggestions were not directly suitable at first. For example, the special food timer was fixed to disappear, but then it appeared too frequently and stayed too long. The timing values and respawn behavior were adjusted manually after testing.

The group understands and implemented the main project logic, including:

- using `deque` for snake movement,
- checking collisions,
- spawning food safely,
- managing game states,
- saving high scores,
- and controlling rendering and input flow.

AI was used as a support tool, but the final project decisions, testing, and submitted implementation were reviewed by the group.

