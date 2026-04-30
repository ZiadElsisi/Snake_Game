#include <SFML/Graphics.hpp>
#include "Shared.h"
#include "Game.h"
#include "InputHandler.h"

InputHandler::InputHandler(Game& game)
    : game_(game)
    , clockAccum_(0.f)
{}

// Called once per event from main's pollEvent loop
void InputHandler::processEvent(const sf::Event& e)
{
    if (e.type != sf::Event::KeyPressed) return;

    GameState state = game_.getState();

    switch (e.key.code)
    {
        case sf::Keyboard::W: case sf::Keyboard::Up:
            game_.setDirection(Direction::UP);    break;
        case sf::Keyboard::S: case sf::Keyboard::Down:
            game_.setDirection(Direction::DOWN);  break;
        case sf::Keyboard::A: case sf::Keyboard::Left:
            game_.setDirection(Direction::LEFT);  break;
        case sf::Keyboard::D: case sf::Keyboard::Right:
            game_.setDirection(Direction::RIGHT); break;

        case sf::Keyboard::R:
            if (state == GameState::GAME_OVER)
                game_.reset();
            break;

        case sf::Keyboard::P:
            if (state == GameState::PLAYING)
                game_.setState(GameState::PAUSED);
            else if (state == GameState::PAUSED)
                game_.setState(GameState::PLAYING);
            break;

        case sf::Keyboard::Escape:
            game_.setState(GameState::MENU);
            break;

        default: break;
    }
}

void InputHandler::tick()
{
    float interval = 1.f / (Constants::INIT_SPEED +
                             static_cast<float>(game_.getLevel() - 1) * 0.5f);

    static sf::Clock clock;
    clockAccum_ += clock.restart().asSeconds();

    while (clockAccum_ >= interval) {
        clockAccum_ -= interval;
        if (game_.getState() == GameState::PLAYING)
            game_.update();
    }
}