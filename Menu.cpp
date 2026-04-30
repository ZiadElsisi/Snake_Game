#include "Menu.h"
#include <iostream>

// Colors
static const sf::Color COLOR_SELECTED  = sf::Color(50, 220, 50);   // bright green
static const sf::Color COLOR_NORMAL    = sf::Color(160, 160, 160); // dim gray
static const sf::Color COLOR_TITLE     = sf::Color(255, 255, 255); // white
static const sf::Color COLOR_HIGHSCORE = sf::Color(255, 215, 0);   // gold

//  Constructor
Menu::Menu(float windowWidth, float windowHeight, int highScore)
    : selectedIndex(0),
      windowWidth(windowWidth),
      windowHeight(windowHeight)
{
    //  1. Load Font
    if (!font.loadFromFile("arial.ttf")) {
        // If loading fails, print a warning. The game won't crash but text won't show.
        std::cerr << "[Menu] ERROR: Could not load font 'arial.ttf'!\n";
        std::cerr << "       Place arial.ttf next to your executable.\n";
    }

    // 2. Setup Title
    titleText.setFont(font);
    titleText.setString("SNAKE");
    titleText.setCharacterSize(72);
    titleText.setFillColor(COLOR_TITLE);
    titleText.setStyle(sf::Text::Bold);
    // Center title horizontally, place in upper area
    float titleX = (windowWidth - titleText.getGlobalBounds().width) / 2.f;
    titleText.setPosition(titleX, windowHeight * 0.12f);

    //  3. Setup Menu Options
    const std::string labels[MENU_COUNT] = {
        "START GAME",
        "HIGH SCORES",
        "EXIT"
    };

    // Vertical spacing: start at 40% of screen height, each item 80px below
    float startY  = windowHeight * 0.40f;
    float spacingY = 80.f;

    for (int i = 0; i < MENU_COUNT; i++) {
        items[i].setFont(font);
        items[i].setString(labels[i]);
        items[i].setCharacterSize(36);
        // Default color (will be updated by updateColors() below)
        items[i].setFillColor(COLOR_NORMAL);

        // Center each item horizontally
        float textWidth = items[i].getGlobalBounds().width;
        float x = (windowWidth - textWidth) / 2.f;
        float y = startY + i * spacingY;
        items[i].setPosition(x, y);
    }

    //  4. Setup High Score Text
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(24);
    highScoreText.setFillColor(COLOR_HIGHSCORE);
    setHighScore(highScore); // This sets the string AND repositions

    //  5. Apply initial highlight
    updateColors();
}

// updateColors
// Called every time selectedIndex changes.
// Makes the selected item bright green, all others gray.
void Menu::updateColors() {
    for (int i = 0; i < MENU_COUNT; i++) {
        if (i == selectedIndex) {
            items[i].setFillColor(COLOR_SELECTED);
            items[i].setStyle(sf::Text::Bold);       // selected = bold
        } else {
            items[i].setFillColor(COLOR_NORMAL);
            items[i].setStyle(sf::Text::Regular);    // others = normal weight
        }
    }
}

// setHighScore
void Menu::setHighScore(int score) {
    highScoreText.setString("HIGH SCORE: " + std::to_string(score));
    // Re-center after string changes (width changes with new number)
    float textWidth = highScoreText.getGlobalBounds().width;
    float x = (windowWidth - textWidth) / 2.f;
    highScoreText.setPosition(x, windowHeight * 0.80f); // near bottom
}

// handleInput
// Call this once per event in your event loop.
// Returns -1 until the user presses ENTER, then returns 0, 1, or 2.
int Menu::handleInput(sf::Event& event) {
    // Only care about key-press events
    if (event.type != sf::Event::KeyPressed)
        return -1;

    if (event.key.code == sf::Keyboard::Up) {
        // Move selection up, wrap around from top to bottom
        selectedIndex = (selectedIndex - 1 + MENU_COUNT) % MENU_COUNT;
        updateColors();
    }
    else if (event.key.code == sf::Keyboard::Down) {
        // Move selection down, wrap around from bottom to top
        selectedIndex = (selectedIndex + 1) % MENU_COUNT;
        updateColors();
    }
    else if (event.key.code == sf::Keyboard::Return) {
        // ENTER confirms the current selection
        return selectedIndex;
    }

    return -1; // No selection confirmed yet
}

// draw
void Menu::draw(sf::RenderWindow& window) {
    window.draw(titleText);
    for (int i = 0; i < MENU_COUNT; i++) {
        window.draw(items[i]);
    }
    window.draw(highScoreText);
}
