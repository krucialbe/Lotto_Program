#include "lottoclasses.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

PowerballNumberGenerator::PowerballNumberGenerator() {
    srand(time(nullptr)); // Initialize random seed
}

int PowerballNumberGenerator::generateNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

Powerball::Powerball() : numberGenerator(PowerballNumberGenerator()) {
    plays = 0;
    // Use -1 for max_plays if no limit
    max_plays = -1;
}

void Powerball::startGame() {
    while (userTicket.empty()) {
        std::cout << "Processing ticket..." << std::endl;
        while (true) {
            if (plays == max_plays)
                exit(0);
            int jackpotNumbers = numberGenerator.generateNumber(1, 69);
            int userNumbers = numberGenerator.generateNumber(1, 69);
            int jackpotMega = numberGenerator.generateNumber(1, 26);
            int userMega = numberGenerator.generateNumber(1, 26);
            for (int n = 0; n < 5; ++n) {
                if (std::find(jackpot.begin(), jackpot.end(), jackpotNumbers) == jackpot.end() && jackpot.size() != 5)
                    jackpot.push_back(jackpotNumbers);
                if (std::find(userTicket.begin(), userTicket.end(), userNumbers) == userTicket.end() && userTicket.size() != 5)
                    userTicket.push_back(userNumbers);
                std::sort(jackpot.begin(), jackpot.end());
                std::sort(userTicket.begin(), userTicket.end());
                if (jackpot.size() == 5) {
                    if (userTicket.size() == 5) {
                        if (jackpot != userTicket) {
                            if (jackpotMega != userMega) {
                                ++plays;
                                jackpot.clear();
                                userTicket.clear();
                                int jackpotMega = 0;
                                int userMega = 0;
                            }
                        } else if (jackpot == userTicket) {
                            if (jackpotMega == userMega) {
                                ++plays;
                                std::cout << "You won in " << plays << " tries!" << std::endl;
                                std::cout << "The winning numbers were: ";
                                for (int i = 0; i < userTicket.size(); ++i) {
                                    std::cout << userTicket[i];
                                    if (i != userTicket.size() - 1)
                                        std::cout << ", ";
                                }
                                std::cout << std::endl;
                                exit(0);
                            }
                        }
                    }
                }
            }
        }
    }
}
