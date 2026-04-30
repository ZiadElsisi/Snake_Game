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