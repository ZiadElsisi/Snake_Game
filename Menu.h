#pragma once
#include <SFML/Graphics.hpp>
#include <string>

// Number of menu options
static const int MENU_COUNT = 3;

class Menu {
public:
    // Constructor: needs window size to center items, and the high score to display
    Menu(float windowWidth, float windowHeight, int highScore);

    // Draw all menu items to the window
    void draw(sf::RenderWindow& window);

    // Handle keyboard input. Returns:
    //   -1   nothing selected yet (keep showing menu)
    //    0   "START GAME" confirmed
    //    1   "HIGH SCORES" confirmed
    //    2   "EXIT" confirmed
    int handleInput(sf::Event& event);

    // Update high score text (call this if the score changes)
    void setHighScore(int score);

private:
    sf::Font   font;                    // The loaded font
    sf::Text   items[MENU_COUNT];       // The 3 menu option texts
    sf::Text   highScoreText;           // High score display at bottom
    sf::Text   titleText;               // "SNAKE" title at top

    int        selectedIndex;           // Which item is currently highlighted (0-2)
    float      windowWidth;
    float      windowHeight;

    // Internal helper: reapply colors based on selectedIndex
    void updateColors();
};
