#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "grafic.h"
#include "controller.h"
#include <time.h>
int main()
{
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO);
    int gameArr[20][10];
    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            gameArr[y][x] = 0;
        }
        printf("\n");
    }

    SDL_Window *window = SDL_CreateWindow("Snow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 700, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Event event;
    int running = 1;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    int test = 1;
    int iteration = 0;
    int score = 0;
    while (running == 1)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_a:
                    playMove(gameArr, -1, 0);
                    break;

                case SDLK_d:
                    playMove(gameArr, 1, 0);
                    break;

                case SDLK_s:
                    moveDown(gameArr);
                    iteration = 0;
                    break;

                case SDLK_w:

                    rotateShape(gameArr);
                    break;
                }
            }
        }
        if (shapeIsActive(gameArr))
        {
            if (iteration >= 30)
            {
                moveDown(gameArr);

                iteration = 0;
            }
        }
        else
        {
            score += controlLine(gameArr);
            
            if (spawnShape(gameArr) == 1)
            {
                printf("Game Over! Score: %d\n", score);
                running = 0;
            }
            
            

            iteration = 0;
        }   

        iteration++;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        renderArr(gameArr, renderer, window);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}