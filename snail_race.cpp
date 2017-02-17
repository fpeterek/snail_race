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
    std::vector<size_t> snailPositions = qsort(snailIndexes);
    return snailPositions;

}

void SnailRace::outputInfo() {

    std::vector<size_t> snailsInWinningOrder = sortSnails();

    for (size_t i = 0; i < _snails.size(); ++i) {

        std::cout << "Snail number: " << (i + 1) << " Snail position: " << _snails[i].getPosition() << std::endl;

    }

    for (size_t i = 0; i < snailsInWinningOrder.size(); ++i) {
        std::cout << i + 1 << ". position: Snail number " << (snailsInWinningOrder[i] + 1) << " distance: " << _snails[snailsInWinningOrder[i]].getPosition() << std::endl;
    }

}

void SnailRace::startRace() {

    unsigned int time = 0;

    while (++time <= _raceLength) {
        updateSnails();
    }

    outputInfo();

}
