#include "snail.hpp"

void Snail::initFont(const std::string & fontName) {

    if (not Snail::font.loadFromFile(fontName)) {
        throw std::runtime_error("Font " + fontName + " could not be loaded. ");
    }

}

void Snail::initTexture(const std::string & textureName) {

    if (not Snail::texture.loadFromFile(textureName)) {
        throw std::runtime_error("Font " + textureName + " could not be loaded. ");
    }

}

Snail::Snail(const unsigned int startingPosition, const unsigned int mmPerSecond) :
    _startingPosition(startingPosition),
    _mmPerSecond(mmPerSecond) {

        if (_startingPosition > SNAIL_POSITION_LIMIT) {
            throw std::invalid_argument("Invalid snail position. ");
        }
        if (_mmPerSecond > SNAIL_SPEED_LIMIT) {
            throw std::invalid_argument("Invalid snail speed. ");
        }

        _currentPosition = _startingPosition;

        setTexture(Snail::texture);

        _text.setFont(Snail::font);
        _text.setCharacterSize(32);
        _text.setString(std::to_string(Snail::snailNumber));

        Snail::snailNumber += 1;

}

void Snail::update() {

    _currentPosition += _mmPerSecond;

}

sf::Text Snail::getText() {

    return _text;

}

unsigned int Snail::getPosition() {

    return _currentPosition;

}
