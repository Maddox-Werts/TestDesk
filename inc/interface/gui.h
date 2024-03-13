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
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Value_Input.H>

// Structures
typedef struct MissedQuestion{
  // Variables
  char* title;
  char* prompt;
  char* user;
  char* correct;
} MissedQuestion;
typedef struct HubData{
  Fl_Input* name;
  Fl_Value_Input* questions;
} HubData;

// Classes
class Window{
private:
  // Variables
  Fl_Window* window;

public:
  // Variables
  static Window* instance;
  Fl_Window* getWindow();

  // Constructors
  Window(const char* title, int w, int h);

  // Functions
  void Update();
  void Show(int argc, char* argv[]);
};

class Hub_GUI{
private:
  // Variables
  Fl_Box* title;
  Fl_Box* subtitle;
  Fl_Box* credits;
  Fl_Input* quizName;
  Fl_Value_Input* numQuestions;
  Fl_Button* start;

  // Functions
public:
  // Variables
  static Hub_GUI* instance;

  // Constructors
  Hub_GUI();

  // Functions
  void Clean();
};
class Tester_GUI{
private:
  // Variables
  Fl_Button* g_exam_next;
  Fl_Button* g_exam_back;
  Fl_Box* g_exam_title;
  Fl_Box* g_exam_question;
  std::vector<Fl_Radio_Round_Button*> questionButtons;

  std::vector<MissedQuestion> mQuestions;
  Fl_Group* g_grade_header;
  Fl_Box* g_grade_prompt;
  Fl_Box* g_grade_user;
  Fl_Box* g_grade_correct;
  int gCurrent, gMax;

  // Functions

public:
  // Variables
  static Tester_GUI* instance;

  Quiz* quiz;
  int sResponse;

  // Constructors
  Tester_GUI(Quiz* quiz);

  // Functions
  void Instantiate();
  void Populate();

  void gPopulate();
  void gNav(int dir);

  void LastQuestion();
  void EndTest();
};

#endif