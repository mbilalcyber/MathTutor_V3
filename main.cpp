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

#include <iostream>  // cout, cin
#include <string>    // string, getline
#include <cstdlib>   // rand, srand
#include <ctime>     // time() for srand seed
#include <limits>    // numeric limits for input cleanup
#include <cctype>    // tolower for y/yes/n/no processing
using namespace std;


int main() {
	
    // constants
    const int MAX_ATTEMPTS = 3;          // user gets 3 tries per question
    const int LEVEL_RANGE_CHANGE = 10;   // each level changes range by 10

	enum MathType { MT_ADD = 1, MT_SUB, MT_MUL, MT_DIV }; // Enum for math type
	
	  // ===== State variables (then seed RNG) 
	
    int leftNum = 0;
    int rightNum = 0;

    char mathSymbol = '?';

    int correctAnswer = 0;
    int userAnswer = 0;

    int temp = 0;
    int totalCorrect = 0;     // streak of correct answers
    int totalIncorrect = 0;   // streak of incorrect answers
    int currentLevel = 1;
    int currentRange = LEVEL_RANGE_CHANGE; // start with 1..10 

    string userInput = "?";
    string userName = "?";

    // Seed the random number generator (after variables)
    srand(static_cast<unsigned>(time(0)));

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

	// Ask for user name 
    cout << "Enter your full name: ";
    getline(cin, userName);
    if (userName.empty()) userName = "User";
    cout << "Welcome " << userName << " to the Silly Simple Math Tutor!" << endl << endl;



    // Build the question and compute the correct answer 
do {
        // generate question numbers
        leftNum = (rand() % currentRange) + 1;
        rightNum = (rand() % currentRange) + 1;
        MathType mathType = static_cast<MathType>((rand() % 4) + 1);

        char mathSymbol = '?';

        // switch for math operation
        switch (mathType) {
            case MT_ADD:
                mathSymbol = '+';
                correctAnswer = leftNum + rightNum;
                break;
            case MT_SUB:
                mathSymbol = '-';
                if (leftNum < rightNum) { temp = leftNum; leftNum = rightNum; rightNum = temp; }
                correctAnswer = leftNum - rightNum;
                break;
            case MT_MUL:
                mathSymbol = '*';
                correctAnswer = leftNum * rightNum;
                break;
            case MT_DIV:
                mathSymbol = '/';
                correctAnswer = leftNum;
                leftNum *= rightNum;
                break;
            default:
        cout << "Invalid math type: " << static_cast<int>(mathType) << endl;
        cout << "Exiting due to invalid operation. Please notify Bilal and Jacob." << endl;
        return -1;
    }

	
// ask user 3 attempts
        for (int i = 1; i <= MAX_ATTEMPTS; i++) {
            cout << "[Level " << currentLevel << "] " << userName
                 << ", what is " << leftNum << " " << mathSymbol << " " << rightNum << " = ";

            while (!(cin >> userAnswer)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a valid number: ";
            }

            if (userAnswer == correctAnswer) {
                cout << "Correct, nice job!" << endl;
                totalCorrect++;
                break;
            } else {
                if (i == MAX_ATTEMPTS) {
                    totalIncorrect++;
                    cout << "Incorrect. Correct answer was: " << correctAnswer << endl;
                } else {
                    cout << "Try again. Attempts left: " << (MAX_ATTEMPTS - i) << endl;
                }
            }
        }

        // level up
        if (totalCorrect == MAX_ATTEMPTS) {
            currentLevel++;
            currentRange += LEVEL_RANGE_CHANGE;
            totalCorrect = 0;
            totalIncorrect = 0;
            cout << "Level up! Now you're at Level " << currentLevel
                 << " with range 1 to " << currentRange << endl;
        }

        // level down
        if (totalIncorrect == MAX_ATTEMPTS && currentLevel > 1) {
            currentLevel--;
            currentRange -= LEVEL_RANGE_CHANGE;
            if (currentRange < LEVEL_RANGE_CHANGE) currentRange = LEVEL_RANGE_CHANGE;
            totalCorrect = 0;
            totalIncorrect = 0;
            cout << "Level down. You're now Level " << currentLevel << endl;
        }

        // ask to continue
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while (true) {
            cout << "Do you want another question? (yes/no): ";
            getline(cin, userInput);
            for (char &ch : userInput) ch = tolower(ch);
            if (userInput == "y" || userInput == "yes" || userInput == "n" || userInput == "no") break;
        }

    } while (userInput == "y" || userInput == "yes");

    cout << "Thanks for playing " << userName << "! Goodbye." << endl;
    return 0;
}
