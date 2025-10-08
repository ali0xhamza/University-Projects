#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <limits>
#include <stdlib.h> // For system("cls")

using namespace std;

// Structure to store user information
struct User
{
    string username;
    string password;
    string background;
    int biologyScore;
    int mathScore;
    int physicsScore;
    int chemistryScore;
    int computerScore;
    int totalScore;
};

// Structure for quiz questions
struct Question
{
    string questionText;
    vector<string> options;
    char correctAnswer;
    string subject;
};

// Global variables
vector<User> users;
User currentUser;
vector<Question> questions;

// Function prototypes
void clearScreen();
void loadQuestions();
void saveUserData();
void loadUserData();
void signUpScreen();
bool loginScreen();
void backgroundSelectionScreen();
void quizScreen();
void resultsScreen();
void adminPanel();
void addQuestion();

// Main function
int main()
{
    loadQuestions();
    loadUserData();

    int choice;
    bool loggedIn = false;

    do
    {
        clearScreen();
        cout << "\n\n\t\tQUIZ APPLICATION\n";
        cout << "\t\t----------------\n";
        cout << "\t1. Sign Up\n";
        cout << "\t2. Login\n";
        cout << "\t3. Exit\n";
        cout << "\tEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            signUpScreen();
            break;
        case 2:
            loggedIn = loginScreen();
            if (loggedIn)
            {
                if (currentUser.username == "admin")
                {
                    adminPanel();
                }
                else
                {
                    backgroundSelectionScreen();
                    quizScreen();
                    resultsScreen();
                    saveUserData();
                }
            }
            break;
        case 3:
            cout << "\n\tThank you for using the Quiz Application!\n";
            break;
        default:
            cout << "\n\tInvalid choice. Please try again.\n";
            cin.ignore();
            cin.get();
        }
    } while (choice != 3);

    return 0;
}

void clearScreen()
{
    system("cls"); // For Windows
    // system("clear"); // For Linux/Mac
}

// Load quiz questions
void loadQuestions()
{
    // Biology questions
    questions.push_back({"Which of the following is the basic unit of life?",
                         {"Cell", "Tissue", "Organ", "Organ System"},
                         'A',
                         "Biology"});
    questions.push_back({"Photosynthesis occurs in which part of the plant cell?",
                         {"Mitochondria", "Chloroplast", "Nucleus", "Ribosome"},
                         'B',
                         "Biology"});
    questions.push_back({"Which of these is not a function of the liver?",
                         {"Protein synthesis", "Detoxification", "Glycogen storage", "Oxygen transport"},
                         'D',
                         "Biology"});

    // Chemistry questions
    questions.push_back({"What is the pH of pure water at 25°C?",
                         {"5", "7", "10", "14"},
                         'B',
                         "Chemistry"});
    questions.push_back({"Which of these is a noble gas?",
                         {"Oxygen", "Nitrogen", "Neon", "Chlorine"},
                         'C',
                         "Chemistry"});
    questions.push_back({"The process of converting a solid directly to gas is called:",
                         {"Sublimation", "Evaporation", "Condensation", "Fusion"},
                         'A',
                         "Chemistry"});

    // Physics questions
    questions.push_back({"The SI unit of force is:",
                         {"Joule", "Watt", "Newton", "Pascal"},
                         'C',
                         "Physics"});
    questions.push_back({"Which law states that every action has an equal and opposite reaction?",
                         {"Newton's First Law", "Newton's Second Law", "Newton's Third Law", "Ohm's Law"},
                         'C',
                         "Physics"});
    questions.push_back({"The unit of electric current is:",
                         {"Volt", "Ohm", "Ampere", "Watt"},
                         'C',
                         "Physics"});

    // Math questions
    questions.push_back({"What is the derivative of x²?",
                         {"x", "2x", "x³/3", "2"},
                         'B',
                         "Math"});
    questions.push_back({"If a triangle has angles 45°, 45°, and 90°, it is:",
                         {"Isosceles", "Equilateral", "Scalene", "Obtuse"},
                         'A',
                         "Math"});
    questions.push_back({"The value of π (pi) is approximately:",
                         {"3.14", "2.71", "1.61", "1.41"},
                         'A',
                         "Math"});

    // Computer questions
    questions.push_back({"Which of these is not a programming language?",
                         {"Python", "Java", "HTML", "C++"},
                         'C',
                         "Computer"});
    questions.push_back({"The brain of a computer is:",
                         {"CPU", "RAM", "Hard Disk", "Monitor"},
                         'A',
                         "Computer"});
    questions.push_back({"Which of these is an example of an operating system?",
                         {"Microsoft Word", "Windows", "Google Chrome", "Adobe Photoshop"},
                         'B',
                         "Computer"});
}

