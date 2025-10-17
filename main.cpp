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
    //Variables
    char mathSymbol = '?';

    int leftNum = 0;
    int rightNum = 0;
    int correctAnswer = 0;
    int userAnswer = 0;
    int temp = 0;
    int totalCorrect = 0;
    int totalIncorrect = 0;
    int level = 1;
    int currentRange = 1;

    string userInput = "y";
    string userName = "?";

    const int MaxAttemps = 3;           // User has 3 tries per question
    const int LevelRangeChange = 10;    // The jump between number range for levels


    enum MathType { MT_ADD = 1, MT_SUB, MT_MUL, MT_DIV };
    MathType mathType = MT_ADD;
    while (!(cin >> userName)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\tInvalid input!"           << endl;
        cout << "\tPlease enter a number:"   << endl;
    } // end of get userAnswer while loop


    srand(time(0));
    
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -       " << endl;
    cout << "     __  __       _   _       _____      _                          " << endl;
    cout << "    |  \\/  | __ _| |_| |__   |_   _|   _| |_ ___  _ __             " << endl;
    cout << "    | |\\/| |/ _` | __| '_ \\    | || | | | __/ _ \\| '__|          " << endl;
    cout << "    | |  | | (_| | |_| | | |   | || |_| | || (_) | |                " << endl;
    cout << "    |_|  |_|\\__,_|\\__|_| |_|   |_| \\__,_|\\__\\___/|_|           " << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -       " << endl;
    cout << "      Welcome to the Silly Simple Math Tutor  V3                    " << endl;
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -       " << endl;
    cout << endl;

    cout << "Enter your full name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, userName);
    if (userName.empty()) userName = "Friend";

    do {
        if (level < 1) level = 1;
        currentRange = level * LevelRangeChange;  // Level 1 -> 10, Level 2 -> 20, ...

        leftNum  = (rand() % currentRange) + 1;
        rightNum = (rand() % currentRange) + 1;

        mathType = static_cast <MathType>(rand() % 4) + 1;

        switch (mathType) {
            case 1: // Doing Addition
                mathSymbol = '+';
                correctAnswer = leftNum + rightNum;
                break;

            case 2: // Subtraction: swap so answer is not negative
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

            case 4: // Division: make a clean integer answer
                mathSymbol = '/';
                rightNum = (rand() % (currentRange / 2 + 1)) + 1; // divisor 1 (range/2+1)
                if (rightNum < 1) rightNum = 1;
            {
                int maxK = currentRange / rightNum;
                if (maxK < 1) maxK = 1;
                int k = (rand() % maxK) + 1;
                leftNum = rightNum * k; // divisible
            }
                correctAnswer = leftNum / rightNum;
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

        while (userInput == "y" || userInput == "Y");

    return 0;
}
