//
// Created by Ziad Elsisi on 30/04/2026.
//
#pragma once
#include "Shared.h"
#include <SFML/Graphics.hpp>
class Renderer {
public:
    Renderer(sf::RenderWindow& window);
    void drawGame(const Body& snakeBody, const Cell& food,
                  bool specialActive, const Cell& specialFood, float specialTimeLeft,
                  int score, int level, int highScore,
                  const std::vector<Cell>& obstacles);
    void drawMenu(int selectedIndex, int highScore);
    void drawGameOver(int finalScore, int highScore, bool isNewRecord);
    void drawPause();
private:
    sf::RenderWindow& window_;
    sf::Font font_;
    // sf::RectangleShape, sf::CircleShape etc as reusable members
    void drawCell(const Cell& c, const sf::Color& color);
    void drawSidePanel(int score, int level, int highScore);
    void drawGrid();
};