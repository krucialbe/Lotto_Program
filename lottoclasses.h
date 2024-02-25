#ifndef LOTTO_PROGRAM_LOTTOCLASSES_H
#define LOTTO_PROGRAM_LOTTOCLASSES_H

//this shouldn't be the main branch

#include <vector>

class PowerballNumberGenerator {
public:
    PowerballNumberGenerator();
    int generateNumber(int min, int max);
};


class LottoGame {
private:
    std::vector<int> nums;
    std::vector<int> ticket;
    int plays;
    int max_plays;
    PowerballNumberGenerator numberGenerator;

public:
    LottoGame();
    void startGame();
};

#endif //LOTTO_PROGRAM_LOTTOCLASSES_H
