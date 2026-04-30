#pragma once  // This is a header guard to prevent multiple inclusions of this file
#include "Shared.h"

class SpecialFood {  
public:
    SpecialFood();   
    void spawn(const Body& snakeBody, int gridW, int gridH);
    void deactivate();
    void tick(float deltaSeconds);
    Cell getPosition() const;
    bool isActive() const;
    float getRemainingTime() const;
// Static constants for points awarded and lifetime duration of the special food
    static const int POINTS;
    static const float LIFETIME;   

private:
    Cell position_;
    bool active_;
    float timeLeft_;
};
