// Header
#include <tester/question.h>

Question::Question(std::string prompt, std::vector<std::string> responses, int correct){
  // Getting the JSON stuff
  this->prompt = prompt;
  this->responses = responses;
  this->correct = correct;
}