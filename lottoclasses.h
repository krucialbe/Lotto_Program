#ifndef LOTTO_PROGRAM_LOTTOCLASSES_H
#define LOTTO_PROGRAM_LOTTOCLASSES_H

#include <vector>

class PowerballNumberGenerator {
public:
    PowerballNumberGenerator();
    int generateNumber(int min, int max);
};


class Powerball {
private:
    std::vector<int> jackpot;
    std::vector<int> userTicket;
    int plays;
    int max_plays;
    PowerballNumberGenerator numberGenerator;

public:
    Powerball();
    void startGame();
};

#endif //LOTTO_PROGRAM_LOTTOCLASSES_H
