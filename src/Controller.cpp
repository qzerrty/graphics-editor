#include "Controller.hpp"

#include <iostream>

Controller::Controller() {
  hoveredObj = NULL;
  focusedObj = NULL;
  focusedTextInput = NULL;
}

void Controller::changeFocus(Focused* newObj) {
  if (focusedObj != newObj) {
    if (focusedObj != NULL) focusedObj->toggleFocusedDraw();
    focusedObj = newObj;
  } else {
    focusedObj = NULL;
  }
}

bool Controller::changeHover(Hovered* newObj) {
  if (hoveredObj != newObj) {
    if (hoveredObj != NULL) hoveredObj->toggleHoveredDraw();
    hoveredObj = newObj;
    return true;
  }
  return false;
}

void Controller::clearHoveredObj() {
  if (hoveredObj != NULL) {
    hoveredObj->toggleHoveredDraw();
    hoveredObj = NULL;
  }
}

void Controller::focusTextInput(TextInput* newObj) {
  if (focusedTextInput != newObj)
    focusedTextInput = newObj;
  else
    focusedTextInput = NULL;
}

bool Controller::waitingForInput() {
  return focusedTextInput != NULL;
}

void Controller::readInput(SDL_Event* event) {
  SDLKey sym = event->key.keysym.sym;
  int value = std::stoi(focusedTextInput->getValue());

  if (sym == SDLK_BACKSPACE) {
    value /= 10;
  }

  if (sym >= 48 && sym <= 57)
    value = value * 10 + sym - 48;

  switch (focusedTextInput->getValueClass()) {
    case ValueClasses::Line:
      if (value == 0) value = 1;
      if (value > 20) value = 20;
      break;
    case ValueClasses::RGB:
      if (value > 255) value = 255;
      break;
  }
  

  focusedTextInput->changeValue(std::to_string(value));
}


Controller* Controller::m_controller = 0;
