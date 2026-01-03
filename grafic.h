#ifndef grafic_h
#define grafic_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> 

void renderArr(int gameArr[20][10], SDL_Renderer *renderer, SDL_Window *window, int nextShape, TTF_Font *font, int score, int highscore[5]);
void drawText(SDL_Renderer *renderer, int x, int y, const char *text, TTF_Font *font, SDL_Color color);
void setColor(SDL_Renderer *renderer, int shape);

extern const int shapes[7][4][4];

#endif