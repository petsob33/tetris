#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "grafic.h"
#include "controller.h"
#include <time.h>
#include <SDL2/SDL_ttf.h>

int main()
{
    
    srand(time(NULL));
    // INITIALIZATION
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("font.ttf", 24);
    SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 700, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Event event;

    int highScore[5] = {0};
    FILE *file = fopen("scores.txt", "r");
    if (file)
    {
        for (int i = 0; i < 5; i++)
        {
            fscanf(file, "%d", &highScore[i]);
        }
        fclose(file);
    }

    int gameArr[20][10] = {0};
    int actualShape = rand() % 7;
    int nextShape = rand() % 7;
    int iteration = 0, score = 0, speed = 30;

    GameState state = MENU;
    int menuOption = 0; // 0 -2

    // INPUT

    while (state != QUIT)
    {
        // event handling
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                state = QUIT;
                saveScore(score, highScore);
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (state == MENU)
                {
                    if (event.key.keysym.sym == SDLK_w)
                    {
                        menuOption--;
                        if (menuOption < 0)
                            menuOption = 2;
                    }
                    if (event.key.keysym.sym == SDLK_s)
                    {
                        menuOption++;
                        if (menuOption > 2)
                            menuOption = 0;
                    }
                    if (event.key.keysym.sym == SDLK_RETURN)
                    {
                        if (menuOption == 0)
                        {
                            resetGame(gameArr, &score, &iteration, &actualShape, &nextShape);
                            state = GAME;
                        }
                        if (menuOption == 1)
                            state = HIGHSCORES;
                        if (menuOption == 2)
                            state = QUIT;
                    }
                }
                else if (state == HIGHSCORES)
                {
                    if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_RETURN)
                    {
                        state = MENU;
                    }
                }

                else if (state == GAME)
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
                    case SDLK_SPACE:
                        while (shapeIsActive(gameArr))
                            moveDown(gameArr);
                        break;
                    case SDLK_ESCAPE:
                        saveScore(score, highScore);
                        state = MENU;
                        break;
                    }
                }
            }
        }

        // UI

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Color white = {255, 255, 255, 255};
        SDL_Color red = {255, 0, 0, 255};
        int width, height;
        SDL_GetWindowSize(window, &width, &height);

        switch (state)
        {
        case MENU:

            drawText(renderer, width / 2 - 50, 150, "TETRIS", font, white);
            drawText(renderer, width / 2 - 50, 300, "Start Game", font, (menuOption == 0) ? red : white);
            drawText(renderer, width / 2 - 50, 350, "High Scores", font, (menuOption == 1) ? red : white);
            drawText(renderer, width / 2 - 50, 400, "Exit", font, (menuOption == 2) ? red : white);
            drawText(renderer, width / 2 - 50, 600, "W - UP S - DOWN", font, white);

            break;

        case HIGHSCORES:

            drawText(renderer, width / 2 - 100, 100, "TOP 5 SCORE", font, white);
            char buffer[50];
            for (int i = 0; i < 5; i++)
            {
                sprintf(buffer, "%d. %d", i + 1, highScore[i]);
                drawText(renderer, width / 2 - 100, 200 + (i * 40), buffer, font, white);
            }
            drawText(renderer, width / 2 - 10, 500, "Press Enter", font, white);
            break;

        case GAME:

            if (shapeIsActive(gameArr))
            {
                if (iteration >= speed)
                {
                    moveDown(gameArr);
                    iteration = 0;
                }
            }
            else
            {
                
                switch (controlLine(gameArr))
                {
                case 1:
                    score += 40;
                    break;
                case 2:
                    score += 100;
                    break;
                case 3:
                    score += 300;
                    break;
                case 4:
                    score += 1200;
                    break;
                }
                if (score < 500)
                    speed = 30;
                else if (score < 1000)
                    speed = 25;
                else if (score < 2000)
                    speed = 21;
                else if (score < 4000)
                    speed = 17;
                else if (score < 8000)
                    speed = 13;
                else
                    speed = 10;

                if (spawnShape(gameArr, nextShape) == 1)
                {
                    saveScore(score, highScore);
                    state = MENU;
                }
                actualShape = nextShape;
                nextShape = rand() % 7;
                iteration = 0;
            }
            iteration++;
            renderArr(gameArr, renderer, window, nextShape, font, score, highScore);

            break;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}