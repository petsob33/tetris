#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "grafic.h"
#define WIDTH 10
#define HEIGHT 20

void renderArr(int gameArr[20][10], SDL_Renderer *renderer, SDL_Window *window)
{

    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    int widthStep = (width - 100) / WIDTH;
    int heightStep = (height - 100) / HEIGHT;
    SDL_Rect rect;
    rect.w = widthStep;
    rect.h = heightStep;

    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            int hodnota = gameArr[y][x]%10;

            if (hodnota != 0)
            {
                switch (hodnota)
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
}