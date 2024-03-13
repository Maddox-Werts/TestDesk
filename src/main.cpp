// Includes
#include <base.h>
#include <tester/quiz.h>
#include <interface/cli.h>
#include <interface/gui.h>

// Variables
std::string quizPath = "data/exams/";
int numOfQuestions = 15;

// Functions
void cli_version(){
    // Loading a new test
    Quiz quiz = Quiz(quizPath.c_str(), numOfQuestions);

    // Init application
    Tester_CLI cli;

    // Asking the user questions
    cli.AskQuestions(quiz, numOfQuestions);
}
int gui_version(int argc, char* argv[]){
    // Loading a quiz
    Quiz* quiz = new Quiz(quizPath.c_str(), numOfQuestions);

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
        printf("\t-t: Sets the test you want to use (ex: CompTIA 1101)\n");
        printf("\t-q: Sets the amount of questions to be quizzed on (random)\n");
        printf("\t--help: Displays how to use the program\n");
        printf("\t--cli: Starts program in a Command Line Interface.\n");
        return 0;
    }
    
    // Getting typed arguments
    for(unsigned i = 0; i < argc; i++){
        // Converting the char array into a string
        std::string arg_string = std::string(argv[i]);
        
        // What do we want?
        if(arg_string == "--cli"){
            cli_version();
            return 0;
        }
        if(arg_string == "-q"){
            numOfQuestions = std::stoi(argv[i+1]);
            i++;
        }
        if(arg_string == "-t"){
            quizPath += argv[i+1];
            quizPath += ".json";
            i++;
        }
    }

    // Starting the GUI Version
    return gui_version(argc, argv);
}