// Save user data to file
void saveUserData()
{
    ofstream outFile("users.txt");
    if (outFile.is_open())
    {
        for (const auto &user : users)
        {
            outFile << user.username << " "
                    << user.password << " "
                    << user.background << " "
                    << user.biologyScore << " "
                    << user.mathScore << " "
                    << user.physicsScore << " "
                    << user.chemistryScore << " "
                    << user.computerScore << " "
                    << user.totalScore << "\n";
        }
        outFile.close();
    }
    else
    {
        cout << "\n\tError: Unable to save user data!\n";
    }
}

// Load user data from file
void loadUserData()
{
    ifstream inFile("users.txt");
    users.clear();
    if (inFile.is_open())
    {
        User user;
        while (inFile >> user.username >> user.password >> user.background >> user.biologyScore >> user.mathScore >> user.physicsScore >> user.chemistryScore >> user.computerScore >> user.totalScore)
        {
            users.push_back(user);
        }
        inFile.close();
    }

    // Add admin user if not exists
    bool adminExists = false;
    for (const auto &user : users)
    {
        if (user.username == "admin")
        {
            adminExists = true;
            break;
        }
    }
    if (!adminExists)
    {
        User admin;
        admin.username = "admin";
        admin.password = "admin123";
        admin.background = "Admin";
        users.push_back(admin);
        saveUserData();
    }
}

// Sign up screen
void signUpScreen()
{
    clearScreen();
    User newUser;
    cout << "\n\n\t\tSIGN UP SCREEN\n";
    cout << "\t\t--------------\n";
    cout << "\tEnter username: ";
    cin >> newUser.username;

    // Check if username already exists
    for (const auto &user : users)
    {
        if (user.username == newUser.username)
        {
            cout << "\n\tUsername already exists. Please choose another.\n";
            cin.ignore();
            cin.get();
            return;
        }
    }

    cout << "\tEnter password: ";
    cin >> newUser.password;

    // Initialize scores
    newUser.biologyScore = 0;
    newUser.mathScore = 0;
    newUser.physicsScore = 0;
    newUser.chemistryScore = 0;
    newUser.computerScore = 0;
    newUser.totalScore = 0;
    newUser.background = ""; // Will be set in background selection screen

    users.push_back(newUser);
    currentUser = newUser;
    saveUserData();
    cout << "\n\tRegistration successful! Press enter to continue...";
    cin.ignore();
    cin.get();
}

// Login screen
bool loginScreen()
{
    clearScreen();
    string username, password;
    cout << "\n\n\t\tLOGIN SCREEN\n";
    cout << "\t\t------------\n";
    cout << "\tEnter username: ";
    cin >> username;
    cout << "\tEnter password: ";
    cin >> password;

    for (auto &user : users)
    {
        if (user.username == username && user.password == password)
        {
            currentUser = user;
            cout << "\n\tLogin successful! Press enter to continue...";
            cin.ignore();
            cin.get();
            return true;
        }
    }

    cout << "\n\tInvalid username or password. Press enter to try again...";
    cin.ignore();
    cin.get();
    return false;
}

// Background selection screen
void backgroundSelectionScreen()
{
    clearScreen();
    int bgChoice;
    cout << "\n\n\t\tBACKGROUND SELECTION\n";
    cout << "\t\t--------------------\n";
    cout << "\t1. FSC Biology\n";
    cout << "\t2. FSC Math\n";
    cout << "\t3. ICS\n";
    cout << "\tEnter your choice (1-3): ";
    cin >> bgChoice;

    switch (bgChoice)
    {
    case 1:
        currentUser.background = "FSC Biology";
        break;
    case 2:
        currentUser.background = "FSC Math";
        break;
    case 3:
        currentUser.background = "ICS";
        break;
    default:
        cout << "\n\tInvalid choice. Defaulting to FSC Biology.\n";
        currentUser.background = "FSC Biology";
    }

    // Update the user in the users vector
    for (auto &user : users)
    {
        if (user.username == currentUser.username)
        {
            user = currentUser;
            break;
        }
    }

    cout << "\n\tBackground selected: " << currentUser.background << "\n";
    cout << "\tPress enter to start the quiz...";
    cin.ignore();
    cin.get();
}

