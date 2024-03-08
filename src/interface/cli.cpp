// Header
#include <interface/cli.h>

// Constants
std::vector<std::string> indexes = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q"};


// Constructors
Tester_CLI::Tester_CLI(){
  /*
    INIT CLI (Command Line Interface)
  */

  // Clearing the screen
  system("clear");
}

// Functions
int Tester_CLI::Letter2Number(const char* letter){
  for(unsigned int i = 0; i < indexes.size(); i++){
    if(indexes[i] == letter){
      return i;
    }
  }
  return -1;
}
void Tester_CLI::DisplayQuestion(int index, std::string title, Question* question){
  // Clear screen
  system("clear");

  // Test title
  std::cout << "-- " << title << " --" << "\n";
  std::cout << "\n";
  
  // Giving the question's prompt
  std::cout << index+1 << ") " << question->prompt << "\n";
  std::cout << "\n";

  // Spitting out responses
  for(unsigned int i = 0; i < question->responses.size(); i++){
    std::cout << indexes[i] << ") " << question->responses[i] << "\n";
  }
  
  std::cout << "\n";
}
void Tester_CLI::DisplayScore(Score score, std::string title){
  // Clear screen
  system("clear");

  // Test title
  std::cout << "-- " << title << " --" << "\n";

  // Quick Stats
  std::cout << "\n";
  std::cout << "- Summary -" << "\n";
  std::cout << "\tGrade: " << score.percentage << "%\n";
  std::cout << "\tCorrect: " << score.correct << " / " << (score.correct + score.incorrect) << "\n";
  if(score.incorrect) {std::cout << "\t" << "You missed " << score.incorrect << " questions.\n";}
  std::cout << "\n";

  // Did we miss any?
  if(score.incorrect <= 0){
    std::cout << "\n";
    return;
  }

  // Showing wrong answers
  std::cout << "\n";
  std::cout << "- Missed Questions -" << "\n";
  for(unsigned int i = 0; i < score.incorrect; i++){
    std::cout << score.iIncorrect[i] + 1 << ") " << score.qIncorrect[i]->prompt << "\n";
    std::cout << "\n";
    std::cout << "You said: \t\t" << score.qIncorrect[i]->responses[score.aIncorrect[i]] << "\n";
    std::cout << "Correct answer: \t" << score.qIncorrect[i]->responses[score.qIncorrect[i]->correct] << "\n";
    std::cout << "\n";
  }
}