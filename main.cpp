
#include <SFML/Graphics.hpp>
#include "Shared.h"
#include "ScoreManager.h"
#include "LevelManager.h"
#include "Menu.h"
#include "Game.h"
#include "Renderer.h"
#include "InputHandler.h"

int main()
{
    // 1.  Create the SFML window

    const unsigned int WINDOW_W = Constants::GRID_WIDTH  * Constants::CELL_SIZE
                                + Constants::PANEL_WIDTH;
    const unsigned int WINDOW_H = Constants::GRID_HEIGHT * Constants::CELL_SIZE;

    sf::RenderWindow window(
        sf::VideoMode(WINDOW_W, WINDOW_H),
        "Snake Game",
        sf::Style::Titlebar | sf::Style::Close
    );
    window.setFramerateLimit(60);

    // 2.  Initialise core objects
    ScoreManager  scoreManager;
    LevelManager  levelManager;
    Game          game;
    Renderer      renderer(window);
    InputHandler  inputHandler;
    Menu          menu;

    // Load the persisted high score at startup
    scoreManager.loadHighScore();

    // Starting game state
    GameState state = GameState::MENU;

    // 3.  Fixed-timestep (tick) variables

    sf::Clock clock;
    float     accumulator = 0.f;   // seconds accumulated since last tick

    // 4.  Main game loop

    while (window.isOpen())
    {
        // 4a. Delta time
        float deltaTime = clock.restart().asSeconds();
        // Clamp to avoid spiral-of-death on lag spikes
        if (deltaTime > 0.2f) deltaTime = 0.2f;

        //  4b. Event polling
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Pass every event to the input handler so it can
            // record key presses for this frame
            inputHandler.handleEvent(event);
        }

        //  4c. State machine
        switch (state)
        {

        case GameState::MENU:
        {
            // Let the menu react to Up / Down / Enter
            menu.handleInput(inputHandler);

            if (menu.isStartSelected())
            {
                // Reset everything for a fresh run
                game.reset();
                levelManager.reset();
                accumulator = 0.f;
                state = GameState::PLAYING;
            }
            else if (menu.isExitSelected())
            {
                window.close();
            }

            // Render menu
            window.clear(sf::Color::Black);
            renderer.drawMenu(menu, scoreManager.getHighScore());
            window.display();
            break;
        }


        case GameState::PLAYING:

        {
            //  Pause toggle
            if (inputHandler.isPausePressed())
            {
                state = GameState::PAUSED;
                break;
            }

            // Pass directional input to game
            Direction dir = inputHandler.getDirection();
            game.setDirection(dir);

            // Fixed-timestep update (tick system)
            // Speed (ticks/sec) may increase as the level grows
            float tickInterval = 1.f / levelManager.getSpeed();
            accumulator += deltaTime;

            while (accumulator >= tickInterval)
            {
                game.update();          // advance snake, check food, etc.
                accumulator -= tickInterval;

                // Update level based on current score
                levelManager.update(game.getScore());

                // Did the snake die this tick?
                if (game.isGameOver())
                {
                    // Persist high score then switch state
                    scoreManager.updateHighScore(game.getScore());
                    scoreManager.saveHighScore();
                    state = GameState::GAME_OVER;
                    break;              // exit the tick loop
                }
            }

            if (state != GameState::PLAYING) break; // state changed inside loop

            //  Render
            window.clear(sf::Color::Black);
            renderer.drawGame(game, levelManager, scoreManager.getHighScore());
            window.display();
            break;
        }
        case GameState::PAUSED:

        {
            // Resume on pause key press
            if (inputHandler.isPausePressed())
            {
                // Reset clock so the pause duration isn't added
                // to the accumulator on resume
                clock.restart();
                accumulator = 0.f;
                state = GameState::PLAYING;
            }

            // Render the paused view (game board dimmed + overlay)
            window.clear(sf::Color::Black);
            renderer.drawGame(game, levelManager, scoreManager.getHighScore());
            renderer.drawPauseOverlay();
            window.display();
            break;
        }

        case GameState::GAME_OVER:

        {
            // Any key (e.g. Enter / Space) returns to menu
            if (inputHandler.isConfirmPressed())
            {
                menu.reset();
                state = GameState::MENU;
            }

            // Render game-over screen
            window.clear(sf::Color::Black);
            renderer.drawGameOver(game.getScore(), scoreManager.getHighScore());
            window.display();
            break;
        }

        } // end switch

        // 4d. Clear per-frame input state
        inputHandler.reset();

    } // end while(window.isOpen())

    return 0;
}