#include "window.hpp"

Window::Window(std::vector<Snail> & snails) : _snails(snails) {

    sf::VideoMode vm = sf::VideoMode::getFullscreenNodes()[3];
    create(vm, "Snail Race");
    setScale(vm.width / 800.f);

    for (auto & i : _snails) {
        i.setScale(getScale());
    }

}

void Window::render() {

    clear();

    for (const auto & i : _snails) {
        draw(i);
        draw(i.getText());
    }

    display();

}

bool Window::open() {

    return isOpened();

}
