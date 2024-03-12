// Header
#include <interface/gui.h>

// Functions
void onBTNclick(Fl_Widget*, void* data){
  // Getting info from data
  std::vector<Fl_Radio_Round_Button*> *buttons = (std::vector<Fl_Radio_Round_Button*> *)data;

  // Going through buttons
  for(unsigned int i = 0; i < buttons->size(); i++){
    if(buttons->at(i)->value()){
      // Printing that we answered
      printf("Answered: %i\n", i);
    }
  }
}

// Variables
Fl_Window* Window::getWindow(){
  return window;
}
Quiz* Tester_GUI::getQuiz(){
  return quiz;
}

// Constructors
Window::Window(const char* title, int w, int h){
  // Creating a window
  this->window = new Fl_Window(w, h, title);
}

Tester_GUI::Tester_GUI(Quiz* quiz){
  // Setting Quiz pointer
  this->quiz = quiz;

  // Adding a exam title
  this->g_exam_title = new Fl_Box(10, 10, 5, 30, quiz->name.c_str());
  this->g_exam_title->align(FL_ALIGN_RIGHT);
  this->g_exam_title->labelsize(24);

  // Adding next button
  this->g_exam_next = new Fl_Button(700, 485, 60, 30);
  this->g_exam_next->labeltype(FL_NORMAL_LABEL);
  this->g_exam_next->label("Next");
  this->g_exam_next->box(FL_UP_BOX);

  // Adding back button
  this->g_exam_back = new Fl_Button(635, 485, 60, 30);
  this->g_exam_back->labeltype(FL_NORMAL_LABEL);
  this->g_exam_back->label("Back");
  this->g_exam_back->box(FL_UP_BOX);

  // Update to the current question
  updateQuestion();
}

// Functions
void Window::Update(){
  this->window->end();
}
void Window::Show(int argc, char* argv[]){
  this->window->show(argc, argv);
}

void Tester_GUI::updateQuestion(){
  // Adding a exam question
  this->g_exam_question = new Fl_Box(20, 45, 730, 85, quiz->qGet()->prompt.c_str());
  this->g_exam_question->align(FL_ALIGN_LEFT|FL_ALIGN_CLIP|FL_ALIGN_WRAP|FL_ALIGN_INSIDE);
  this->g_exam_question->labelsize(14);

  // Adding buttons for each question response
  for(unsigned int i = 0; i < quiz->qGet()->responses.size(); i++){
    Fl_Radio_Round_Button* nRB = new Fl_Radio_Round_Button(45, 145+(i*30), 15, 15);

    nRB->labeltype(FL_NORMAL_LABEL);
    nRB->label(quiz->qGet()->responses[i].c_str());

    nRB->box(FL_NO_BOX);
    nRB->down_box(FL_ROUND_DOWN_BOX);
    nRB->align(FL_ALIGN_RIGHT);

    this->questionButtons.push_back(nRB);
  }

  // Callback data
  CallbackData data;
  data.buttons = &this->questionButtons;
  data.gui = this;

  // Next Callback
  this->g_exam_next->callback(onBTNclick, (void*)&this->questionButtons);
}