/***********************************************************************************************************************
* Title......: Math Tutor V3
* Programmers: Muhammad Bilal, Jacob Lilly
* Date.......: 2025.10.14
* Git Repo: https://github.com/mbilalcyber/MathTutor.V3.git
* Description: This program is designed to teach you how to learn math.
               It will tell them a funny joke, and it will ask the user's
               name to greet them. Then, it will generate random numbers
               and chose a operation to ask random simple math questions.
               It will ask the user by their name the math question. It
               will check their answer with the right answer. Then the
               program will either say Correct, or incorect then give them
               the right answer so they can learn. After that it will tell
               the user that this is all the program does at this time
***********************************************************************************************************************/

#include <iostream>   // console input or output
#include <string>     // string and get line
#include <cstdlib>    // rand and srand
#include <ctime>      // time for random seed

using namespace std;

int main() {
    string userName = "?";
    int leftNum = 0;
    int rightNum = 0;
    int mathType = 0;
    char mathSymbol = '?';
    int correctAnswer = 0;
    int userAnswer = 0;
    int temp = 0;

    srand(time(0));

    std::cout << R"( _____ _             _       ___  ___      _   _       _____     _
/  ___(_)           | |      |  \/  |     | | | |     |_   _|   | |
\ `--. _ _ __   __ _| | ___  | .  . | __ _| |_| |__     | |_   _| |_ ___  _ __
 `--. \ | '_ \ / _` | |/ _ \ | |\/| |/ _` | __| '_ \    | | | | | __/ _ \| '__|
/\__/ / | | | | (_| | |  __/ | |  | | (_| | |_| | | |   | | |_| | || (_) | |
\____/|_|_| |_|\__, |_|\___| \_|  |_/\__,_|\__|_| |_|   \_/\__,_|\__\___/|_|
                __/ |
               |___/
)" << std::endl;
    cout << "Enter your full name: ";
    getline(cin, userName);

    leftNum = (rand() % 10) + 1;
    rightNum = (rand() % 10) + 1;
    mathType = (rand() % 4) + 1;
    // Choose the operation using a switch
    switch (mathType) {
        case 1: // Doing Addition
            mathSymbol = '+';
        correctAnswer = leftNum + rightNum;
        break;
        // Subtraction: swap so answer is not negative
        case 2:
            if (leftNum < rightNum) {
                temp = leftNum;
                leftNum = rightNum;
                rightNum = temp;
            }
        mathSymbol = '-';
        correctAnswer = leftNum - rightNum;
        break;

        case 3: // Multiplication
            mathSymbol = '*';
        correctAnswer = leftNum * rightNum;
        break;

        case 4: // Division: make a clean integer answer (no fractions)
            mathSymbol = '/';
        correctAnswer = leftNum;      // keep original left as the answer
        leftNum = leftNum * rightNum;   // now leftNum / rightNum == original left
        break;

        default:
            cout << "Error: Contact Debbie." << endl;
        return -1;
    }

    // Single cout to display the full question line
    cout << endl << userName << ", what is "
         << leftNum << " " << mathSymbol << " " << rightNum << " ?" << endl;
    cout << "Your answer: ";
    cin >> userAnswer;

    if (userAnswer == correctAnswer) {
        cout << "Correct!" << endl;
    }
    else {
        cout << "Incorrect. The correct answer was " << correctAnswer << endl;
    }

    cout << "Thanks for playing, " << userName << "!" << endl;

    return 0;
}