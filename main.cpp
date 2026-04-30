#include <iostream>
#include <SFML/Graphics.hpp>
#include <Shared.h>
using namespace std;
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    sf::RenderWindow window(
        sf::VideoMode(
            GRID_WIDTH * CELL_SIZE + PANEL_WIDTH,
            GRID_HEIGHT * CELL_SIZE
        ),
        "Snake Game"
    );
}