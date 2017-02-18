#ifndef SNAIL_RACE
#define SNAIL_RACE

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <array>
#include <chrono>
#include <thread>
#include <list>
#include <map>

#include "snail.hpp"
#include "window.hpp"


class SnailRace {

    std::vector<Snail> _snails;

    int _raceLength;

    std::vector<size_t> qsort(const std::vector<size_t> & snailIndexes);
    std::vector<size_t> sortSnails();
    void updateSnails();
    void outputInfo();

public:

    void readDataFromFile(const std::string & filename);

    void startRace();

};

#endif
