#include <iostream>
#include "Shared.h"
#include <SFML/Graphics.hpp>
using namespace std;


int main() {
    sf::RenderWindow window(
      sf::VideoMode(
          Constants::GRID_WIDTH * Constants::CELL_SIZE + Constants::PANEL_WIDTH,
          Constants::GRID_HEIGHT * Constants::CELL_SIZE
      ),
      "Snake Game"
  );
}