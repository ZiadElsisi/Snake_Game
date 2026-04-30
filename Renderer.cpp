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


void Renderer::drawGame(const Body& snakeBody, const Cell& food,
                       bool specialActive, const Cell& specialFood, float specialTimeLeft,
                       int score, int level, int highScore,
                       const std::vector<Cell>& obstacles)
{
    window_.clear(sf::Color(20, 20, 20));

    // Background (grid area)
    sf::RectangleShape bg;
    bg.setSize(sf::Vector2f(
        Constants::GRID_WIDTH * Constants::CELL_SIZE,
        Constants::GRID_HEIGHT * Constants::CELL_SIZE
    ));
    bg.setFillColor(sf::Color(30,30,30));
    window_.draw(bg);

    drawGrid();

    // Obstacles
    for (const auto& o : obstacles)
        drawCell(o, sf::Color(100,100,100));

    // Snake
    bool isHead = true;
    for (const auto& segment : snakeBody) {
        if (isHead) {
            drawCell(segment, sf::Color(0, 255, 0)); // bright
            isHead = false;
        } else {
            drawCell(segment, sf::Color(0, 150, 0));
        }
    }

    // Food
    sf::CircleShape foodShape(Constants::CELL_SIZE / 2 - 4);
    foodShape.setFillColor(sf::Color::Red);
    foodShape.setPosition(
        food.first * Constants::CELL_SIZE + 4,
        food.second * Constants::CELL_SIZE + 4
    );
    window_.draw(foodShape);

    // Special food (blink when < 2s)
    if (specialActive) {
        bool blink = (specialTimeLeft < 2.0f) &&
                     (static_cast<int>(specialTimeLeft * 10) % 2 == 0);

        if (!blink || specialTimeLeft >= 2.0f) {
            sf::CircleShape special(Constants::CELL_SIZE / 2 - 4);
            special.setFillColor(sf::Color(255, 215, 0)); // gold
            special.setPosition(
                specialFood.first * Constants::CELL_SIZE + 4,
                specialFood.second * Constants::CELL_SIZE + 4
            );
            window_.draw(special);
        }
    }

    drawSidePanel(score, level, highScore);

    window_.display();
}
void drawOverlay(sf::RenderWindow& window, sf::Color color)
{
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(window.getSize()));
    overlay.setFillColor(color);
    window.draw(overlay);
}
void Renderer::drawPause()
{
    drawOverlay(window_, sf::Color(0,0,0,150));

    sf::Text text("PAUSED", font_, 30);
    text.setPosition(200, 200);
    window_.draw(text);

    window_.display();
}
void Renderer::drawGameOver(int finalScore, int highScore, bool isNewRecord)
{
    drawOverlay(window_, sf::Color(0,0,0,180));

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

    window_.display();
}
