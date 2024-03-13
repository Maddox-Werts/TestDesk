// Header
#include <interface/gui.h>

// Functions
void btnNext(Fl_Widget*, void* data){
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

      if(Tester_GUI::instance->quiz->qCurrent == Tester_GUI::instance->quiz->qSize() - 1){
        Tester_GUI::instance->LastQuestion();
      }

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
void btnQuit(Fl_Widget*, void* data){
  exit(EXIT_SUCCESS);
}
void btnGNext(Fl_Widget*, void* data){
  Tester_GUI::instance->gNav(1);
  Tester_GUI::instance->gPopulate();
}
void btnGBack(Fl_Widget*, void* data){
  Tester_GUI::instance->gNav(-1);
  Tester_GUI::instance->gPopulate();
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
  this->g_exam_next->callback(btnNext, (void*)&this->questionButtons);
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

void Tester_GUI::gPopulate(){
  this->g_grade_header->label(mQuestions[gCurrent].title);
  this->g_grade_prompt->label(mQuestions[gCurrent].prompt);
  this->g_grade_user->label(mQuestions[gCurrent].user);
  this->g_grade_correct->label(mQuestions[gCurrent].correct);
}
void Tester_GUI::gNav(int dir){
  this->gCurrent += dir;
  if(this->gCurrent > gMax - 1){
    this->gCurrent = 0;
  }
  else if(this->gCurrent < 0){
    this->gCurrent = gMax - 1;
  }
}

void Tester_GUI::LastQuestion(){
  printf("LAST QUESTION\n");
  this->g_exam_next->label("Submit");
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

  // Adding the top section
  if(true){
    // Adding new elements
    Fl_Box* title = new Fl_Box(270, 100, 215, 30);
    title->labeltype(FL_NORMAL_LABEL);
    title->labelsize(24);

    // Adding percentage in a weird way
    std::string qTitleText = "";

    if(score.percentage < 75){
      qTitleText += "Failed";
    }
    else{
      qTitleText += "Passed";
    }

    qTitleText += " (";

    std::string percent_raw = std::to_string(score.percentage);
    qTitleText += percent_raw.substr(0, percent_raw.length() - 4);

    qTitleText += "%)";

    char* qTitleFinal = new char[qTitleText.length() + 1];
    strcpy(qTitleFinal, qTitleText.c_str());

    title->label(qTitleFinal);
    Window::instance->getWindow()->add(title);

    // The questions you got right and wrong
    Fl_Box* qRatio = new Fl_Box(270, 130, 215, 30);
    qRatio->labeltype(FL_NORMAL_LABEL);
    qRatio->labelsize(16);

    std::string qRatioText = "";
    qRatioText += std::string(std::to_string(score.correct));
    qRatioText += " / ";
    qRatioText += std::to_string(score.correct + score.incorrect);

    char* qRatioFinal = new char[qRatioText.length() + 1];
    strcpy(qRatioFinal, qRatioText.c_str());

    qRatio->label(qRatioFinal);
    Window::instance->getWindow()->add(qRatio);
  }

  // Adding the missed answers section
  if(true){
    // FUNCTION
    gMax = score.qIncorrect.size();

    mQuestions.clear();
    for(unsigned int i = 0; i < gMax; i++){
      // Title
      std::string titleText = "Question ";
      titleText += std::to_string(score.iIncorrect[i]+1);
      char* titleFinal = new char[titleText.length() + 1];
      strcpy(titleFinal, titleText.c_str());

      // Prompt
      std::string promptText = score.qIncorrect[i]->prompt;
      char* promptFinal = new char[promptText.length() + 1];
      strcpy(promptFinal, promptText.c_str());

      // You Said
      std::string mYouSaidText = "You Said: ";
      mYouSaidText += score.qIncorrect[i]->responses[score.aIncorrect[i]];
      char* mYouSaidFinal = new char[mYouSaidText.length() + 1];
      strcpy(mYouSaidFinal, mYouSaidText.c_str());

      // Correct
      std::string mCorrectText = "Correct: ";
      mCorrectText += score.qIncorrect[i]->responses[score.qIncorrect[i]->correct];
      char* mCorrectFinal = new char[mCorrectText.length() + 1];
      strcpy(mCorrectFinal, mCorrectText.c_str());

      // New missed question
      MissedQuestion mq = MissedQuestion();
      mq.title = titleFinal;
      mq.prompt = promptFinal;
      mq.user = mYouSaidFinal;
      mq.correct = mCorrectFinal;

      // Pushing back final result
      mQuestions.push_back(mq);
    }

    // UI
    if(mQuestions.size() > 0){
      Fl_Group* missedQuestions = new Fl_Group(10, 200, 750, 280);
      missedQuestions->labelsize(19);
      missedQuestions->label("Missed Questions");
      Window::instance->getWindow()->add(missedQuestions);

      // Going through all missed questions
      this->g_grade_header = new Fl_Group(20, 225, 730, 150);
      this->g_grade_header->labelsize(14);
      this->g_grade_header->label(mQuestions[0].title);
      missedQuestions->add(this->g_grade_header);

      // Question prompt
      this->g_grade_prompt = new Fl_Box(25, 230, 710, 100);
      this->g_grade_prompt->align(FL_ALIGN_CLIP|FL_ALIGN_WRAP|FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
      this->g_grade_prompt->labelsize(14);
      this->g_grade_prompt->label(mQuestions[0].prompt);
      this->g_grade_header->add(this->g_grade_prompt);

      // You said
      this->g_grade_user = new Fl_Box(40, 330, 5, 20);
      this->g_grade_user->align(FL_ALIGN_RIGHT);
      this->g_grade_user->labelsize(14);
      this->g_grade_user->label(mQuestions[0].user);
      this->g_grade_header->add(this->g_grade_user);

      // Correct
      this->g_grade_correct = new Fl_Box(40, 350, 5, 20);
      this->g_grade_correct->align(FL_ALIGN_RIGHT);
      this->g_grade_correct->labelsize(14);
      this->g_grade_correct->label(mQuestions[0].correct);
      this->g_grade_header->add(this->g_grade_correct);

      // Next
      Fl_Button* next = new Fl_Button(680, 485, 80, 30, "Next");
      next->callback(btnGNext);
      Window::instance->getWindow()->add(next);

      // Next
      Fl_Button* back = new Fl_Button(595, 485, 80, 30, "Back");
      back->callback(btnGBack);
      Window::instance->getWindow()->add(back);
    }
  }

  // Adding quit button
  Fl_Button* quit = new Fl_Button(10, 485, 80, 30, "Quit");
  quit->callback(btnQuit);
  Window::instance->getWindow()->add(quit);

  // Redraw
  Window::instance->getWindow()->redraw();
}