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
void Tester_CLI::DisplayQuestion(int index, Question* question){
  // Clear screen
  system("clear");
  
  // Giving the question's prompt
  std::cout << index+1 << ") " << question->prompt << "\n";

  // Spitting out responses
  for(unsigned int i = 0; i < question->responses.size(); i++){
    std::cout << indexes[i] << ") " << question->responses[i] << "\n";
  }
  
  std::cout << "\n";
}
void Tester_CLI::DisplayScore(Score score){
  // Clear screen
  system("clear");

  // Quick Stats
  std::cout << score.correct << " / " << (score.correct + score.incorrect) << "\n";
  std::cout << score.percentage << "\n";
  std::cout << "\n";
  std::cout << "You missed " << score.incorrect << " questions.\n";
  std::cout << "\n";

  // Showing wrong answers
  for(unsigned int i = 0; i < score.incorrect; i++){
    std::cout << score.iIncorrect[i] << ") " << score.qIncorrect[i]->prompt << "\n";
    std::cout << "You said: " << score.qIncorrect[i]->responses[score.aIncorrect[i]] << "\n";
    std::cout << "\n";
    std::cout << "Correct answer: " << score.qIncorrect[i]->responses[score.qIncorrect[i]->correct] << "\n";
    std::cout << "\n";
  }
}