// Quiz screen
void quizScreen()
{
    clearScreen();
    vector<Question> quizQuestions;
    map<string, int> subjectCounts;

    // Determine which subjects to include based on background
    if (currentUser.background == "FSC Biology")
    {
        subjectCounts["Biology"] = 3;
        subjectCounts["Chemistry"] = 2;
        subjectCounts["Physics"] = 2;
    }
    else if (currentUser.background == "FSC Math")
    {
        subjectCounts["Math"] = 3;
        subjectCounts["Chemistry"] = 2;
        subjectCounts["Physics"] = 2;
    }
    else if (currentUser.background == "ICS")
    {
        subjectCounts["Computer"] = 3;
        subjectCounts["Math"] = 2;
        subjectCounts["Physics"] = 2;
    }

    // Select questions for the quiz
    for (const auto &question : questions)
    {
        if (subjectCounts[question.subject] > 0)
        {
            quizQuestions.push_back(question);
            subjectCounts[question.subject]--;
        }
    }

    // Shuffle the questions
    random_shuffle(quizQuestions.begin(), quizQuestions.end());

    // Reset scores
    currentUser.biologyScore = 0;
    currentUser.mathScore = 0;
    currentUser.physicsScore = 0;
    currentUser.chemistryScore = 0;
    currentUser.computerScore = 0;
    currentUser.totalScore = 0;

    // Take the quiz
    clearScreen();
    cout << "\n\n\t\tQUIZ SCREEN\n";
    cout << "\t\t-----------\n";
    cout << "\tThere are " << quizQuestions.size() << " questions in this quiz.\n";
    cout << "\tPress enter to begin...";
    cin.ignore();
    cin.get();

    for (size_t i = 0; i < quizQuestions.size(); i++)
    {
        clearScreen();
        const auto &q = quizQuestions[i];
        cout << "\n\tQuestion " << i + 1 << " of " << quizQuestions.size() << " (" << q.subject << ")\n";
        cout << "\t---------------------------------\n";
        cout << "\t" << q.questionText << "\n\n";
        for (size_t j = 0; j < q.options.size(); j++)
        {
            cout << "\t" << char('A' + j) << ") " << q.options[j] << "\n";
        }

        char answer;
        bool validAnswer = false;
        do
        {
            cout << "\n\tYour answer (A-D): ";
            cin >> answer;
            answer = toupper(answer);
            if (answer >= 'A' && answer <= 'D')
            {
                validAnswer = true;
            }
            else
            {
                cout << "\tInvalid input. Please enter A, B, C, or D.\n";
            }
        } while (!validAnswer);

        if (answer == q.correctAnswer)
        {
            cout << "\n\tCorrect!\n";

            // Update scores based on subject
            if (q.subject == "Biology")
                currentUser.biologyScore++;
            else if (q.subject == "Math")
                currentUser.mathScore++;
            else if (q.subject == "Physics")
                currentUser.physicsScore++;
            else if (q.subject == "Chemistry")
                currentUser.chemistryScore++;
            else if (q.subject == "Computer")
                currentUser.computerScore++;

            currentUser.totalScore++;
        }
        else
        {
            cout << "\n\tIncorrect. The correct answer is " << q.correctAnswer << ".\n";
        }
        cout << "\n\tPress enter to continue...";
        cin.ignore();
        cin.get();
    }

    // Update the user in the users vector
    for (auto &user : users)
    {
        if (user.username == currentUser.username)
        {
            user = currentUser;
            break;
        }
    }
}

