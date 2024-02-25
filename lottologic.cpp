#include "lottoclasses.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

//this shouldn't be the main branch

PowerballNumberGenerator::PowerballNumberGenerator() {
    srand(time(nullptr)); // Initialize random seed
}

int PowerballNumberGenerator::generateNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

LottoGame::LottoGame() : numberGenerator(PowerballNumberGenerator()) {
    plays = 0;
    // Use -1 for max_plays if no limit
    max_plays = -1;
}

void LottoGame::startGame() {
    while (ticket.empty()) {
        std::cout << "Processing ticket...\n\n";
        while (true) {
            if (plays == max_plays)
                exit(0);
            int x = numberGenerator.generateNumber(1, 69);
            int y = numberGenerator.generateNumber(1, 69);
            int mega = numberGenerator.generateNumber(1, 26);
            int mega_ticket = numberGenerator.generateNumber(1, 26);
            for (int n = 0; n < 5; ++n) {
                if (std::find(nums.begin(), nums.end(), x) == nums.end() && nums.size() != 5)
                    nums.push_back(x);
                if (std::find(ticket.begin(), ticket.end(), y) == ticket.end() && ticket.size() != 5)
                    ticket.push_back(y);
                std::sort(nums.begin(), nums.end());
                std::sort(ticket.begin(), ticket.end());
                if (nums.size() == 5) {
                    if (ticket.size() == 5) {
                        if (nums != ticket) {
                            if (mega != mega_ticket) {
                                ++plays;
                                nums.clear();
                                ticket.clear();
                                int mega_num = 0;
                                int mega_ticket = 0;
                            }
                        } else if (nums == ticket) {
                            if (mega == mega_ticket) {
                                ++plays;
                                std::cout << "You won in " << plays << " tries!\n\n";
                                std::cout << "The winning numbers were: ";
                                for (int i = 0; i < ticket.size(); ++i) {
                                    std::cout << ticket[i];
                                    if (i != ticket.size() - 1)
                                        std::cout << ", ";
                                }
                                std::cout << "\n";
                                exit(0);
                            }
                        }
                    }
                }
            }
        }
    }
}
