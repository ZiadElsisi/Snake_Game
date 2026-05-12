#pragma once
#include <SFML/Graphics.hpp>
#include <string>

// Number of menu options
static const int MENU_COUNT = 2;

class Menu {
public:
    Menu(float windowWidth, float windowHeight, int highScore);
    void draw(sf::RenderWindow& window) const;
    int handleInput(sf::Event& event);

    void setHighScore(int score);
    void setTitle(const std::string& title);

private:
    sf::Font   font;                    // The loaded font
    sf::Text   items[MENU_COUNT];
    sf::Text   highScoreText;           // High score display at bottom
    sf::Text   titleText;               // "SNAKE" title at top

    int        selectedIndex;
    float      windowWidth;
    float      windowHeight;

    // Internal helper: reapply colors based on selectedIndex
    void updateColors();
};
