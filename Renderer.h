#pragma once
#include "Shared.h"
#include "Game.h"
#include "LevelManager.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>

class Renderer {
public:
    Renderer(sf::RenderWindow& window);

    void drawGame(const Game& game, int highScore);

    void drawMenu(const Menu& menu);
    void drawGameOver(int finalScore, int highScore);
    void drawPauseOverlay();
    void drawGameOver(int finalScore, int highScore, bool isNewRecord);
    void drawOverlay(sf::Color color);
private:
    sf::RenderWindow& window_;
    sf::Font font_;

    void drawCell(const Cell& c, const sf::Color& color);
    void drawSidePanel(int score, int level, int highScore);
    void drawGrid();
};
