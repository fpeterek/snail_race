#include "snail_race.hpp"


int main(int argc, const char * argv[]) {

    if (argc < 2) {
        std::cout << "Error: Not Enough Arguments" << std::endl;
        return -1;
    }

    float speedModifier = 1.f;
    if (argc >= 3) {
        try {

            const std::string modifier(argv[2]);
            speedModifier = std::stof(modifier);

        } catch (const std::exception & e) {
            /* Do nothing if an exception is thrown */
        }
    }

    const std::string filename(argv[1]);

    try {

        SnailRace race;
        race.readDataFromFile(filename);
        race.setSpeedModifier(speedModifier);
        race.startRace();

    } catch (const std::invalid_argument & e) {
        std::cout << e.what() << std::endl;
    } catch (const std::runtime_error & e) {
        std::cout << e.what() << std::endl;
    } catch (const std::exception & e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "An unexpected error has occured. " << std::endl;
    }

}
