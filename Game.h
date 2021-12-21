#pragma once
#include "Life.h"
#include "vector"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>

class Game {
public:
    sf::RenderWindow window;

    Game(Life &life);

    Life * Life_ptr;

    const size_t cell_size = 10;

    sf::Vector2<size_t> window_size;

    std::vector<sf::RectangleShape> tilemap;

    bool is_stopped = false;

    bool focused;

    void RenderLoop();
    void DispatchEvent(sf::Event &event);
};
