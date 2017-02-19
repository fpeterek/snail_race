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

#define FONT "Inconsolata.ttf"
#define TEXTURE "snail.png"


class SnailRace {

    std::vector<Snail> _snails;

    static void initSnails();

    int _raceLength;
    float _speedModifier = 1.f;

    std::vector<size_t> qsort(const std::vector<size_t> & snailIndexes);
    std::vector<size_t> sortSnails();
    void updateSnails();
    void formatOutput(const std::vector<size_t> & snails);
    void outputInfo();

public:

    void readDataFromFile(const std::string & filename);
    void setSpeedModifier(const float modifier);

    void startRace();

};

#endif
