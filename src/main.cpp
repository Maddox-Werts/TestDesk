// Includes
#include <base.h>
#include <tester/quiz.h>
#include <interface/cli.h>
#include <interface/gui.h>

// Functions
void cli_version(){
    // Loading a new test
    Quiz quiz = Quiz("data/exams/CompTIA 1101.json", 5);

    // Init application
    Tester_CLI cli;

    // Showing the Main Menu
    cli.MainMenu(quiz);
    std::string menu; std::cin >> menu;
    int numOfQuestions = 0;

    // What page do we want?
    switch(menu[0]){
    case '1':
        numOfQuestions = 15;
        break;
    case '2':
        numOfQuestions = 30;
        break;
    case '3':
        numOfQuestions = 60;
        break;
    default:
        return;
    }

    // Making new quiz
    quiz = Quiz("data/exams/CompTIA 1101.json", numOfQuestions);

    // Asking the user questions
    cli.AskQuestions(quiz, numOfQuestions);
}
int gui_version(int argc, char* argv[]){
    // Loading a quiz
    Quiz* quiz = new Quiz("data/exams/CompTIA 1101.json", 5);

    // Creating the window app
    Window::instance = new Window("TestDesk", 770, 525);

    // Creating the GUI
    Tester_GUI::instance = new Tester_GUI(quiz);

    // Finalizing and showing the window after creating GUI elements
    Window::instance->Update();
    Window::instance->Show(argc, argv);

    // Running FLTK
    return Fl::run();
}

// Entry point
int main(int argc, char* argv[]){
    // Getting argument(s)
    std::vector<std::string> args;
    for(unsigned int i = 0; i < argc; i++){
        args.push_back(std::string(argv[i]));
    }

    // Checking the arguments
    if(args[1] == "--help"){
        printf("Usage: TestDesk [OPTIONS]\n");
        printf("OPTIONS: \n");
        printf("\t--help: Displays how to use the program\n");
        printf("\t--cli: Starts program in a Command Line Interface.\n");
        return 0;
    }
    else if(args[1] == "--cli"){
        cli_version();
        return 0;
    }

    // Starting the GUI Version
    return gui_version(argc, argv);
}
