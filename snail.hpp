#ifndef SNAIL
#define SNAIL

#include <stdexcept>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define SNAIL_SPEED_LIMIT 10000
#define SNAIL_POSITION_LIMIT 10000

class Snail {

    const unsigned int _mmPerSecond;
    const unsigned int _startingPosition;
    unsigned int _currentPosition;

public:

    Snail(const unsigned int startingPosition, const unsigned int mmPerSecond);
    void update();

    unsigned int getPosition();


};

#endif
