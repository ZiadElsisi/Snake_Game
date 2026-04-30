
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
    int highScore = scoreManager.load();
    InputHandler  inputHandler(game);
    Menu          menu(WINDOW_W, WINDOW_H, highScore);


    menu.setHighScore(highScore);
    game.setHighScore(highScore);

    // 3.  Fixed-timestep (tick) variables

    sf::Clock clock;
    float moveTimer = 0.f;
    bool scoreSaved = false;

    // 4.  Main game loop

    while (window.isOpen())
    {

        // ✅ Delta time once per frame, OUTSIDE the event loop
        float deltaTime = clock.restart().asSeconds();
        moveTimer += deltaTime;
        sf::Event event;
        while (window.pollEvent(event))

        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (game.getState() == GameState::MENU || game.getState() == GameState::GAME_OVER)
            {
                int result = menu.handleInput(event);

                if (result == 0) // START
                {
                    game.reset();
                    levelManager.reset();
                    game.setState(GameState::PLAYING);
                    moveTimer = 0.f;
                    scoreSaved = false;
                }
                else if (result == 2) // EXIT
                {
                    window.close();
                }
            }
            else
            {
                // FIX 2: pass the live event to inputHandler INSIDE the loop
                inputHandler.processEvent(event);
            }
        }
        //  4c. State machine
        switch (game.getState())
        {

        case GameState::MENU:
        {
            menu.setTitle("SNAKE");

            // Render menu
            window.clear(sf::Color::Black);
            renderer.drawMenu(menu);
            window.display();
            break;
        }


        case GameState::PLAYING:

        {
            //  Pause toggle

            // Fixed-timestep update (tick system)
            // Speed (ticks/sec) may increase as the level grows

            if (moveTimer >= game.getTickInterval())
            {
                game.update();
                moveTimer = 0.f;
            }

            if (game.getState() != GameState::PLAYING) break; // state changed inside loop

            //  Render
            window.clear(sf::Color::Black);
            renderer.drawGame(game, game.getHighScore());
            window.display();
            break;
        }
        case GameState::PAUSED:

        {
            // Resume on pause key press

            // Render the paused view (game board dimmed + overlay)
            window.clear(sf::Color::Black);
            renderer.drawGame(game, game.getHighScore());
            renderer.drawPauseOverlay();
            window.display();
            break;
        }

            case GameState::GAME_OVER:
        {
            // Save score
            if (!scoreSaved) {
                scoreManager.save(game.getScore());
                scoreSaved = true;
            }

            // Update high score everywhere
            int updatedHigh = scoreManager.load();
            menu.setHighScore(updatedHigh);
            game.setHighScore(updatedHigh);
            menu.setTitle("GAME OVER");

            window.clear(sf::Color::Black);
            renderer.drawMenu(menu);
            window.display();
            break;
        }

        } // end switch

        // 4d. Clear per-frame input state

    } // end while(window.isOpen())

    return 0;
}
