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

      // Answering the question
      Tester_GUI::instance->quiz->qAnswer(i);
      Tester_GUI::instance->quiz->qCurrent++;

      // Do we have more questions?
      if(Tester_GUI::instance->quiz->qCurrent < Tester_GUI::instance->quiz->qSize()){
        // Updating the question board
        Tester_GUI::instance->Populate();
      }
      else{
        // Ending exam
        Tester_GUI::instance->EndTest();
      }
    }
  }
}

// Statics
Window* Window::instance;
Tester_GUI* Tester_GUI::instance;

// Variables
Fl_Window* Window::getWindow(){
  return window;
}

// Constructors
Window::Window(const char* title, int w, int h){
  // Creating a window
  this->window = new Fl_Window(w, h, title);
}
Tester_GUI::Tester_GUI(Quiz* quiz){
  // Setting Quiz pointer
  this->quiz = quiz;
  this->quiz->qCurrent = 0;

  // Update to the current question
  Instantiate();
}

// Functions
void Window::Update(){
  this->window->end();
}

void Window::Show(int argc, char* argv[]){
  this->window->show(argc, argv);
}

void Tester_GUI::Instantiate(){
  // Adding a exam question
  this->g_exam_question = new Fl_Box(20, 45, 730, 85, this->quiz->qGet()->prompt.c_str());
  this->g_exam_question->align(FL_ALIGN_LEFT|FL_ALIGN_CLIP|FL_ALIGN_WRAP|FL_ALIGN_INSIDE);
  this->g_exam_question->labelsize(14);

  // Adding a exam title
  this->g_exam_title = new Fl_Box(10, 10, 5, 30, this->quiz->name.c_str());
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

  // Adding buttons for each question response
  for(unsigned int i = 0; i < this->quiz->qGet()->responses.size(); i++){
    std::string qResponse = this->quiz->qGet()->responses[i];
    
    Fl_Radio_Round_Button* nRB = new Fl_Radio_Round_Button(45, 145+(i*40), 700, 25);

    nRB->labeltype(FL_NORMAL_LABEL);
    nRB->label(this->quiz->qGet()->responses[i].c_str());

    nRB->box(FL_NO_BOX);
    nRB->down_box(FL_ROUND_DOWN_BOX);
    nRB->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE|FL_ALIGN_WRAP|FL_ALIGN_CLIP);

    this->questionButtons.push_back(nRB);
  }

  // Next Callback
  this->g_exam_next->callback(onBTNclick, (void*)&this->questionButtons);
}
void Tester_GUI::Populate(){
  // Setting the question title
  this->g_exam_question->label(this->quiz->qGet()->prompt.c_str());

  // Clearing the existing answers
  for(unsigned int i = 0; i < questionButtons.size(); i++){
    Window::instance->getWindow()->remove(questionButtons[i]);
    delete questionButtons[i];
  }

  // Clearing array
  this->questionButtons.clear();

  // Adding new question buttons
  for(unsigned int i = 0; i < this->quiz->qGet()->responses.size(); i++){
    std::string qResponse = this->quiz->qGet()->responses[i];
    
    Fl_Radio_Round_Button* nRB = new Fl_Radio_Round_Button(45, 145+(i*40), 700, 40);

    nRB->labeltype(FL_NORMAL_LABEL);
    nRB->label(this->quiz->qGet()->responses[i].c_str());

    nRB->box(FL_NO_BOX);
    nRB->down_box(FL_ROUND_DOWN_BOX);
    nRB->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE|FL_ALIGN_WRAP|FL_ALIGN_CLIP);

    this->questionButtons.push_back(nRB);
    Window::instance->getWindow()->add(nRB);
  }

  // After Adding more elements
  Window::instance->getWindow()->redraw();
}

void Tester_GUI::EndTest(){
  // DEBUG
  printf("Your exam has ended.\n");

  // Clearing current screen
  Window::instance->getWindow()->remove(g_exam_question);
  Window::instance->getWindow()->remove(g_exam_next);
  Window::instance->getWindow()->remove(g_exam_back);
  for(unsigned int i = 0; i < this->questionButtons.size(); i++){
    Window::instance->getWindow()->remove(questionButtons[i]);
  }
  
  // Scoring the test
  Score score = Tester_GUI::instance->quiz->qScore();

  // Adding new elements
  Fl_Box* title = new Fl_Box(240, 100, 215, 30);
  title->labeltype(FL_NORMAL_LABEL);
  title->labelsize(24);

  // Adding percentage in a weird way
  if(score.percentage < 75){
    title->label("Failed Test.");
  }
  else{
    title->label("Passed Test.");
  }

  Window::instance->getWindow()->add(title);

  // Redraw
  Window::instance->getWindow()->redraw();
}