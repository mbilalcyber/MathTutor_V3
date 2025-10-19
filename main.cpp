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

          
if (totalCorrect == MAX_ATTEMPTS) {
    mathLevel++;
    totalCorrect = 0;
    totalIncorrect = 0;
    currentRange += LEVEL_RANGE_CHANGE;
	
    cout << "Level up! You’re now Level " << mathLevel
		
         << ". Range is now 1.." << currentRange << endl;
	
} else if (totalIncorrect == MAX_ATTEMPTS && mathLevel > 1) {
    mathLevel--;
    totalCorrect = 0;
    totalIncorrect = 0;
    currentRange -= LEVEL_RANGE_CHANGE;
    if (currentRange < LEVEL_RANGE_CHANGE) currentRange = LEVEL_RANGE_CHANGE;
	
    cout << "Level down. You’re now Level " << mathLevel
         << ". Range is now 1.." << currentRange << endl;
} 

// Clear leftover newline 
cin.ignore(numeric_limits<streamsize>::max(), '\n');

// wording + lowercase handling change
while (true) {
    cout << "Do you want another question (y=yes | n=no)? ";
    getline(cin, userInput);

    for (char &ch : userInput) {
        ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    }

    if (userInput == "y" || userInput == "yes" ||
        userInput == "n" || userInput == "no") {
        break;
    } else {
        cout << "Please type y, yes, n, or no." << endl << endl;
    }
}

} while (userInput == "yes" || userInput == "y");

cout << "Thanks for using Math Tutor. Good luck on your test!" << endl;
return 0;
