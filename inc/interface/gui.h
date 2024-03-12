#ifndef H_GUI
#define H_GUI

// Includes
#include <base.h>
#include <tester/question.h>
#include <tester/quiz.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Radio_Button.H>
#include <FL/Fl_Radio_Round_Button.H>
#include <FL/Fl_Button.H>

// Classes
class Window{
private:
  // Variables
  Fl_Window* window;

public:
  // Variables
  Fl_Window* getWindow();

  // Constructors
  Window(const char* title, int w, int h);

  // Functions
  void Update();
  void Show(int argc, char* argv[]);
};

class Tester_GUI{
private:
  // Variables
  Quiz* quiz;

  Fl_Button* g_exam_next;
  Fl_Button* g_exam_back;

  Fl_Box* g_exam_title;
  Fl_Box* g_exam_question;
  std::vector<Fl_Radio_Round_Button*> questionButtons;

  // Functions

public:
  // Variables
  Quiz* getQuiz();
  int sResponse;

  // Constructors
  Tester_GUI(Quiz* quiz);

  // Functions
  void updateQuestion();
};

#endif