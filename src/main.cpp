// Includes
#include <base.h>
#include <tester/quiz.h>
#include <interface/cli.h>

// Functions

// Entry point
int main(int argc, char* argv[]){
    // Loading a new test
    Quiz quiz = Quiz("data/exams/CompTIA 1101.json", 50);

    // Init application
    Tester_CLI cli;

    // Showing the Main Menu
    cli.MainMenu(quiz);
    std::string menu; std::cin >> menu;
    int numOfQuestions = 0;

    if(menu == "1"){
        numOfQuestions = 15;
    }
    else if(menu == "2"){
        numOfQuestions = 30;
    }
    else if(menu == "3"){
        numOfQuestions = 60;
    }
    else if(menu == "4"){
        return 0;
    }

    // Making new quiz
    quiz = Quiz("data/exams/CompTIA 1101.json", numOfQuestions);

    // Asking the user questions
    cli.AskQuestions(quiz, numOfQuestions);

    // Exit
    return 0;
}
