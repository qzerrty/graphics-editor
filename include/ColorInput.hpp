#pragma once
#include "ChoosenColor.hpp"
#include "Focused.hpp"
#include "Hovered.hpp"

class ColorInput : public ChoosenColor, public Focused {
private:

public:
  ColorInput(SDL_Surface*,int,int,int,int,const Style*,Uint32,char*);
  bool clicked(SDL_Event*);
  void toggleFocusedDraw() override;
  
};
