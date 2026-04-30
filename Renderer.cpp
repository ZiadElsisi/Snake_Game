//
// Created by Ziad Elsisi on 30/04/2026.
//

#include "Renderer.h"
#include <iostream>
Renderer::Renderer(sf::RenderWindow& window)
    : window_(window)
{
    if (!font_.loadFromFile("assets/PressStart2P-Regular.ttf")) {
        // fallback (don’t crash)
        std::cerr << "Failed to load font\n";
    }
}

void Renderer::drawCell(const Cell& c, const sf::Color& color)
{
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(Constants::CELL_SIZE, Constants::CELL_SIZE));
    rect.setPosition(
        c.first * Constants::CELL_SIZE,
        c.second * Constants::CELL_SIZE
    );
    rect.setFillColor(color);

    window_.draw(rect);
}
void Renderer::drawGrid()
{
    sf::VertexArray lines(sf::Lines);

    for (int x = 0; x <= Constants::GRID_WIDTH; ++x) {
        float px = x * Constants::CELL_SIZE;
        lines.append(sf::Vertex(sf::Vector2f(px, 0), sf::Color(50,50,50)));
        lines.append(sf::Vertex(sf::Vector2f(px, Constants::GRID_HEIGHT * Constants::CELL_SIZE), sf::Color(50,50,50)));
    }

    for (int y = 0; y <= Constants::GRID_HEIGHT; ++y) {
        float py = y * Constants::CELL_SIZE;
        lines.append(sf::Vertex(sf::Vector2f(0, py), sf::Color(50,50,50)));
        lines.append(sf::Vertex(sf::Vector2f(Constants::GRID_WIDTH * Constants::CELL_SIZE, py), sf::Color(50,50,50)));
    }

    window_.draw(lines);
}
void Renderer::drawSidePanel(int score, int level, int highScore)
{
    float startX = Constants::GRID_WIDTH * Constants::CELL_SIZE + 10;

    auto makeText = [&](const std::string& str, int y) {
        sf::Text t(str, font_, 16);
        t.setPosition(startX, y);
        t.setFillColor(sf::Color::White);
        window_.draw(t);
    };

    makeText("SCORE: " + std::to_string(score), 50);
    makeText("LEVEL: " + std::to_string(level), 100);
    makeText("HIGH: " + std::to_string(highScore), 150);
}


void Renderer::drawGame(const Game& game, int highScore)
{

    drawGrid();

    // Snake
    bool isHead = true;
    for (const auto& s : game.getSnakeBody()) {
        drawCell(s, isHead ? sf::Color::Green : sf::Color(0,150,0));
        isHead = false;
    }

    // Food
    drawCell(game.getFoodPos(), sf::Color::Red);

    // Special food
    if (game.specialFoodActive()) {
        drawCell(game.getSpecialFoodPos(), sf::Color::Yellow);
    }

    // Obstacles
    for (const auto& o : game.getObstacles()) {
        drawCell(o, sf::Color(120,120,120));
    }

    drawSidePanel(game.getScore(),
                  game.getLevel(),
                  highScore);
}

void Renderer::drawOverlay(sf::Color color)
{
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(window_.getSize()));
    overlay.setFillColor(color);
    window_.draw(overlay);
}

void Renderer::drawPauseOverlay(){
    drawOverlay(sf::Color(0,0,0,150));

    sf::Text text("PAUSED", font_, 30);
    text.setPosition(200, 200);
    window_.draw(text);

}
void Renderer::drawGameOver(int finalScore, int highScore, bool isNewRecord)
{
    drawOverlay(sf::Color(0,0,0,150));

    sf::Text text("GAME OVER", font_, 30);
    text.setPosition(150, 150);
    window_.draw(text);

    sf::Text score("Score: " + std::to_string(finalScore), font_, 16);
    score.setPosition(150, 220);
    window_.draw(score);

    if (isNewRecord) {
        sf::Text rec("NEW RECORD!", font_, 16);
        rec.setFillColor(sf::Color::Yellow);
        rec.setPosition(150, 260);
        window_.draw(rec);
    }

}
void Renderer::drawMenu(const Menu& menu) {
    menu.draw(window_);
}
