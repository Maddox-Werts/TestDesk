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
void btnHStart(Fl_Widget*, void* data){
  // Cast
  HubData* hData = (HubData*)data;

  // Getting values
  const char* quizName = hData->name->value();
  int quizAmount = (int)(floor(hData->questions->value()));

  if(quizAmount > 0){
    // Loading a quiz
    Quiz* quiz = new Quiz(("data/exams/" + std::string(quizName) + ".json").c_str(), quizAmount);

    // Cleanup
    Hub_GUI::instance->Clean();

    // Creating the GUI
    Tester_GUI::instance = new Tester_GUI(quiz);

    // Redrawing the window
    Window_GUI::instance->getWindow()->redraw();
  }
}

std::vector<std::string> split(std::string line, char delimeter){
  std::vector<std::string> splits;
  std::string temp;
  for(unsigned int i = 0; i < line.size(); i++){
    if(line[i] == delimeter){
      splits.push_back(temp);
      temp = "";
    }
    else{
      temp += line[i];
    }
  }
  splits.push_back(temp);
  return splits;
}

// Statics
Window_GUI* Window_GUI::instance;
Hub_GUI* Hub_GUI::instance;
Tester_GUI* Tester_GUI::instance;

// Variables
Fl_Window* Window_GUI::getWindow(){
  return window;
}

// Constructors
Window_GUI::Window_GUI(const char* title, int w, int h){
  // Creating a window
  this->window = new Fl_Window(w, h, title);
}
Hub_GUI::Hub_GUI(){
  // Title
  this->title = new Fl_Box(205, 35, 335, 50, "TestDesk");
  title->labelsize(42);

  // Subtitle
  this->subtitle = new Fl_Box(275, 80, 200, 25, "The simple study assistant.");
  subtitle->labelsize(14);

  // Credits
  this->credits = new Fl_Box(0, 505, 255, 20, "Created by OBJNULL (Maddox Werts)");
  credits->labelsize(14);

  // Quiz Name
  this->quizName = new Fl_Input_Choice(285, 227, 180, 28, "Quiz Name");

  // Getting quiz questions
  std::vector<std::string> quizzes = getQuizzes();
  for(unsigned int i = 0; i < quizzes.size(); i++){
    char* bytes = new char[quizzes[i].length() + 1];
    strcpy(bytes, quizzes[i].c_str());

    quizName->add(bytes);
  }
  
  // Question amounts
  this->numQuestions = new Fl_Value_Input(285, 257, 180, 28, "Questions");

  // Start button
  this->start = new Fl_Button(310, 290, 120, 30, "Start");

  HubData* data = new HubData{quizName, numQuestions};

  start->callback(btnHStart, (void*)data);
}
Tester_GUI::Tester_GUI(Quiz* quiz){
  // Setting Quiz pointer
  this->quiz = quiz;
  this->quiz->qCurrent = 0;

  // Update to the current question
  Instantiate();
}

// Functions
void Window_GUI::Update(){
  this->window->end();
}

void Window_GUI::Show(int argc, char* argv[]){
  this->window->show(argc, argv);
}

std::vector<std::string> Hub_GUI::getQuizzes(){
  // Result object
  std::vector<std::string> result;

  // Going through exams
  for (const auto& entry : std::filesystem::recursive_directory_iterator("data/exams/")) {
    if (std::filesystem::is_regular_file(entry)) {
      // Getting the file name
      std::string line = std::string(entry.path().string());
      std::string strippedName = split(split(line, '/')[2], '.')[0];

      if(strippedName != ""){
        std::cout << strippedName << "\n";
        result.push_back(strippedName);
      }
    }
  }

  // Return Result
  return result;
}
void Hub_GUI::Clean(){
  Window_GUI::instance->getWindow()->remove(this->title);
  Window_GUI::instance->getWindow()->remove(this->subtitle);
  Window_GUI::instance->getWindow()->remove(this->credits);
  Window_GUI::instance->getWindow()->remove(this->quizName);
  Window_GUI::instance->getWindow()->remove(this->numQuestions);
  Window_GUI::instance->getWindow()->remove(this->start);
  Window_GUI::instance->getWindow()->redraw();
}

