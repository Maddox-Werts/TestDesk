#ifndef H_TCLI
#define H_TCLI

// Includes
#include <base.h>
#include <tester/question.h>
#include <tester/quiz.h>

// Classes
class Tester_CLI{
private:
  // Variables

  // Functions

public:
  // Variables

  // Constructor
  Tester_CLI();

  // Functions
  static int Letter2Number(const char* letter);
  void DisplayQuestion(int index, Question* question);
  void DisplayScore(Score score);
};

#endif