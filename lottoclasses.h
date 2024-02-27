#ifndef LOTTO_PROGRAM_LOTTOCLASSES_H
#define LOTTO_PROGRAM_LOTTOCLASSES_H

#include <vector>
#include <set>
#include <iostream>
#include <ctime>
#include <unordered_map>
#include <queue>

// Generates random numbers within a specified range
class PowerballNumberGenerator {
public:
    // Initializes random seed (sets the seed for the random number generator based on the current time.)
    PowerballNumberGenerator() {
        srand(time(nullptr));
    }

    // Generates a random number between min and max (inclusive)
    int generateNumber(int min, int max) {
        return rand() % (max - min + 1) + min;
    }
};

// Compares a pair of objects based on their second element. Used for the priority queue
struct Compare {
    bool operator()(const std::pair<int, int> &a, const std::pair<int, int> &b) {
        return a.second < b.second;
    }
};


// Simulates Powerball game logic
class Powerball {
private:
    std::set<int> jackpot;                      // A set to store the winning numbers of the jackpot
    int jackpotMega;                            // An integer to store the winning mega number of the jackpot
    std::set<int> userTicket = {};              // A set to store the user's selected numbers for the ticket
    int userMega = 0;                           // An integer to store the user's selected mega number
    int plays = 0;                              // An integer to keep track of the number of plays or attempts
    int maxPlays = -1;                          // An integer to set the maximum number of plays allowed (-1 indicates unlimited plays)
    PowerballNumberGenerator numberGenerator;   // An instance of PowerballNumberGenerator used to generate random numbers
    std::unordered_map<int, int> numMap;         // A map used to store the frequency of each number in the lottery
    std::unordered_map<int, int> megaMap;        // A map used to store the frequency of each mega number in the lottery

public:
    // Initializes the numberGenerator member using the PowerballNumberGenerator constructor
    Powerball() : numberGenerator(PowerballNumberGenerator()) {

    }

    void setUserTicket(std::set<int> &nums) {
        userTicket = nums;
    }

    void setUserMega(int mega) {
        userMega = mega;
    }

    // Returns set of numbers equating to the user's ticket, minus the mega number
    std::set<int> getUserTicket() {
        return userTicket;
    }

    // Returns single integer mega number
    int getUserMega() {
        return userMega;
    }

    // Allows the user to limit the amount of loops before exiting
    void setMaxPlays(int max) {
        if (max > 0) {
            maxPlays = max;
        } else {
            maxPlays = -1;
        }
    }

    // Shows what the current play limit is
    void getMaxPlays() {
        if (maxPlays > 0) {
            std::cout << "\nYou are limited to " << maxPlays << " plays.\n" << std::endl;
        } else {
            std::cout << "\nYou have infinite plays.\n" << std::endl;
        }
    }

    // Prints the numbers used most in winning sets, 5 regular numbers and 5 mega numbers
    void printTop5() {
        // Makes sure game has been played at least once to store values
        if (numMap.empty() || megaMap.empty()) {
            std::cout << "\nThere have been no plays.\n" << std::endl;
        }
            // Iterates through maps and places values into priority queues. Prints numbers from queues.
        else {
            std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, Compare> pq;

            for (const auto &entry: numMap) {
                pq.push(entry);
                if (pq.size() > 5) {
                    pq.pop();
                }
            }

            std::cout << "\nTop 5 most used numbers: ";
            int count = 1;
            while (!pq.empty()) {
                if (count == 1) { std::cout << "["; }
                std::cout << pq.top().first;
                if (count < 5) { std::cout << ", "; }
                if (count == 5) { std::cout << "]\n" << std::endl; }
                pq.pop();
                count++;
            }

            for (const auto &entry: megaMap) {
                pq.push(entry);
                if (pq.size() > 5) {
                    pq.pop();
                }
            }

            std::cout << "Top 5 most used mega numbers:";
            count = 1;
            while (!pq.empty()) {
                if (count == 1) { std::cout << "["; }
                std::cout << pq.top().first;
                if (count < 5) { std::cout << ", "; }
                if (count == 5) { std::cout << "]\n" << std::endl; }
                pq.pop();
                count++;
            }
        }
    }

    // Deletes the set of jackpot numbers as well as it's mega. Used at the beginning of a play
    void clearJackpot() {
        jackpot.clear();
        jackpotMega = 0;
        plays = 0;
    }

    // Clears map to release storage for new numbers to be added to the maps
    void clearMaps() {
        numMap.clear();
        megaMap.clear();
    }

    // Function to enter game loop
    void startGame();
};

#endif //LOTTO_PROGRAM_LOTTOCLASSES_H
