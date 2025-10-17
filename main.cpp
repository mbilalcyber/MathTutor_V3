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

#include <iostream>
#include <string>
#include <cstdlib>   // rand, srand
#include <ctime>     // time()
#include <limits>    // numeric_limits
#include <cctype>    // tolower
using namespace std;

// constants
const int MAX_ATTEMPTS = 3;         // User has 3 tries per question
const int LEVEL_RANGE_CHANGE = 10;  // The jump between number

// enum for math type
enum MathType { MT_ADD = 1, MT_SUB, MT_MUL, MT_DIV };

// read a valid integer (keeps asking until user types a number)
int readInt() {
    int value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a number: ";
    }
    return value;
}

int main() {
    // random seed
    srand(static_cast<unsigned>(time(0)));

    // state variables
    int totalCorrect = 0;
    int totalIncorrect = 0;
    int mathLevel = 1;                        // start at level 1
    int levelRange = LEVEL_RANGE_CHANGE;      // current number range (1..levelRange)
    string userInput = "?";                   // for y/yes/n/no
    string userName;

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
    if (userName.empty()) userName = "Friend";
    cout << "Welcome " << userName << " to the Silly Simple Math Tutor!\n\n";

    // main question loop
    do {
        // generate numbers based on current range
        int leftNum  = (rand() % levelRange) + 1;
        int rightNum = (rand() % levelRange) + 1;

        // choose a random math type (enum)
        MathType mathType = static_cast<MathType>((rand() % 4) + 1);

        // build a question and its correct answer
        int correctAnswer = 0;
        char op = '?';
        switch (mathType) {
            case MT_ADD:
                op = '+';
                correctAnswer = leftNum + rightNum;
                break;
            case MT_SUB:
                op = '-';
                // keep subtraction non-negative to match beginner style
                if (leftNum < rightNum) {
                    int t = leftNum; leftNum = rightNum; rightNum = t;
                }
                correctAnswer = leftNum - rightNum;
                break;
            case MT_MUL:
                op = '*';
                correctAnswer = leftNum * rightNum;
                break;
            case MT_DIV:
                op = '/';
                // force a clean integer answer: pick divisor and scale dividend
                rightNum = (rand() % (max(1, levelRange / 2) )) + 1;
                if (rightNum < 1) rightNum = 1;
                {
                    int maxK = max(1, levelRange / rightNum);
                    int k = (rand() % maxK) + 1;
                    leftNum = rightNum * k;  // divisible
                }
                correctAnswer = leftNum / rightNum;
                break;
        }

        // give the user 3 attempts
        bool solved = false;
        for (int attempt = 1; attempt <= MAX_ATTEMPTS; ++attempt) {
            cout << "[Level #" << mathLevel << "] " << userName
                 << ", what does " << leftNum << op << rightNum << " = ";
            int userAnswer = readInt();

            if (userAnswer == correctAnswer) {
                cout << "    Congrats! That was correct :)" << endl;
                totalCorrect++;
                solved = true;
                break;
            } else {
                int left = MAX_ATTEMPTS - attempt;
                if (left > 0) {
                    cout << "    Bummer, that was incorrect." << endl;
                    cout << "    You have " << left << " attempt(s) left." << endl;
                } else {
                    cout << "    Sorry, you are out of attempts." << endl;
                    cout << "    The correct answer is " << correctAnswer << endl;
                    totalIncorrect++;
                }
            }
        }

        // check for leveling up or down after the attempts
        if (totalCorrect == 3) {
            mathLevel++;
            totalCorrect = 0;
            totalIncorrect = 0;
            levelRange += LEVEL_RANGE_CHANGE;
            cout << "WooHoo - Leveling you UP to " << mathLevel << endl;
            cout << "The numbers are now between 1 and " << levelRange << endl;
        } else if (totalIncorrect == 3 && mathLevel > 1) {
            mathLevel--;
            totalCorrect = 0;
            totalIncorrect = 0;
            levelRange -= LEVEL_RANGE_CHANGE;
            cout << "BooHoo - Leveling you DOWN to " << mathLevel << endl;
            cout << "The numbers are now between 1 and " << levelRange << endl;
        }

        // ask to continue. not case sensitive and accepts y or n
        // clear leftover newline from the last number read
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        while (true) {
            cout << "Do you want to continue (y=yes | n=no)? ";
            getline(cin, userInput);

            // makes it lowercase
            for (char &ch : userInput) ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));

            if (userInput == "y" || userInput == "yes" ||
                userInput == "n" || userInput == "no") {
                break; // valid
            } else {
                cout << "Please type y, yes, n, or no.\n";
            }
        }

    } while (userInput == "y" || userInput == "yes");

    cout << "Thanks for playing " << userName << "! Come back soon to learn more!" << endl;
    return 0;
}int main() {
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

    const int maxAttemps = 3;           // User has 3 tries per question
    const int levelRangeChange = 10;    // The jump between number range for levels


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

                // if the program cant pick, it will give them this error code
            default:
                cout << "Error: Contact Jacob or Bilal." << endl;
                cout << "This shouldnt happen :(." << endl;
                return -1;
        }
        // allows user 3 attempts to give correct answer and tells them the level they are on
        for (int i=1; i<= maxAttemps; i++) {
            cout << "[Level " << level << "] " << userName << "what is "
                    << leftNum << " " << mathSymbol << " " << rightNum << " equal?" << endl;
            cout << "Your answer: ";
            cin >> userAnswer;

            // checks if response is valid
            while (!(cin >> userInput)) {
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
            }

            // Tells them how many attempts are left
            else {
                cout << "You have " << maxAttemps - i << " attempts left" << endl;
            }
        }
    } // ends user attempts

    // checks for 3 correct answers then increases level up
    // it will increse the range to add extra 10 numbers
    if (totalCorrect == 3) {
        level ++;
        totalCorrect = 0;
        totalIncorrect = 0;
        currentRange += currentRange;
        cout << "Congrats, you leveled up!" << endl;
        cout << "Your new level is " << level << " with numbers ranging from 1 to " << currentRange << endl;
    }

    // checks for 3 wrong answers then lowers their level if its above level 1
    if (totalIncorrect == 3 && level > 1) {
        level --;
        totalCorrect = 0;
        totalIncorrect = 0;
        currentRange = currentRange;
        cout << "You leveled down. Your new level is" << level
        << "with numbers ranging from 1 to" << currentRange << endl;
    }


                cout << "Thanks for playing, " << userName << "!" << endl;

            return 0;
        }