// Includes
#include <base.h>
#include <tester/quiz.h>
#include <interface/cli.h>
#include <interface/gui_fltk.h>

// Variables
std::string quizPath = "data/exams/";
int numOfQuestions = 15;
int flagsSet = 0;

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
    // Creating the window app
    Window_GUI::instance = new Window_GUI("TestDesk", 770, 525);

    if(flagsSet >= 2){
        // Loading a quiz
        Quiz* quiz = new Quiz(quizPath.c_str(), numOfQuestions);

        // Creating the GUI
        Tester_GUI::instance = new Tester_GUI(quiz);
    }
    else{
        Hub_GUI::instance = new Hub_GUI();
    }

    // Finalizing and showing the window after creating GUI elements
    Window_GUI::instance->Update();
    Window_GUI::instance->Show(argc, argv);

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
    if(argc > 1){
        if(args[1] == "--help"){
            printf("Usage: TestDesk [OPTIONS]\n");
            printf("OPTIONS: \n");
            printf("\t-t: Sets the test you want to use (ex: CompTIA 1101)\n");
            printf("\t-q: Sets the amount of questions to be quizzed on (random)\n");
            printf("\t--help: Displays how to use the program\n");
            printf("\t--cli: Starts program in a Command Line Interface.\n");
            return 0;
        }
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
            flagsSet++;
        }
        if(arg_string == "-t"){
            quizPath += argv[i+1];
            quizPath += ".json";
            i++;
            flagsSet++;
        }
    }

    // Starting the GUI Version
    return gui_version(argc, argv);
}