void Tester_GUI::Instantiate(){
  // Progress
  this->g_exam_progress = new Fl_Box(760, 5, 13, 20);
  this->g_exam_progress->align(FL_ALIGN_LEFT);

  std::string progressText = "Question " + std::to_string(this->quiz->qCurrent+1) + " / " + std::to_string(this->quiz->qSize());
  char* progressFinal = new char[progressText.length() + 1];
  strcpy(progressFinal, progressText.c_str());

  this->g_exam_progress->label(progressFinal);
  Window_GUI::instance->getWindow()->add(this->g_exam_progress);

  // Title
  std::string promptText = this->quiz->qGet()->prompt;
  char* promptFinal = new char[promptText.length() + 1];
  strcpy(promptFinal, promptText.c_str());

  // Adding a exam question
  this->g_exam_question = new Fl_Box(20, 45, 730, 85, promptFinal);
  this->g_exam_question->align(FL_ALIGN_LEFT|FL_ALIGN_CLIP|FL_ALIGN_WRAP|FL_ALIGN_INSIDE);
  this->g_exam_question->labelsize(14);
  Window_GUI::instance->getWindow()->add(this->g_exam_question);

  // Adding a exam title
  this->g_exam_title = new Fl_Box(10, 10, 5, 30, this->quiz->name.c_str());
  this->g_exam_title->align(FL_ALIGN_RIGHT);
  this->g_exam_title->labelsize(24);
  Window_GUI::instance->getWindow()->add(this->g_exam_title);

  // Adding next button
  this->g_exam_next = new Fl_Button(700, 485, 60, 30);
  this->g_exam_next->labeltype(FL_NORMAL_LABEL);
  this->g_exam_next->label("Next");
  this->g_exam_next->box(FL_UP_BOX);
  Window_GUI::instance->getWindow()->add(this->g_exam_next);

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
    Window_GUI::instance->getWindow()->add(nRB);
  }

  // Next Callback
  this->g_exam_next->callback(btnNext, (void*)&this->questionButtons);
}
void Tester_GUI::Populate(){
  // Progress
  std::string progressText = "Question " + std::to_string(this->quiz->qCurrent+1) + " / " + std::to_string(this->quiz->qSize());
  char* progressFinal = new char[progressText.length() + 1];
  strcpy(progressFinal, progressText.c_str());

  this->g_exam_progress->label(progressFinal);

  // Title
  std::string promptText = std::to_string(this->quiz->qCurrent+1) +") " + this->quiz->qGet()->prompt;
  char* promptFinal = new char[promptText.length() + 1];
  strcpy(promptFinal, promptText.c_str());

  // Setting the question title
  this->g_exam_question->label(promptFinal);

  // Clearing the existing answers
  for(unsigned int i = 0; i < questionButtons.size(); i++){
    Window_GUI::instance->getWindow()->remove(questionButtons[i]);
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
    Window_GUI::instance->getWindow()->add(nRB);
  }

  // After Adding more elements
  Window_GUI::instance->getWindow()->redraw();
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
  Window_GUI::instance->getWindow()->remove(g_exam_question);
  Window_GUI::instance->getWindow()->remove(g_exam_next);
  Window_GUI::instance->getWindow()->remove(g_exam_back);
  for(unsigned int i = 0; i < this->questionButtons.size(); i++){
    Window_GUI::instance->getWindow()->remove(questionButtons[i]);
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
    Window_GUI::instance->getWindow()->add(title);

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
    Window_GUI::instance->getWindow()->add(qRatio);
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
      Window_GUI::instance->getWindow()->add(missedQuestions);

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
      Window_GUI::instance->getWindow()->add(next);

      // Next
      Fl_Button* back = new Fl_Button(595, 485, 80, 30, "Back");
      back->callback(btnGBack);
      Window_GUI::instance->getWindow()->add(back);
    }
  }

  // Adding quit button
  Fl_Button* quit = new Fl_Button(10, 485, 80, 30, "Quit");
  quit->callback(btnQuit);
  Window_GUI::instance->getWindow()->add(quit);

  // Redraw
  Window_GUI::instance->getWindow()->redraw();
}