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

    getline(cin, userName);
    if (userName.empty()) userName = "User";
    cout << "Welcome " << userName << " to the Silly Simple Math Tutor!\n";


    // Build the question and compute the correct answer 
switch (mathType) {
    case MT_ADD: {
        mathSymbol = '+';
        correctAnswer = leftNum + rightNum;
        break;
    }
    case MT_SUB: {
        mathSymbol = '-';
        if (leftNum < rightNum) {
            temp = leftNum;
            leftNum = rightNum;
            rightNum = temp;
        }
        correctAnswer = leftNum - rightNum;
        break;
    }
    case MT_MUL: {
        mathSymbol = '*';
        correctAnswer = leftNum * rightNum;
        break;
    }
    case MT_DIV: {
        // keep division as an integer result
        mathSymbol = '/';
        correctAnswer = leftNum;  // original left is the answer
        leftNum *= rightNum;      // make dividend a multiple of divisor
        break;
    }
    default: {
        cout << "Invalid math type: " << static_cast<int>(mathType) << endl;
        cout << "Exiting due to invalid operation. Please notify the instructor." << endl;
        return -1;
    }
}

	
for (int i = 1; i <= MAX_ATTEMPTS; ++i) {
    cout << "[Level " << mathLevel << "] " << userName
         << ", what is " << leftNum << " " << mathSymbol << " " << rightNum << " = ";

    // numeric guard
    while (!(cin >> userAnswer)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\tInvalid input. Please enter a number: ";
    }

    if (userAnswer == correctAnswer) {
        totalCorrect++;
        cout << "\tCorrect nice work dude!" << endl;
        cout << "\tStreak: " << totalCorrect << " correct" << endl << endl;
        break;
    } else {
        if (i == MAX_ATTEMPTS) {
            totalIncorrect++;
            cout << "\tOut of attempts. Correct answer: " << correctAnswer << endl;
        } else {
            cout << "\tNot quite. Attempts remaining: " << (MAX_ATTEMPTS - i) << endl;
        }
    }
}

            // if answer is correct, it'll say congrats then break
            if (userAnswer == correctAnswer) {
                totalCorrect ++;
                cout << "Correct!" << endl;
                break;
            }
            //if incorrect, it'll say incorrect and break
            if (i >= maxAttemps) {
                cout << "Incorrect. The correct answer was " << correctAnswer << endl;
                totalIncorrect++;
            }

            // Tells them how many attempts are left
            else {
                cout << "You have " << maxAttemps - i << " attempts left" << endl;
                cout << "Dont give up!" << endl;
            }
        } // ends user attempts



        // checks for 3 correct answers then increases level up
        // it will increase the range to add extra 10 numbers
        if (totalCorrect == 3) {
            currentLevel++;
            totalCorrect = 0;   // new level means clen record
            totalIncorrect = 0; // goes back to defaults
            currentRange += levelRange;
            cout << "Congrats, you leveled up!" << endl;
            cout << "Your new level is " << currentLevel << " with numbers ranging from 1 to " << currentRange << endl;
        }

        // checks for 3 wrong answers then lowers their level if its above level 1
        if (totalIncorrect >= 3 && currentLevel > 1) {
            currentLevel --;
            totalCorrect = 0;      // resets to 0
            totalIncorrect = 0;    // back to defaults
            currentRange -= levelRange;
            if (currentRange < levelRange) currentRange = levelRange; //
            cout << "You leveled down. You're now on Level " << currentLevel
                 << " with numbers ranging from 1 to " << currentRange << endl;

        } // end of main question loop // DEBBIE: this is not the end of main loop - this is the end of the if statement

		// DEBBIE: you need to have the code logic here for y/n input that I provided you in the assignment

		// DEBBIE: this is where the end of the do-while should be for y/yes answer

    cout << "Thanks for playing, " << userName << "!" << endl;
    return 0;

        return 0; // DEBBIE: don't need
    } // don't need if you end your while loop on like 206 like I stated
} // DEBBIE: end of main function
