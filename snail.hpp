#ifndef SNAIL
#define SNAIL

#include <stdexcept>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define SNAIL_SPEED_LIMIT 10000
#define SNAIL_POSITION_LIMIT 10000

class Snail : public sf::Sprite {

    static unsigned int snailNumber;
    static sf::Font font;
    static sf::Texture texture;
    static unsigned int windowWidth;
    static unsigned int windowHeight;
    static float raceLen;

    const unsigned int _mmPerSecond;
    const unsigned int _startingPosition;
    unsigned int _currentPosition;

    unsigned int _number;
    sf::Text _text;

    void updateSprite();

public:

    static void loadFont(const std::string & fontName);
    static void initTexture(const std::string & textureName);
    static void initDimensions(const unsigned int windowWidth, const unsigned int windowHeight);
    static void setRaceLength(const float len);

    Snail(const unsigned int startingPosition, const unsigned int mmPerSecond);
    void update();

    unsigned int getPosition();

    sf::Text & getText();


};

#endif
