#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <stdexcept>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "snail.hpp"

class Window : sf::RenderWindow {

    std::vector<Snail> & _snails;

public:

    Window();

    void render();
    bool open();

};

#endif
