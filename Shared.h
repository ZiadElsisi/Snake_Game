#pragma once
#include <deque>
#include <utility>
#include <vector>
using namespace std;
// ── Constants
namespace Constants {
    const int GRID_WIDTH    = 20;
    const int GRID_HEIGHT   = 20;
    const int CELL_SIZE     = 32;   // pixels per cell
    const int PANEL_WIDTH   = 200;  // right side panel
    const float INIT_SPEED  = 10.f; // ticks per second
}

// ── Enums
enum class Direction { UP, DOWN, LEFT, RIGHT };
enum class GameState { MENU, PLAYING, PAUSED, GAME_OVER };

// ── Type aliases
using Cell = pair<int,int>; // Best Data Structure For Cordinates
using Body = deque<Cell>;

// ── Forward declarations (implementations in .cpp)
class Snake;
class Food;
class SpecialFood;
class LevelManager;
class Game;
class Renderer;
class InputHandler;
class ScoreManager;
class Menu;