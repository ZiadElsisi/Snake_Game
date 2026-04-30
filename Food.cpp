#include "Food.h"
#include <random>

// Static random engine - seeded once
static std::mt19937 g_rng(std::random_device{}());

Food::Food() : position_(0, 0), active_(false) {
}   // Note: The constructor initializes the food as inactive and at position (0, 0)

void Food::respawn(const Body& snakeBody, int gridW, int gridH) {
    std::uniform_int_distribution<int> distX(0, gridW - 1);
    std::uniform_int_distribution<int> distY(0, gridH - 1);
    // We need to ensure the new position is not on the snake's body
    Cell newPosition;
    bool positionValid = false;  // Flag to check if the generated position is valid (not on snake body)

    // Keep generating random positions until we find one not in snakeBody
    while (!positionValid) {
        newPosition = {distX(g_rng), distY(g_rng)};

        positionValid = true;
        for (const auto& segment : snakeBody) {
            if (segment == newPosition) {
                positionValid = false;
                break;   // If the new position is on the snake's body, we need to generate a new one
            }
        }
    }

    position_ = newPosition;
    active_ = true;  // Once we have a valid position, we set the food to active
}

Cell Food::getPosition() const {
    return position_;
}

bool Food::isActive() const {
    return active_;
}
