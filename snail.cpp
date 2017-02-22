#include "snail.hpp"

unsigned int Snail::snailNumber = 1;

sf::Font Snail::font;
sf::Texture Snail::texture;
unsigned int Snail::windowWidth  = 0;
unsigned int Snail::windowHeight = 0;
float Snail::raceLen = 15000.f;


void Snail::loadFont(const std::string & fontName) {

    if (not Snail::font.loadFromFile(fontName)) {
        throw std::runtime_error("Font " + fontName + " could not be loaded. ");
    }

}

void Snail::initTexture(const std::string & textureName) {

    if (not Snail::texture.loadFromFile(textureName)) {
        throw std::runtime_error("Font " + textureName + " could not be loaded. ");
    }

}

void Snail::initDimensions(const unsigned int windowW, const unsigned int windowH) {

    Snail::windowWidth = windowW;
    Snail::windowHeight = windowH;

}

void Snail::setRaceLength(const float len) {

    Snail::raceLen = len;
    
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
        _text.setFillColor(sf::Color::Red);

        _number = Snail::snailNumber;

        Snail::snailNumber += 1;

}

void Snail::updateSprite() {

    const int x = (windowWidth / Snail::raceLen) * _currentPosition;
    const int y = (_number - 1) * (Snail::windowWidth / 20);

    setPosition(x, y);
    _text.setPosition(x + 20, y - 7);

}

void Snail::update() {

    _currentPosition += _mmPerSecond;
    updateSprite();

}

sf::Text & Snail::getText() {

    return _text;

}

unsigned int Snail::getPosition() {

    return _currentPosition;

}