// Results screen
void resultsScreen()
{
    clearScreen();
    cout << "\n\n\t\tRESULTS SCREEN\n";
    cout << "\t\t--------------\n";
    cout << "\tUsername: " << currentUser.username << "\n";
    cout << "\tBackground: " << currentUser.background << "\n";
    cout << "\n\tSubject-wise Scores:\n";

    if (currentUser.background == "FSC Biology")
    {
        cout << "\tBiology: " << currentUser.biologyScore << "/3\n";
        cout << "\tChemistry: " << currentUser.chemistryScore << "/2\n";
        cout << "\tPhysics: " << currentUser.physicsScore << "/2\n";
    }
    else if (currentUser.background == "FSC Math")
    {
        cout << "\tMath: " << currentUser.mathScore << "/3\n";
        cout << "\tChemistry: " << currentUser.chemistryScore << "/2\n";
        cout << "\tPhysics: " << currentUser.physicsScore << "/2\n";
    }
    else if (currentUser.background == "ICS")
    {
        cout << "\tComputer: " << currentUser.computerScore << "/3\n";
        cout << "\tMath: " << currentUser.mathScore << "/2\n";
        cout << "\tPhysics: " << currentUser.physicsScore << "/2\n";
    }

    cout << "\n\tTotal Score: " << currentUser.totalScore << "/7\n";
    cout << "\n\tPress enter to return to main menu...";
    cin.ignore();
    cin.get();
}

// Admin panel for managing questions
void adminPanel()
{
    int choice;
    do
    {
        clearScreen();
        cout << "\n\n\t\tADMIN PANEL\n";
        cout << "\t\t-----------\n";
        cout << "\t1. Add New Question\n";
        cout << "\t2. View All Questions\n";
        cout << "\t3. View All Users\n";
        cout << "\t4. Back to Main Menu\n";
        cout << "\tEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addQuestion();
            break;
        case 2:
            clearScreen();
            cout << "\n\tALL QUESTIONS\n";
            cout << "\t-------------\n";
            for (size_t i = 0; i < questions.size(); i++)
            {
                const auto &q = questions[i];
                cout << "\tQuestion " << i + 1 << " (" << q.subject << "): " << q.questionText << "\n";
                for (size_t j = 0; j < q.options.size(); j++)
                {
                    cout << "\t" << char('A' + j) << ") " << q.options[j] << "\n";
                }
                cout << "\tCorrect Answer: " << q.correctAnswer << "\n\n";
            }
            cout << "\n\tPress enter to continue...";
            cin.ignore();
            cin.get();
            break;
        case 3:
            clearScreen();
            cout << "\n\tALL USERS\n";
            cout << "\t---------\n";
            for (const auto &user : users)
            {
                if (user.username != "admin")
                {
                    cout << "\tUsername: " << user.username << "\n";
                    cout << "\tBackground: " << user.background << "\n";
                    cout << "\tTotal Score: " << user.totalScore << "\n";
                    cout << "\t------------------------\n";
                }
            }
            cout << "\n\tPress enter to continue...";
            cin.ignore();
            cin.get();
            break;
        case 4:
            cout << "\n\tReturning to main menu...\n";
            break;
        default:
            cout << "\n\tInvalid choice. Please try again.\n";
            cin.ignore();
            cin.get();
        }
    } while (choice != 4);
}

// Add new question (admin only)
void addQuestion()
{
    clearScreen();
    Question newQuestion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n\n\t\tADD NEW QUESTION\n";
    cout << "\t\t---------------\n";
    cout << "\tEnter question text: ";
    getline(cin, newQuestion.questionText);

    newQuestion.options.resize(4);
    cout << "\tEnter option A: ";
    getline(cin, newQuestion.options[0]);
    cout << "\tEnter option B: ";
    getline(cin, newQuestion.options[1]);
    cout << "\tEnter option C: ";
    getline(cin, newQuestion.options[2]);
    cout << "\tEnter option D: ";
    getline(cin, newQuestion.options[3]);

    char correctAns;
    cout << "\tEnter correct answer (A-D): ";
    cin >> correctAns;
    newQuestion.correctAnswer = toupper(correctAns);

    int subjectChoice;
    cout << "\n\tSelect subject:\n";
    cout << "\t1. Biology\n";
    cout << "\t2. Chemistry\n";
    cout << "\t3. Physics\n";
    cout << "\t4. Math\n";
    cout << "\t5. Computer\n";
    cout << "\tEnter choice (1-5): ";
    cin >> subjectChoice;

    switch (subjectChoice)
    {
    case 1:
        newQuestion.subject = "Biology";
        break;
    case 2:
        newQuestion.subject = "Chemistry";
        break;
    case 3:
        newQuestion.subject = "Physics";
        break;
    case 4:
        newQuestion.subject = "Math";
        break;
    case 5:
        newQuestion.subject = "Computer";
        break;
    default:
        newQuestion.subject = "General";
    }

    questions.push_back(newQuestion);
    cout << "\n\tQuestion added successfully! Press enter to continue...";
    cin.ignore();
    cin.get();
}