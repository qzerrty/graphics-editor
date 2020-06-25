#pragma once
#include "Interfaces/Tool.hpp"
#include "main/graphicsEditor.hpp"

class ClearInstrument : public Tool {
  Point pos;
public:
  void draw(int,int,SDL_Rect) override;
  void finishDraw(SDL_Rect) override;
};