#pragma once
#include "Shared.h"
// Food class represents the regular food in the snake game. It can respawn at random locations on the grid, ensuring it does not spawn on the snake's body. It has a position and an active state.
class Food {
public:    
    Food(); 
    void respawn(const Body& snakeBody, int gridW, int gridH);
    Cell getPosition() const;
    bool isActive() const;
 
private:
    Cell position_;
    bool active_;
};
