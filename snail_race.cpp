#include "snail_race.hpp"

std::array<std::string, 2> splitStr(const std::string & str, const std::string & delimiter) {

    size_t delimiterPos = str.find(delimiter);
    if (delimiterPos == std::string::npos) {
        throw std::runtime_error("String \"" + str + "\" could not be parsed. ");
    }
    std::array<std::string, 2> substrings;
    substrings[0] = str.substr(0, delimiterPos);
    substrings[1] = str.substr(delimiterPos + delimiter.length());

    return substrings;

}

void SnailRace::initSnails() {

    Snail::loadFont(FONT);
    Snail::initTexture(TEXTURE);
    Snail::initDimensions(1200, 800);

}

void SnailRace::readDataFromFile(const std::string & filename) {

    std::ifstream input(filename);
    if (not input) {
        throw std::invalid_argument("File " + filename + " could not be opened. ");
    }

    {
        std::string raceLenStr;
        std::getline(input, raceLenStr);
        _raceLength = std::stoi(raceLenStr);
    }

    int lineCounter = 0;
    std::string line;

    /* Init fonts, textures... before constructing snails */
    SnailRace::initSnails();

    while (lineCounter < 20) {

        std::getline(input, line);

        if (line == "") {
            break;
        }

        std::array<std::string, 2> substrings = splitStr(line, " ");
        const unsigned int startingPosition = std::stoi(substrings[0]);
        const unsigned int mmPerSecond = std::stoi(substrings[1]);

        _snails.emplace_back( Snail(startingPosition, mmPerSecond) );

    }

}

void SnailRace::updateSnails() {

    for (auto & snail : _snails) {
        snail.update();
    }

}

std::vector<size_t> SnailRace::qsort(const std::vector<size_t> & snailIndexes) {

    const size_t size = snailIndexes.size();

    if (size <= 1) {
        return snailIndexes;
    }

    const size_t pivot = size / 2;
    const unsigned int pivotPosition = _snails[snailIndexes[pivot]].getPosition();
    std::vector<size_t> left;
    std::vector<size_t> right;

    for (size_t i = 0; i < size; ++i) {

        if (i == pivot) {
            continue;
        }
        if (_snails[snailIndexes[i]].getPosition() >= pivotPosition) {
            left.emplace_back(snailIndexes[i]);
        } else {
            right.emplace_back(snailIndexes[i]);
        }

    }

    left = qsort(left);
    right = qsort(right);
    left.emplace_back(snailIndexes[pivot]);
    for (auto & snail : right) {
        left.emplace_back(snail);
    }

    return left;

}

std::vector<size_t> SnailRace::sortSnails() {

    std::vector<size_t> snailIndexes;
    for (size_t i = 0; i < _snails.size(); ++i) {
        snailIndexes.emplace_back(i);
    }
    snailIndexes = qsort(snailIndexes);
    return snailIndexes;

}

void SnailRace::formatOutput(const std::vector<size_t> & snails, const int firstPos, const int lastPos) {

    const size_t vectorSize = snails.size();

    if (not vectorSize) {
        return;
    }

    if (vectorSize == 1) {

        std::cout << firstPos << ". position: Snail number " << (snails[0] + 1)
                  << " distance: " << _snails[snails[0]].getPosition() << std::endl;
        return;

    }

    std::cout << firstPos << " - " << lastPos << ". position: Snails number ";

    for (unsigned int i = 0; i < vectorSize - 2; ++i) {

        std::cout << (snails[i] + 1) << ", ";

    }
    std::cout << (snails[vectorSize - 2] + 1) << " and " << (snails[vectorSize - 1] + 1);
    std::cout << " distance: " << _snails[snails[0]].getPosition() << std::endl;


}

int SnailRace::getMaxDistance() {

    unsigned int time = 0;

    std::vector<Snail> snailsCopy(_snails);

    /* Get position after raceLength + 1 so the snail doesn't walk out of boundaries */
    while (++time <= _raceLength + 1) {

        for (auto & snail : snailsCopy) {
            snail.update();
        }

    }

    int maxDistance = 0;
    for (auto & snail : snailsCopy) {
        if (snail.getPosition() > maxDistance) {
            maxDistance = snail.getPosition();
        }
    }

    return maxDistance;

}

void SnailRace::outputInfo() {

    std::vector<size_t> snailsInWinningOrder = sortSnails();
    /* Just a placeholder, the last item in the vector is ignored */
    snailsInWinningOrder.emplace_back(-1);
    unsigned int firstPos = 1;
    unsigned int lastPos  = 1;

    std::vector<size_t> temp;

    for (size_t i = 0; i < snailsInWinningOrder.size() - 1; ++i) {

        temp.emplace_back(snailsInWinningOrder[i]);

        if (_snails[snailsInWinningOrder[i]].getPosition() != _snails[snailsInWinningOrder[i + 1]].getPosition()) {

            formatOutput(temp, firstPos, lastPos);
            temp = std::vector<size_t>();

            firstPos = lastPos + 1;

        }

        ++lastPos;

    }

    std::cout << "\n\n" << "---------- Actual output ----------" << "\n\n";

    for (size_t i = 0; i < snailsInWinningOrder.size(); ++i) {
        std::cout << i + 1 << ". position: Snail number " << (snailsInWinningOrder[i] + 1)
                  << " distance: " << _snails[snailsInWinningOrder[i]].getPosition() << std::endl;
    }

}

void SnailRace::setSpeedModifier(const float modifier) {

    _speedModifier = modifier;

}

void SnailRace::startRace() {

    unsigned int time = 0;

    Window window(_snails);

    sf::Event event;

    Snail::setRaceLength(getMaxDistance() + 30);

    while (++time <= _raceLength) {
        updateSnails();

        if (window.open()) {
            window.render();
        }

        while (window.getEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.closeWindow();
            } else if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::Down) {
                    _speedModifier /= 2;
                } else if (event.key.code == sf::Keyboard::Up) {
                    _speedModifier *= 2;
                }

            }
        }

        const int sleepFor = (1.f / _speedModifier) * 1000;
        std::this_thread::sleep_for(std::chrono::milliseconds( sleepFor ));

    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    window.closeWindow();
    outputInfo();

}
