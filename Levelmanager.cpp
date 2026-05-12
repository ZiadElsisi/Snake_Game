#include "LevelManager.h"
#include <algorithm>

const float LevelManager::BASE_INTERVAL = 0.12f; // about 8 moves/sec
const float LevelManager::SPEED_FACTOR  = 0.92f; // 8% faster each level
const float LevelManager::MIN_INTERVAL  = 0.06f; // cap at about 16 moves/sec

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
