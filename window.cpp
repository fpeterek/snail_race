#include "window.hpp"

Window::Window(std::vector<Snail> & snails) : _snails(snails) {

    const unsigned int width = 1200;
    const unsigned int height = 800;

    sf::VideoMode vm = sf::VideoMode(width, height);
    create(vm, "Snail Race");

    _background = sf::RectangleShape(sf::Vector2f(width, height));
    _background.setFillColor(sf::Color::White);

}

void Window::render() {

    clear();

    draw(_background);
    for (auto & i : _snails) {
        draw(i);
        draw(i.getText());
    }

    display();

}

bool Window::open() {

    return isOpen();

}

bool Window::getEvent(sf::Event & event) {
    return pollEvent(event);
}

void Window::closeWindow() {

    close();

}
