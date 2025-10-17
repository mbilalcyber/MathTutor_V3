/***********************************************************************************************************************
* Title......: Math Tutor V3
* Programmers: Muhammad Bilal, Jacob Lilly
* Date.......: 2025.10.14
* Git Repo: https://github.com/mbilalcyber/MathTutor.V3.git
* Description:
 * - The program is designed to help users practice and learn basic math.
 * - It starts by telling a funny joke.
 * - It asks the user to enter their name and greets them personally.
 * - The program generates two random numbers.
 * - It randomly chooses one of the four operations: addition, subtraction, multiplication, or division.
 * - It asks the user a math question using their name.
 * - The user's answer is checked against the correct answer.
 * - If the answer is correct, the program displays a "Correct" message.
 * - If the answer is wrong, it shows the correct answer so the user can learn.
 * - The program continues asking questions based on the user's choice.
 * - Finally, it tells the user that this is all the program does at the moment.
***********************************************************************************************************************/

#include <iostream>   // console input or output
#include <string>     // string and get line
#include <cstdlib>    // rand and srand
#include <ctime>      // time for random seed
#include <limits>
using namespace std;

int main() {
    string userName = "?";
    int leftNum = 0;
    int rightNum = 0;
    char mathSymbol = '?';
    int correctAnswer = 0;
    int userAnswer = 0;
    int temp = 0;
    string userInput = "?";


    enum MathType { MT_ADD = 1, MT_SUB, MT_MUL, MT_DIV };
    MathType mathType = MT_ADD;
    while (!(cin >> userName)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<< "\tInvalid input!" << endl;
        cout << "\tPlease enter a number: ";
    } // end of get userAnswer while loop


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


    do {
        leftNum = (rand() % 10) + 1;
        rightNum = (rand() % 10) + 1;
        mathType = static_cast <MathType>(rand() % 4) + 1;

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

    } while (userInput == "yes" || userInput == "y");

    return 0;
}