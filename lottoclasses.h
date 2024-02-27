#ifndef LOTTO_PROGRAM_LOTTOCLASSES_H
#define LOTTO_PROGRAM_LOTTOCLASSES_H

#include <vector>
#include <set>
#include <iostream>
#include <ctime>

class PowerballNumberGenerator {            // Generates random numbers within a specified range
public:
    PowerballNumberGenerator() {
        srand(time(nullptr)); // Initialize random seed
    }

    int generateNumber(int min, int max) {
        return rand() % (max - min + 1) + min;
    }
};

// Simulates Powerball game logic
class Powerball {
private:
    std::set<int> jackpot;
    int jackpotMega;
    std::set<int> userTicket = {};
    int userMega = 0;
    int plays = 0;
    int maxPlays = -1;
    PowerballNumberGenerator numberGenerator;

public:
    Powerball() : numberGenerator(PowerballNumberGenerator()) {

    }

    void setUserTicket(std::set<int> &nums) {
        userTicket = nums;
    }

    void setUserMega(int mega) {
        userMega = mega;
    }

    std::set<int> getUserTicket() {
        return userTicket;
    }

    int getUserMega() {
        return userMega;
    }

    void setMaxPlays(int max) {
        if (max > 0) {
            maxPlays = max;
        } else {
            maxPlays = -1;
        }
    }

    void getMaxPlays() {
        if (maxPlays > 0) {
            std::cout << "\nYou are limited to " << maxPlays << " plays.\n" << std::endl;
        } else {
            std::cout << "\nYou have infinite plays.\n" << std::endl;
        }
    }

    void clearJackpot() {
        jackpot.clear();
        jackpotMega = 0;
        plays = 0;
    }

    void startGame();
};

#endif //LOTTO_PROGRAM_LOTTOCLASSES_H
