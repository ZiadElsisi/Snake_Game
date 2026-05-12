#pragma once

#include "Shared.h"
#include <vector>
#include <cmath>

class LevelManager {
public:
    LevelManager();
    void reset();
    void update(int score);

    int   getLevel()        const;  // Current level (1-based)
    float getTickInterval() const;  // Seconds between snake moves

    void addObstacleWalls(std::vector<Cell>& obstacles, int level);

private:
    int   level_;
    float tickInterval_;

    // Tuning constants
    static const float BASE_INTERVAL; // Starting speed  (0.10 s  to 10 ticks/s)
    static const float SPEED_FACTOR;  // Per-level multiplier (0.88 to 12% faster/level)
    static const float MIN_INTERVAL;  // Speed cap       (0.05 s  to 20 ticks/s)
};