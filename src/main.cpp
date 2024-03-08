// Includes
#include <base.h>
#include <tester/quiz.h>
#include <interface/cli.h>

// Functions

// Entry point
int main(int argc, char* argv[]){
    // Loading a new test
    Quiz quiz = Quiz("data/exams/CompTIA 1101.json");

    // Init application
    Tester_CLI cli;

    // Quiz Header
    std::cout << quiz.name << "\n";
    std::cout << quiz.description << "\n";
    std::cout << quiz.qSize() << " Possible Questions.\n";
    std::cout << "\n";

    // Displaying questions
    quiz.qCurrent = 0;
    for(unsigned int i = 0; i < quiz.qSize(); i++){
        cli.DisplayQuestion(quiz.qCurrent, quiz.name, quiz.qGet());

        std::string typed;
        std::cout << "Answer: ";
        std::cin >> typed;

        quiz.qAnswer(Tester_CLI::Letter2Number(typed.c_str()));
        quiz.qCurrent++;
    }

    // Showing results
    cli.DisplayScore(quiz.qScore(), quiz.name);

    // Exit
    return 0;
}
