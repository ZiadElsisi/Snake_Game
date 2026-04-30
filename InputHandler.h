#pragma once
#include "Shared.h"
#include "Game.h"

// Forward-declare sf::RenderWindow so this header compiles without SFML
namespace sf { class RenderWindow; }

class InputHandler {
public:
    explicit InputHandler(Game& game);

    // Call every frame — handles window events and key presses
    void processEvents(sf::RenderWindow& window);

    // Call every frame — fires game.update() on tick interval
    void tick();

private:
    Game& game_;
    float clockAccum_;  // accumulated seconds since last tick
};