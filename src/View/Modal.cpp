#include "../../../libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "Controller/Controller.hpp"
#include "Modal.hpp"
#include "main/graphicsEditor.hpp"
#include <iostream>

Modal::Modal(
  SDL_Surface * screenSurface,
  int w,
  int h,
  const style_s * windowStyle
) : txtInput(nullptr), m_confirm(nullptr) {
  style = windowStyle;
  screen = screenSurface;

  int xcenter = window_width / 2;
  int ycenter = window_height / 2;
  pos.x = xcenter - w / 2;
  pos.y = ycenter - h / 2;
  pos.w = w;
  pos.h = h;

  tmp = SDL_CreateRGBSurface(SDL_HWSURFACE |
    SDL_DOUBLEBUF, window_width, window_height, window_scrdepth,
    screen->format->Rmask, screen->format->Gmask,
    screen->format->Bmask, screen->format->Amask);
}

Modal::~Modal() {
  SDL_FreeSurface(tmp);
  delete txtInput;
  delete m_confirm;
}

SDL_Rect Modal::getBound() {
  return pos;
}

void Modal::draw() {
  SDL_BlitSurface(screen, NULL, tmp, NULL);
  Draw_FillRect(screen, 0, 0, window_width, window_height, backgroundColor);
  Draw_FillRect(screen, 
    (Sint16) (pos.x + style->shadowOffset), 
    (Sint16) (pos.y + pos.h),
    pos.w, style->shadowOffset, 
    style->shadowColor);
  Draw_FillRect(screen,
    (Sint16) (pos.x + pos.w),
    (Sint16) (pos.y + style->shadowOffset),
    style->shadowOffset,
    (Uint16) (pos.h - style->shadowOffset),
    style->shadowColor);
  Draw_FillRect(screen, pos.x, pos.y, pos.w, pos.h, style->color);
  if (txtInput != nullptr) txtInput->draw();
  if (m_confirm != nullptr) m_confirm->draw();
}

void Modal::close() {
  SDL_BlitSurface(tmp, NULL, screen, NULL);
}

bool Modal::clicked(SDL_Event * event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    if (txtInput != nullptr && txtInput->clicked(event)) return true;
    if (m_confirm != nullptr && m_confirm->clicked(event)) return true;
    return true;
	}
  return false;
}

bool Modal::hovered(SDL_Event * event) {
  if (
		pos.x <= event->button.x && pos.x + pos.w >= event->button.x &&
		pos.y <= event->button.y && pos.y + pos.h >= event->button.y
	) {
    if (txtInput != nullptr && txtInput->hovered(event)) return true;
    if (m_confirm != nullptr && m_confirm->hovered(event)) return true;
    Controller::getController()->clearHoveredObj();
    return true;
	}
  return false;
}

void Modal::setInput(int x, int y, int w, int h, char * tooltipTxt, char * holderTxt, ComponentName name) {
  txtInput = new TextInput(screen, pos.x + x, pos.y + y, w, h, &textInputStyle, tooltipTxt, holderTxt, name, false);
}

void Modal::setConfirm(int x, int y, int w, int h) {
  m_confirm = new Confirm(screen, pos.x + x, pos.y + y, w, h, &btnStyle);
}