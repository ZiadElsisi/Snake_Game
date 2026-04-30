#pragma once
#include "Shared.h"
#include "Snake.h"
#include "Food.h"
#include "SpecialFood.h"
#include "LevelManager.h"
class Game {
public:
    Game();
    void reset();
    void update();
    GameState getState() const;
    const Body& getSnakeBody() const;
    Cell getFoodPos() const;
    bool specialFoodActive() const;
    Cell getSpecialFoodPos() const;
    float getSpecialFoodTime() const;
    int getScore() const;
    int getLevel() const;
    const std::vector<Cell>& getObstacles() const;
    void setHighScore(int hs);
    int getHighScore() const;
    void setDirection(Direction d);
    void setState(GameState s);
private:
    Snake        snake_;
    Food         food_;
    SpecialFood  specialFood_;
    LevelManager level_;
    Direction    currentDir_, pendingDir_;
    std::deque<Direction> dirBuffer_;
    GameState    state_;
    int          score_, highScore_;
    int          ticksSinceSpecial_;
    std::vector<Cell> obstacles_;
    bool validateDirection(Direction next, Direction current);
};
