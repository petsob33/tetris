#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "grafic.h"
#include <SDL2/SDL_ttf.h>

#define WIDTH 10
#define HEIGHT 20
// for drawing text
void drawText(SDL_Renderer *renderer, int x, int y, const char *text, TTF_Font *font, SDL_Color color)
{

    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
// main render function
void renderArr(int gameArr[20][10], SDL_Renderer *renderer, SDL_Window *window, int nextShape, TTF_Font *font, int score, int highscore[5])
{

    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    int heightStep = (height) / HEIGHT;
    int widthStepSite = (width - (16 * heightStep)) / 2;
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Rect rect;
    rect.w = heightStep;
    rect.h = heightStep;
    // draw game array
    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            int val = gameArr[y][x] % 10;

            rect.x = widthStepSite + x * heightStep;
            rect.y = y * heightStep;
            if (val != 0)
            {

                setColor(renderer, val);

                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
                SDL_RenderDrawRect(renderer, &rect);
            }
            else
            {

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
    // draw next shape preview
    int previewX = (WIDTH * heightStep) + 50 + widthStepSite;
    int previewY = 100;
    char scoreBuffer[20];
    sprintf(scoreBuffer, "Score: %d", score);
    drawText(renderer, previewX, 5, scoreBuffer, font, textColor);
    drawText(renderer, previewX, previewY - 60, "NEXT", font, textColor);
    // draw high scores
    for (int i = 0; i < 5; i++)
    {
        char buf[15];
        sprintf(buf, "%d", highscore[i]);
        drawText(renderer, previewX, 300 + i * 30, buf, font, textColor);
    }

    
    SDL_Rect borderRect = {previewX - 20, previewY - 30, (4 * heightStep) + 20, (4 * heightStep) + 20};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &borderRect);
    // draw next shape
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (shapes[nextShape][y][x] != 0)
            {
                setColor(renderer, nextShape + 1);

                rect.x = previewX + (x * heightStep);
                rect.y = previewY + (y * heightStep);

                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
}
void setColor(SDL_Renderer *renderer, int shape)
{
    switch (shape)
    {
    case 1: // I
        SDL_SetRenderDrawColor(renderer, 0, 188, 212, 255);
        break;
    case 2: // O
        SDL_SetRenderDrawColor(renderer, 255, 235, 59, 255);
        break;
    case 3: // T
        SDL_SetRenderDrawColor(renderer, 156, 39, 176, 255);
        break;
    case 4: // S
        SDL_SetRenderDrawColor(renderer, 76, 175, 80, 255);
        break;
    case 5: // Z
        SDL_SetRenderDrawColor(renderer, 244, 67, 54, 255);
        break;
    case 6: // J
        SDL_SetRenderDrawColor(renderer, 33, 150, 243, 255);
        break;
    case 7: // L
        SDL_SetRenderDrawColor(renderer, 255, 152, 0, 255);
        break;
    default:
        SDL_SetRenderDrawColor(renderer, 96, 125, 139, 255);
        break; // deafult gray-
    }
}