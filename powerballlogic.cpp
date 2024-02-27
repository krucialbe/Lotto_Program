#include "lottoclasses.h"
#include <iostream>
#include <cstdlib>
#include <limits>


void Powerball::startGame() {
    std::set<int> nums = {};            // Set of numbers to be placed into User ticket
    int num = 0;                        // Number to be used as Mega ball
    int randomNum;                      // Temp variable to store numbers while randomly generating
    char choice;                        // Temp variable to store user choice when expecting a letter
    int numChoice;                      // Temp variable to store user choice when expecting a number
    std::cout << "Thank you for choosing to play Powerball!\n" << std::endl;
    // Loop that keeps user in main menu until they exit
    while (true) {
        bool keepPlaying = true;        // Variables used for staying in
        bool validChoice = false;       // and exiting loop validation
        std::cout
                << "Select an option: \n1. Play\n2. Quick play\n3. Pick numbers\n"
                   "4. Check ticket\n5. Set play limit\n6. Check play limit\n7. Top Numbers\n0. Exit"
                << std::endl;
        std::cout << "=> ";
        std::cin >> numChoice;
        // Input validation
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid option.\n" << std::endl;
        } else
            // Main menu
            switch (numChoice) {
                case 1:         // Play draw (takes current user ticket and plays until match or limit reached)
                    // Game only starts if user has selected a ticket
                    if (!userTicket.empty() && num > 0) {
                        clearJackpot();         // Clears jackpot member variable so new jackpot can be created
                        clearMaps();
                        std::cout << "Processing ticket...\n" << std::endl;
                        // Loop to keep generating new draws until a match is found
                        while (keepPlaying && plays != maxPlays) {
                            int jackpotNumbers = numberGenerator.generateNumber(1, 69);
                            int jackpotMega = numberGenerator.generateNumber(1, 26);
                            megaMap[jackpotMega]++;         // Tallies the amount of times a number is used for the mega number
                            // Adds numbers to jackpot until 5 are selected
                            for (int n = 0; n < 5; ++n) {
                                if (std::find(jackpot.begin(), jackpot.end(), jackpotNumbers)
                                    == jackpot.end() && jackpot.size() != 5) {
                                    jackpot.insert(jackpotNumbers);
                                    numMap[jackpotNumbers]++;           // Tallies the amount of times a number is used for the jackpot
                                }
                            }
                            // When jackpot has enough numbers
                            if (jackpot.size() == 5) {
                                // Start over if no match
                                if (jackpot != userTicket) {
                                    ++plays;
                                    jackpot.clear();
                                }
                                    // Win logic, exit loop, return to main menu
                                else if (jackpot == userTicket) {
                                    if (jackpotMega == userMega) {
                                        ++plays;
                                        std::cout << "You won in " << plays << " tries!\n" << std::endl;
                                        keepPlaying = false;
                                    }
                                }
                            }
                            // If max plays set and no win is found when reached, exit loop, return to main menu
                            if (plays == maxPlays) {
                                std::cout << "Sorry! You did not win in " << plays << " plays.\n" << std::endl;
                                keepPlaying = false;
                            }
                        }
                    }
                        // Message displayed if there is not a ticket
                    else {
                        std::cout << "No numbers selected. Please select your numbers.\n" << std::endl;
                    }
                    break;
                case 2:         // Quick play (generates random numbers for user and plays until match or limit reached)
                    nums.clear(); // Clear the set before generating new numbers
                    num = numberGenerator.generateNumber(1, 26);    // Generates random number for User mega
                    // Generates random numbers for User ticket while there are not 5 numbers
                    do {
                        randomNum = numberGenerator.generateNumber(1, 69);
                        nums.insert(randomNum);
                    } while (nums.find(randomNum) != nums.end() && nums.size() != 5);
                    setUserTicket(nums);            // Set User ticker
                    setUserMega(num);           // Set Mega Ball number
                    clearJackpot();         // Clears jackpot member variable so new jackpot can be created
                    clearMaps();
                    std::cout << "Processing ticket...\n" << std::endl;
                    // Loop to keep generating new draws until a match is found
                    while (keepPlaying && plays != maxPlays) {
                        int jackpotNumbers = numberGenerator.generateNumber(1, 69);
                        int jackpotMega = numberGenerator.generateNumber(1, 26);
                        megaMap[jackpotMega]++;         // Tallies the amount of times a number is used for the mega number
                        // Adds numbers to jackpot until 5 are selected
                        for (int n = 0; n < 5; ++n) {
                            if (std::find(jackpot.begin(), jackpot.end(), jackpotNumbers)
                                == jackpot.end() && jackpot.size() != 5) {
                                jackpot.insert(jackpotNumbers);
                                numMap[jackpotNumbers]++;           // Tallies the amount of times a number is used for the jackpot
                            }
                        }
                        // When jackpot has enough numbers
                        if (jackpot.size() == 5) {
                            // Start over if no match
                            if (jackpot != userTicket) {
                                ++plays;
                                jackpot.clear();
                            }
                                // Win logic, print numbers, exit loop, return to main menu
                            else if (jackpot == userTicket) {
                                if (jackpotMega == userMega) {
                                    ++plays;
                                    std::cout << "You won in " << plays << " tries!\n" << std::endl;
                                    std::cout << "The winning numbers were: ";
                                    for (auto &number: getUserTicket()) {
                                        std::cout << number << ", ";
                                    }
                                    std::cout << getUserMega() << "\n" << std::endl;
                                    keepPlaying = false;
                                }
                            }
                        }
                        // If max plays set and no win is found when reached, exit loop, return to main menu
                        if (plays == maxPlays) {
                            std::cout << "Sorry! You did not win in " << plays << " plays.\n" << std::endl;
                            keepPlaying = false;
                        }
                    }
                    break;
                case 3:         // Pick numbers (creates ticket for user randomly or manually)
                    std::cout << "\nWould you like to use random numbers, pick your numbers, or cancel? (r/p/c)"
                              << std::endl;
                    std::cout << "=> ";
                    // Input validation & keeps user in number selection menu until they exit or enter valid input
                    while (true) {
                        std::cin >> choice;
                        if (std::cin.fail() || (tolower(choice) != 'r' && tolower(choice) != 'p'
                                                && tolower(choice) != 'c')) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Please enter a valid option (r, p, or c).\n";
                        } else {
                            // Clear the input buffer
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            break;
                        }
                    }
                    // Logic for random number selection
                    if (tolower(choice) == 'r') {
                        nums.clear();
                        num = numberGenerator.generateNumber(1, 26);
                        do {
                            randomNum = numberGenerator.generateNumber(1, 69);
                            nums.insert(randomNum);
                        } while (nums.find(randomNum) != nums.end() && nums.size() != 5);
                    }
                        // Logic for manual number selection
                    else if (tolower(choice) == 'p') {
                        std::set<int> tempNums = nums;      // Temp variable stores previous set in case of cancel
                        int tempNum = num;              // Saves Mega Ball number in case of cancel
                        nums.clear();           // clears last user ticket numbers
                        num = 0;                // clears last user Mega Ball number
                        while (num == 0) {
                            std::cout << "Enter 5 numbers between 1 and 69 (or -1 to stop): ";

                            while (nums.size() < 5) {
                                // Loop for each of the 5 user numbers
                                for (int i = 0; i < 5; ++i) {
                                    std::cin >> numChoice;

                                    // Stop input if -1 is entered
                                    if (numChoice == -1) {
                                        nums = tempNums;
                                        num = tempNum;
                                        tempNums.clear();
                                        tempNum = 0;
                                        break;
                                    }

                                    // Check for invalid input and indicate end of input
                                    if (std::cin.fail() || numChoice < -1 || numChoice > 69) {
                                        std::cin.clear(); // Clear error flags
                                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                                                        '\n'); // Discard invalid input
                                        std::cout
                                                << "Invalid input. Please enter a number between 1 and 69, or -1 to stop."
                                                << std::endl;
                                        --i;
                                        continue; // Skip to the next iteration of the loop for the next number
                                    }

                                    // Add unique number to the set
                                    if (nums.insert(numChoice).second) {
                                        std::cout << "Number " << i + 1 << ": " << numChoice << " added successfully."
                                                  << std::endl;
                                    } else {
                                        std::cout << numChoice
                                                  << " is already in the set. Please enter a unique number."
                                                  << std::endl;
                                        --i;
                                        continue; // Skip to the next iteration of the loop for the next number
                                    }
                                }

                            }


                            // Prompt for the Mega Ball number
                            while (!num) {
                                if (numChoice != -1) {
                                    std::cout << "\nPlease choose your mega number, between 1 and 26: ";
                                    std::cin >> numChoice;

                                    // Check and handle invalid Mega Ball input
                                    if ((std::cin.fail() || numChoice < 1 || numChoice > 26) && numChoice != -1) {
                                        std::cin.clear();
                                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                        std::cout << "\nInvalid input. Please enter a number between 1 and 26."
                                                  << std::endl;
                                        continue; // Skip to the next iteration of the overall loop
                                    }
                                        // Exits if -1 entered
                                    else if (numChoice == -1) {
                                        nums = tempNums;
                                        num = tempNum;
                                        tempNums.clear();
                                        tempNum = 0;
                                        break;
                                    }
                                        // Valid Mega Ball number, update variable and exit the loop
                                    else {
                                        num = numChoice;
                                        std::cin.clear();
                                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    }
                                } else {
                                    break;
                                }
                            }
                        }

                    }
                        // Exits back to main menu
                    else if ('c') {
                        std::cout << "\n";
                        break;
                    }
                    // Set User Ticket and User Mega member values
                    setUserTicket(nums);
                    setUserMega(num);
                    // Prints out ticket before exiting back to main menu
                    std::cout << "\nYour numbers are: ";
                    for (auto &number: getUserTicket()) {
                        std::cout << number << ", ";
                    }
                    std::cout << getUserMega() << "\n" << std::endl;
                    break;
                case 4:         // Check ticket (displays the current User ticket, if there is one)
                    // Exits to main menu if not ticket has been selected
                    if (userTicket.empty()) {
                        std::cout << "No numbers selected. Please select your numbers.\n" << std::endl;
                    }
                        // Prints ticket
                    else {
                        std::cout << "\nYour numbers are: ";
                        for (auto &number: getUserTicket()) {
                            std::cout << number << ", ";
                        }
                        std::cout << getUserMega() << "\n" << std::endl;
                    }
                    break;
                case 5:         // Set play limit (sets a limit to how many draws will happen until checking stops)
                    std::cout << "\nSet the limit of plays. Set -1 for infinite plays.\n" << std::endl;
                    std::cout << "=> ";
                    // Loop to keep player in set play limit menu if their input is invalid
                    do {
                        std::cin >> numChoice;
                        // Input validation.
                        if (std::cin.fail()) {
                            std::cout << "Invalid input. Please enter a number.\n" << std::endl;
                            std::cin.clear(); // Clear error flags
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                            validChoice = false;
                        }
                            // If an integer is used, limits number of plays to user input
                        else {
                            setMaxPlays(numChoice); // Valid integer, call the function
                            std::cout << "Limit of plays set to: " << numChoice << "\n" << std::endl;
                            validChoice = true;
                        }
                    } while (!validChoice);
                    break;
                case 6:         // Check play limit (displays current limit, default is infinite)
                    getMaxPlays();          // Prints out the number of plays the program will check before a win
                    break;
                case 7:         // Top Numbers (Displays the top 5 most used numbers and mega numbers in the last play)
                    printTop5();
                    break;
                case 0:        // Exit
                    exit(0);
                default:
                    std::cout << "Please enter a valid option.\n" << std::endl;
            }
    }
}
