// SFML included only here — keeps the header SFML-free
#include <SFML/Graphics.hpp>
#include "Shared.h"
#include "Game.h"
#include "InputHandler.h"

InputHandler::InputHandler(Game& game)
    : game_(game)
    , clockAccum_(0.f)
{}

void InputHandler::processEvents(sf::RenderWindow& window)
{
    sf::Event e;
    while (window.pollEvent(e))
    {
        // ── Window close ─────────────────────────────────────────────────
        if (e.type == sf::Event::Closed)
            window.close();

        // ── Key press ────────────────────────────────────────────────────
        if (e.type == sf::Event::KeyPressed)
        {
            GameState state = game_.getState();

            switch (e.key.code)
            {
                // Direction — only when playing
                case sf::Keyboard::W: case sf::Keyboard::Up:
                    game_.setDirection(Direction::UP);    break;
                case sf::Keyboard::S: case sf::Keyboard::Down:
                    game_.setDirection(Direction::DOWN);  break;
                case sf::Keyboard::A: case sf::Keyboard::Left:
                    game_.setDirection(Direction::LEFT);  break;
                case sf::Keyboard::D: case sf::Keyboard::Right:
                    game_.setDirection(Direction::RIGHT); break;

                // R — reset only on GAME_OVER
                case sf::Keyboard::R:
                    if (state == GameState::GAME_OVER)
                        game_.reset();
                    break;

                // P — toggle PLAYING / PAUSED
                case sf::Keyboard::P:
                    if (state == GameState::PLAYING)
                        game_.setState(GameState::PAUSED);
                    else if (state == GameState::PAUSED)
                        game_.setState(GameState::PLAYING);
                    break;

                // Escape — return to menu
                case sf::Keyboard::Escape:
                    game_.setState(GameState::MENU);
                    break;

                default: break;
            }
        }
    }
}

void InputHandler::tick()
{
    // Tick interval comes from LevelManager via game level
    // Reconstruct interval: base speed + 0.5 per level above 1
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