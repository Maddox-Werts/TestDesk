#ifndef H_QUIZ
#define H_QUIZ

// Includes
#include <base.h>
#include "question.h"

// Classes
class Score{
public:
  // Variables
  float percentage;
  int incorrect;
  int correct;

  std::vector<Question*> qIncorrect;
  std::vector<int> aIncorrect;
  std::vector<int> iIncorrect;

  // Constructor
  Score();
};

class Quiz{
private:
  // Variables
  std::vector<Question*> questions;
  std::vector<int> answers;

public:
  // Variables
  std::string name;
  std::string description;
  int qCurrent;

  // Constructors
  Quiz(const char* quizPath, int wantedQuestions);

  // Functions
  void qAnswer(int answer);
  Question* qGet();
  int qSize();

  Score qScore();
};

#endif