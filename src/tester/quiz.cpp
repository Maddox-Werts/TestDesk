// Includes
#include <tester/quiz.h>

// Constructors
Score::Score(){
  percentage = 0;
  incorrect = 0;
  correct = 0;
}
Quiz::Quiz(const char* quizPath){
  // Load the quiz from path
  std::ifstream file(quizPath);

  // Parsing JSON
  json qData = json::parse(file);

  // Did it work?
  if(qData == nullptr){
    // Exit
    printf("ERROR: Failed to parse JSON.\n");
    exit(EXIT_FAILURE);
  }

  // Getting important data
  this->name = qData["name"];
  this->description = qData["description"];

  // Loading questions
  for(unsigned int i = 0; i < qData["questions"].size(); i++){
    // Current questions
    json lq = qData["questions"][i];

    // Loading responses
    std::vector<std::string> responses;
    for(unsigned int i = 0; i < lq["responses"].size(); i++){
      responses.push_back(lq["responses"][i]);
    }

    // Creating a new question
    Question* nq = new Question(lq["prompt"], responses, lq["correct"]);

    // Adding it into the list
    this->questions.push_back(nq);
  }
}

// Functions
void Quiz::qAnswer(int answer){
  answers.push_back(answer);
}
Question* Quiz::qGet(){
  return this->questions[this->qCurrent];
}
int Quiz::qSize(){
  return this->questions.size();
}

Score Quiz::qScore(){
  // Result
  Score result;

  // Going through all questions
  for(unsigned int i = 0; i < this->questions.size(); i++){
    if(this->questions[i]->correct == this->answers[i]){
      result.correct++;
    }
    else{
      result.incorrect++;
      result.qIncorrect.push_back(this->questions[i]);
      result.aIncorrect.push_back(this->answers[i]);
      result.iIncorrect.push_back(i);
    }
  }

  // Calculate percentage
  float fC = result.correct;
  float fI = result.correct + result.incorrect;
  result.percentage = fC / fI;

  // Return result
  return result;
}