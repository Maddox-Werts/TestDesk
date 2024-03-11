// Header
#include <interface/window.h>

// Constructor
Window::Window(const char* title, int w, int h){
  // Creating a window
  this->window = new QWindow();

  // Setting window properties
  window->setTitle("TestDesk");
  window->setWidth(w);
  window->setHeight(h);

  // Showing the screen
  window->show();
}