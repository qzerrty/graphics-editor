#pragma once
#include "ChoosenColor.hpp"
#include "Interfaces/Focused.hpp"

class ColorInput : public ChoosenColor, public Focused {
public:
  ColorInput(int,int,int,int,const style_s *,Uint32,char *,ComponentName);
  bool clicked(SDL_Event *);
  void toggleFocusedDraw() override;
  Uint32 getColorValue();
  
};
