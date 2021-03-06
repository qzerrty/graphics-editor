#pragma once
#include <vector>
#include <istream>
#include "main/graphicsEditor.hpp"
#include "Interfaces/Window.hpp"
#include "ColorInput.hpp"
#include "ChoosenColor.hpp"
#include "TextInput.hpp"

class Palette : public Window {
private:
  std::vector<ColorInput *> colors;
  std::vector<TextInput *> textInputs;
  ChoosenColor* m_choosenColor;

public:
  Palette(int,int,int,int,const style_s *);
  ~Palette();
	bool clicked(SDL_Event *) override;
	bool hovered(SDL_Event *) override;
  void draw(SDL_Surface *) override;
  void addColorInput(int,int,int,int,const style_s *,Uint32,char *,ComponentName);
  void addTextInput(int,int,int,int,const style_s *,char *,std::string,ComponentName);
  void setChoosenColor(int,int,int,int,const style_s *,Uint32,char *,ComponentName);
  ChoosenColor * getChoosenColor();
  TextInput * getTextInput(size_t index);

};