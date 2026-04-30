#pragma once

#include "Shared.h"
#include <vector>
#include <cmath>

class LevelManager {
public:
    //  Lifecycle
    LevelManager();   // Initialises to level 1, base speed
    void reset();     // Restores level 1, base speed (call on new game)

    // Called every time score changes
    // Recomputes level and tickInterval from the new score.
    void update(int score);

    // Getters
    int   getLevel()        const;  // Current level (1-based)
    float getTickInterval() const;  // Seconds between snake moves

    // Obstacle generation
    // Appends fixed wall cells for the given level into `obstacles`.
    // No obstacles are added for levels 1–2.
    // The caller owns the vector and may clear it between levels.
    void addObstacleWalls(std::vector<Cell>& obstacles, int level);

private:
    int   level_;         // Current level (always >= 1)
    float tickInterval_;  // Seconds per snake tick (lower = faster)

    // Tuning constants
    static const float BASE_INTERVAL; // Starting speed  (0.10 s  to 10 ticks/s)
    static const float SPEED_FACTOR;  // Per-level multiplier (0.88 to 12% faster/level)
    static const float MIN_INTERVAL;  // Speed cap       (0.05 s  to 20 ticks/s)
};