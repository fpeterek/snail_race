#include "snail.hpp"

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

}

void Snail::update() {

    _currentPosition += _mmPerSecond;

}

unsigned int Snail::getPosition() {

    return _currentPosition;

}
