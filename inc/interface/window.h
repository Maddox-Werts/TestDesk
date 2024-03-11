#ifndef H_WINDOW
#define H_WINDOW

// Includes
#include <QWindow>

// Classes
class Window{
private:
  // Variables
  QWindow* window;

public:
  // Constructors
  Window(const char* title, int w, int h);
};

#endif