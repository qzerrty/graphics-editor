#include "libs/SDL_draw-1.2.13/include/SDL_draw.h"
#include "Model/DataModel.hpp"
#include "ImageInstrument.hpp"
#include "main/utils.hpp"
#include <unistd.h>
#include <regex>

void ImageInstrument::draw(int x, int y, SDL_Rect bound) {
  updateCanvasScreen(&bound);
  pos.x = x;
  pos.y = y;
  if (
    pos.x >= bound.x && pos.x < bound.w + bound.x &&
    pos.y >= bound.y && pos.y < bound.h + bound.y
  ) {
    std::string fileName = DataModel::getData()->getFilePath();
    std::cmatch m;
    std::regex e (".bmp$");
    if (
      access(fileName.c_str(), F_OK) != -1
      && std::regex_search(fileName.c_str(), m, e)
    ) {
       SDL_Surface * img = SDL_LoadBMP(fileName.c_str());

      SDL_Rect posToPlace = {(Sint16) pos.x, (Sint16) pos.y, (Uint16) img->w, (Uint16) img->h};
      SDL_Rect posFromTake = {0, 0, (Uint16) img->w, (Uint16) img->h};

      if (img->w + pos.x > bound.w + bound.x) {
        posFromTake.w -= img->w + pos.x - bound.w - bound.x;
        posToPlace.w = posFromTake.w;
      }

      if (img->h + pos.y > bound.h + bound.y) {
        posFromTake.h -= img->h + pos.y - bound.h - bound.y;
        posToPlace.h = posFromTake.h;
      }

      SDL_BlitSurface(img, &posFromTake, screen, &posToPlace);
      SDL_Flip(screen);
    }

  }
}

void ImageInstrument::finishDraw(SDL_Rect bound) {
  if (
    pos.x >= bound.x && pos.x < bound.w + bound.x &&
    pos.y >= bound.y && pos.y < bound.h + bound.y
  ) {
    pos.x = 0;
    pos.y = 0;
    updateCanvasSurface(&bound);
  }
}
