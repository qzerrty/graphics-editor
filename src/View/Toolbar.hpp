#pragma once
#include <vector>
#include "Interfaces/Window.hpp"
#include "Button.hpp"
#include "TextInput.hpp"

class Toolbar : public Window {
private:
  std::vector<Button *> btns;
	std::vector<TextInput *> textInputs;

public:
  Toolbar(int,int,int,int,const style_s *);
  ~Toolbar();
  void addButton(int,int,int,int,const style_s *,char *,char *,ComponentName,bool=true,bool=true);
	void addTextInput(int,int,int,int,const style_s *,char *,std::string,ComponentName);
  void addSaveButton(int,int,int,int,const style_s *);
	bool clicked(SDL_Event *) override;
	bool hovered(SDL_Event *) override;
	void draw(SDL_Surface *) override;
	
};