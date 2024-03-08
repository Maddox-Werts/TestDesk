#ifndef H_QUESTION
#define H_QUESTION

// Includes
#include "base.h"

// Classes
class Question{
public:
  // Variables
  std::string prompt;
  std::vector<std::string> responses;
  int correct;

  // Constructor
  Question(std::string prompt, std::vector<std::string> responses, int correct);

  // Functions
};

#endif