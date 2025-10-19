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

// DEBBIE: this really should be inside main at the top
// enum for math type
enum MathType { MT_ADD = 1, MT_SUB, MT_MUL, MT_DIV };

int main() {
    // DEBBIE: seeding the random should be after all variables
	
	// state variables
    int leftNum = 0;
    int rightNum = 0;

    char mathSymbol = '?';

    int correctAnswer = 0;
    int userAnswer = 0;

    int temp = 0;
    int totalCorrect = 0;
    int totalIncorrect = 0;
    int currentLevel = 1;
    int currentRange = 1; // DEBBIE: should be initialized to a constant variable LEVEL_RANGE_CHANGE

    string userInput = "?";
    string userName = "?";

	// random seed
    srand(static_cast<unsigned>(time(0)));

	// DEBBIE: const variables should be the first variables in main and they need to be all UPPER_CASED
	// DEBBIE: MAX_ATTEMPTS and LEVEL_RANGE_CHANGE
    const int MAXATTEMPTS = 3;     // User has 3 tries per question
    const int LEVELRANGE = 10;    // The jump between number range for levels

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
    cout << "Welcome " << userName << " to the Silly Simple Math Tutor!\n\n";
	// DEBBIE: NOTE - you only need one blank line for code logic separation


    // main question loop
    do {
        // generate numbers based on current range
        int leftNum = (rand() % currentRange) + 1;
        int rightNum = (rand() % currentRange) + 1;

        // choose a random math type (enum)
        MathType mathType = static_cast<MathType>((rand() % 4) + 1);

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
				// DEBBIE: do this how Chapter 2 & 3 (MathTutorV2) explains how to write this logic
				// DEBBIE: also make sure your code is properly indented
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

                // if the program cant pick, it will give them this error code
            default:
				// DEBBIE: again look at how Ch 2 & 3 (MathTutorV2) is suppose to write this
				// DEBBIE: you should be displaying the invalid mathType too
                cout << "Error: Contact Jacob or Bilal." << endl;
                cout << "This shouldnt happen :(" << endl;
                return -1;
        }// DEBBIE: always have a blank line before & after constructs
        // allows user 3 attempts to give correct answer and tells them the level they are on
        // It also asks them the question
        for (int i=1; i<= maxAttemps; i++) {
            cout << "[Level " << currentLevel << "] " << userName << "what is "
                    << leftNum << " " << mathSymbol << " " << rightNum << " equal?" << endl;
            cout << "Your answer: ";
            cin >> userAnswer; // DEBBIE: delete this line because the while loop is doing this for you

			// DEBBIE: I recommend adding tabs (\t) for all output related to the current question

            // checks if response is valid
            while (!(cin >> userAnswer)) { // DEBBIE: fully document the while loop like I did in the assignment code example
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Please enter a number:"   << endl; // tells user to give it a number if it was invalid
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
