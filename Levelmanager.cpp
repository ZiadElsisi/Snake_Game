#include "LevelManager.h"

const float LevelManager::BASE_INTERVAL = 1.0f / 10.0f; // 0.10 s  to 10 moves/sec
const float LevelManager::SPEED_FACTOR  = 0.88f;         // 12% faster each level
const float LevelManager::MIN_INTERVAL  = 0.05f;         // 0.05 s  to 20 moves/sec (cap)

//  Constructor Sets the game to its initial state: level 1, base speed.
LevelManager::LevelManager()
    : level_(1), tickInterval_(BASE_INTERVAL)
{}

//  reset() Restores everything to the starting state.
//  Call this when the player starts a new game.
void LevelManager::reset()
{
    level_        = 1;
    tickInterval_ = BASE_INTERVAL;
}

//  update(score) Called every time the score changes.

//  Level formula:
//      level = score / 5 + 1          (integer division)
//
//      score  0- 4  →  level 1
//      score  5- 9  →  level 2
//      score 10-14  →  level 3  … and so on.
//
//  Speed formula:
//      tickInterval = max(MIN_INTERVAL,
//                         BASE_INTERVAL * pow(SPEED_FACTOR, level - 1))
//
//      At level 1: BASE_INTERVAL * 0.88^0 = 0.10  s
//      At level 2: BASE_INTERVAL * 0.88^1 = 0.088 s  (+12% faster)
//      At level 3: BASE_INTERVAL * 0.88^2 = 0.077 s
//      … capped at MIN_INTERVAL so it never becomes unplayable.

void LevelManager::update(int score)
{
    // 1. Derive level from score
    level_ = score / 5 + 1;

    //  2. Derive tick interval from level
    float rawInterval = BASE_INTERVAL
                        * static_cast<float>(std::pow(SPEED_FACTOR, level_ - 1));

    //  Clamp: never go below the minimum (would be too fast to play).
    tickInterval_ = std::max(MIN_INTERVAL, rawInterval);
}

//  Getters

int LevelManager::getLevel() const
{
    return level_;
}

float LevelManager::getTickInterval() const
{
    return tickInterval_;
}



//  addObstacleWalls(obstacles, level)
//  Appends a fixed, hardcoded wall pattern to `obstacles` depending on the
//  level passed in.  The caller decides when to clear the vector (e.g. only
//  on level-up) — this method only ever *adds* cells, never removes them.

//  Pattern summary
//  Level 1–2 : no obstacles
//  Level 3   : short horizontal bar (center of grid)
//  Level 4   : short vertical bar   (center of grid)
//  Level 5+  : hollow 3×3 box       (center of grid)

//  All coordinates are expressed as {row, col} grid cells.
//  Assumes a grid at least 10 cells wide/tall (standard Snake grids are 20×20+).

void LevelManager::addObstacleWalls(std::vector<Cell>& obstacles, int level)
{
    // Compute the approximate center of the grid.
    // GRID_SIZE is expected to be defined in Shared.h (e.g. const int GRID_SIZE = 20).
   const int mid = Constants::GRID_WIDTH / 2;  // e.g. 10 for a 20×20 grid

    if (level == 3)
    {
        //  Horizontal bar
        //  Spans 5 cells across the middle row.

        for (int col = mid - 2; col <= mid + 2; ++col)
        {
            obstacles.push_back({ mid, col });
        }
    }
    else if (level == 4)
    {
        // Vertical bar
        //  Spans 5 cells down the middle column.
        for (int row = mid - 2; row <= mid + 2; ++row)
        {
            obstacles.push_back({ row, mid });
        }
    }
    else if (level >= 5)
    {
        // Hollow 3×3 box
        //  8 border cells of a 3×3 square; center cell left open so the
        //  snake can (just barely) navigate around it.

        for (int row = mid - 1; row <= mid + 1; ++row)
        {
            for (int col = mid - 1; col <= mid + 1; ++col)
            {
                // Skip the very center — keep it passable.
                if (row == mid && col == mid)
                    continue;

                obstacles.push_back({ row, col });
            }
        }
    }
    // Levels 1–2: nothing added; the board stays clear.
}