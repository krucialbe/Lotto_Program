#include "lottoclasses.h"
#include <iostream>
#include <cstdlib>
#include <limits>


void Powerball::startGame() {
    std::set<int> nums = {};
    int num = 0;
    int randomNum = 0;
    char choice;
    int numChoice;
    std::cout << "Thank you for choosing to play Powerball!\n" << std::endl;
    while (true) {
        bool keepPlaying = true;
        std::cout
                << "Select an option: \n1. Play draw\n2. Quick play\n3. Pick numbers\n4. Check ticket\n5. Set play limit\n6. Check play limit\n-1. Exit"
                << std::endl;
        std::cout << "=> ";
        std::cin >> numChoice;
        switch (numChoice) {
            case 1:
                if (!nums.empty() && num > 0) {
                    clearJackpot();
                    std::cout << "Processing ticket...\n" << std::endl;
                    while (keepPlaying && plays != maxPlays) {
                        int jackpotNumbers = numberGenerator.generateNumber(1, 69);
                        int jackpotMega = numberGenerator.generateNumber(1, 26);
                        for (int n = 0; n < 5; ++n) {
                            if (std::find(jackpot.begin(), jackpot.end(), jackpotNumbers) == jackpot.end() &&
                                jackpot.size() != 5)
                                jackpot.insert(jackpotNumbers);
                        }
                        if (jackpot.size() == 5) {
                            if (jackpot != userTicket) {
                                ++plays;
                                jackpot.clear();
                            } else if (jackpot == userTicket) {
                                if (jackpotMega == userMega) {
                                    ++plays;
                                    std::cout << "You won in " << plays << " tries!\n" << std::endl;
                                    keepPlaying = false;
                                }
                            }
                        }
                        if (plays == maxPlays) {
                            std::cout << "Sorry! You did not win in " << plays << " plays.\n" << std::endl;
                            keepPlaying = false;
                        }
                    }
                } else {
                    std::cout << "No numbers selected. Please select your numbers.\n" << std::endl;
                }
                break;
            case 2:
                nums.clear(); // Clear the set before generating new numbers
                num = numberGenerator.generateNumber(1, 26);
                do {
                    randomNum = numberGenerator.generateNumber(1, 69);
                    nums.insert(randomNum);
                } while (nums.find(randomNum) != nums.end() && nums.size() != 5);
                setUserTicket(nums);
                setUserMega(num); // Set Mega Ball number
                std::cout << "Processing ticket...\n" << std::endl;
                while (keepPlaying && plays != maxPlays) {
                    int jackpotNumbers = numberGenerator.generateNumber(1, 69);
                    int jackpotMega = numberGenerator.generateNumber(1, 26);
                    for (int n = 0; n < 5; ++n) {
                        if (std::find(jackpot.begin(), jackpot.end(), jackpotNumbers) == jackpot.end() &&
                            jackpot.size() != 5)
                            jackpot.insert(jackpotNumbers);
                    }
                    if (jackpot.size() == 5) {
                        if (jackpot != userTicket) {
                            ++plays;
                            jackpot.clear();
                        } else if (jackpot == userTicket) {
                            if (jackpotMega == userMega) {
                                ++plays;
                                std::cout << "You won in " << plays << " tries!\n" << std::endl;
                                keepPlaying = false;
                            }
                        }
                    }
                    if (plays == maxPlays) {
                        std::cout << "Sorry! You did not win in " << plays << " plays.\n" << std::endl;
                        keepPlaying = false;
                    }
                }
                break;
            case 3:
                std::cout << "\nWould you like to use a random set of numbers? (Y/N)" << std::endl;
                std::cout << "=> ";
                std::cin >> choice;
                if (tolower(choice) == 'y') {
                    nums.clear();
                    num = numberGenerator.generateNumber(1, 26);
                    do {
                        randomNum = numberGenerator.generateNumber(1, 69);
                        nums.insert(randomNum);
                    } while (nums.find(randomNum) != nums.end() && nums.size() != 5);
                } else if (tolower(choice) == 'n') {
                    while (num == 0) {
                        std::cout << "Enter 5 numbers between 1 and 69 (or -1 to stop): ";

                        // Loop for each of the 5 user numbers
                        for (int i = 0; i < 5; ++i) {
                            std::cin >> numChoice;

                            // Check for invalid input and end of input indicator
                            if (std::cin.fail() || numChoice < -1 || numChoice > 69) {
                                std::cin.clear(); // Clear error flags
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                                '\n'); // Discard invalid input
                                std::cout << "Invalid input. Please enter a number between 1 and 69, or -1 to stop."
                                          << std::endl;
                                continue; // Skip to the next iteration of the loop for the next number
                            }

                            // Stop input if -1 is entered
                            if (numChoice == -1) {
                                break; // Exit the loop for entering the 5 numbers
                            }

                            // Add unique number to the set
                            if (nums.insert(numChoice).second) {
                                std::cout << numChoice << " added successfully." << std::endl;
                            } else {
                                std::cout << numChoice << " is already in the set. Please enter a unique number."
                                          << std::endl;
                            }
                        }

                        // Check if user entered enough numbers or stopped input
                        if (nums.size() < 5 && numChoice != -1) {
                            std::cout << "You entered less than 5 unique numbers. Please enter all 5." << std::endl;
                        }

                        // Prompt for the Mega Ball number
                        std::cout << "Please choose your mega number, between 1 and 26: ";
                        std::cin >> numChoice;

                        // Check and handle invalid Mega Ball input
                        if (std::cin.fail() || numChoice < 1 || numChoice > 26) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Invalid input. Please enter a number between 1 and 26." << std::endl;
                            continue; // Skip to the next iteration of the overall loop
                        } else {
                            num = numChoice; // Valid Mega Ball number, update variable and exit the loop
                        }
                    }

                }
                setUserTicket(nums);
                setUserMega(num);
                std::cout << "\nYour numbers are: ";
                for (auto &number: getUserTicket()) {
                    std::cout << number << ", ";
                }
                std::cout << getUserMega() << "\n" << std::endl;
                break;
            case 4:
                if (nums.empty()) {
                    std::cout << "No numbers selected. Please select your numbers.\n" << std::endl;
                } else {
                    std::cout << "\nYour numbers are: ";
                    for (auto &number: getUserTicket()) {
                        std::cout << number << ", ";
                    }
                    std::cout << getUserMega() << "\n" << std::endl;
                }
                break;
            case 5:
                std::cout << "\nSet the limit of draws. Set -1 for infinite plays.\n" << std::endl;
                std::cout << "=> ";
                std::cin >> numChoice;
                if (std::cin.fail()) {
                    std::cout << "Invalid input. Please enter a number.\n" << std::endl;
                    std::cin.clear(); // Clear error flags
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                } else {
                    setMaxPlays(numChoice); // Valid integer, call the function
                }
                break;
            case 6:
                getMaxPlays();
                break;
            case -1:
                exit(0);  // Exit the loop when user enters -1
            default:
                std::cout << "Please enter a valid option.\n" << std::endl;
        }
    }
}
