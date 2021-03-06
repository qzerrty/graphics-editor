#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "graphicsEditor.hpp"
#include "utils.hpp"

SDL_Color translate_color(Uint32 int_color) {
	#if SDL_BYTEORDER != SDL_BIG_ENDIAN
		SDL_Color color={
			(Uint8) ((int_color & 0x00ff0000)/0x10000),
			(Uint8) ((int_color & 0x0000ff00)/0x100),
			(Uint8) (int_color & 0x000000ff), 0};
	#else
		SDL_Color color={
			(Uint8) (int_color & 0x000000ff),
			(Uint8) ((int_color & 0x0000ff00)/0x100),
			(Uint8) ((int_color & 0x00ff0000)/0x10000), 0};
	#endif
	return color;
}

void renderText(SDL_Surface* screen, SDL_Rect dst, const char* message, int fontSize, Uint32 color) {
  SDL_Surface* textSurface;
	TTF_Font* fnt;

  if (!(fnt = TTF_OpenFont("../public/Ubuntu.ttf", fontSize))) {
    return;
	}
	if ((textSurface = TTF_RenderUTF8_Blended(fnt, message, translate_color(color)))) {
		SDL_BlitSurface(textSurface, NULL, screen, &dst);
		SDL_FreeSurface(textSurface);
		textSurface = NULL;
	}

  TTF_CloseFont(fnt);
}

char* IntToHexChars(int value) {
	char* result = new char[7];
	sprintf(result, "#%06X", value);
	return result;
}

char* IntToChars(int value) {
	char* result = new char[3];
	sprintf(result, "%d", value);
	return result;
}

Uint32 createRGB(int r, int g, int b) {  
  return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

Uint32 getpixel(SDL_Surface * surface, int x, int y) {
  int bpp = surface->format->BytesPerPixel;
  Uint8 * p = (Uint8 *) surface->pixels + y * surface->pitch + x * bpp;

  switch (bpp) {
    case 1:
      return *p;
    case 2:
      return *(Uint16 *) p;
    case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return p[0] << 16 | p[1] << 8 | p[2];
      else
        return p[0] | p[1] << 8 | p[2] << 16;
    case 4:
      return *(Uint32 *) p;
    default:
      return 0;
  }
}