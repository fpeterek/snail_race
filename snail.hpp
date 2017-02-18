#ifndef SNAIL
#define SNAIL

#include <stdexcept>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define SNAIL_SPEED_LIMIT 10000
#define SNAIL_POSITION_LIMIT 10000

class Snail : public sf::Sprite {

    static unsigned int snailNumber = 1;
    static sf::Font font;
    static sf::Texture texture;

    const unsigned int _mmPerSecond;
    const unsigned int _startingPosition;
    unsigned int _currentPosition;

    sf::Text _text;

public:

    static void loadFont(const std::string & fontName);
    static void initTexture(const std::string & textureName);

    Snail(const unsigned int startingPosition, const unsigned int mmPerSecond);
    void update();

    unsigned int getPosition();

    sf::Text & getText();


};

#endif
