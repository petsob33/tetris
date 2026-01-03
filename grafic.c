#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "grafic.h"
#include <SDL2/SDL_ttf.h>

#define WIDTH 10
#define HEIGHT 20

void drawText(SDL_Renderer *renderer, int x, int y, const char *text, TTF_Font *font, SDL_Color color)
{

    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    if (!surface)
    {
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void renderArr(int gameArr[20][10], SDL_Renderer *renderer, SDL_Window *window, int nextShape, TTF_Font *font, int score, int highscore[5])
{

    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    int widthStep = (width - 250) / WIDTH;
    int heightStep = (height - 100) / HEIGHT;
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Rect rect;
    rect.w = widthStep;
    rect.h = heightStep;

    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            int val = gameArr[y][x] % 10;

            if (val != 0)
            {

                setColor(renderer, val);
                rect.x = x * widthStep;
                rect.y = y * heightStep;

                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
            else
            {
                rect.x = x * widthStep;
                rect.y = y * heightStep;
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }
    int previewX = (WIDTH * widthStep) + 50;
    int previewY = 100;
    char scoreBuffer[20];
    sprintf(scoreBuffer, "Score: %d", score);
    drawText(renderer, previewX, 5, scoreBuffer, font, textColor);
    drawText(renderer, previewX, previewY - 60, "NEXT", font, textColor);

    for (int i = 0; i < 5; i++)
    {
        char buf[15];
        sprintf(buf, "%d", highscore[i]);
        drawText(renderer, previewX, 300 + i *30,buf, font, textColor);
    }

    SDL_Rect borderRect = {previewX - 20, previewY - 30, (4 * widthStep) + 20, (4 * heightStep) + 20};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &borderRect);

    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (shapes[nextShape][y][x] != 0)
            {
                setColor(renderer, nextShape + 1);

                rect.x = previewX + (x * widthStep);
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
    case 1:
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        break; // I - Azurová
    case 2:
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        break; // O - Žlutá
    case 3:
        SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);
        break; // T - Fialová
    case 4:
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        break; // S - Zelená
    case 5:
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        break; // Z - Červená
    case 6:
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        break; // J - Modrá
    case 7:
        SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
        break; // L - Oranžová
    default:
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        break; // Šedá (pojistka)
    }
}