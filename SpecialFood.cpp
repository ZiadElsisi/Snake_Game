#include "SpecialFood.h"
#include <random>

// Static constants
const int SpecialFood::POINTS = 2;
const float SpecialFood::LIFETIME = 3.0f;

// Static random engine - seeded once
static std::mt19937 g_rng_special(std::random_device{}());

SpecialFood::SpecialFood() : position_(0, 0), active_(false), timeLeft_(0.0f) {
}

void SpecialFood::spawn(const Body& snakeBody, int gridW, int gridH) {
    std::uniform_int_distribution<int> distX(0, gridW - 1);
    std::uniform_int_distribution<int> distY(0, gridH - 1);
// We need to ensure the new position is not on the snake's body
    Cell newPosition;
    bool positionValid = false;

    // Keep generating random positions until we find one not in snakeBody
    while (!positionValid) {
        newPosition = {distX(g_rng_special), distY(g_rng_special)};  // Generate a random position within the grid

        positionValid = true;
        for (const auto& segment : snakeBody) {
            if (segment == newPosition) {
                positionValid = false;
                break; // If the new position is on the snake's body, we need to generate a new one
            }
        }
    }

    position_ = newPosition;
    active_ = true;
    timeLeft_ = LIFETIME;  // Reset the remaining time to the full lifetime when spawning
}

void SpecialFood::deactivate() {
    active_ = false;
    timeLeft_ = 0.0f;   // When deactivating, we also reset the remaining time to 0
}

void SpecialFood::tick(float deltaSeconds) {
    if (!active_) {   // If the special food is not active, we don't need to do anything
        return;
    }

    timeLeft_ -= deltaSeconds;
    if (timeLeft_ <= 0.0f) {
        deactivate();
    }
}

Cell SpecialFood::getPosition() const {
    return position_;
}

bool SpecialFood::isActive() const {
    return active_;
}

float SpecialFood::getRemainingTime() const {
    return timeLeft_;
}
