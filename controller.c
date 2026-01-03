#include <stdlib.h>
#include <stdio.h>
#include "controller.h"

// Definice tvarů s ID barev podle tvého switche
const int shapes[7][4][4] = {
    {{0, 0, 0, 0},
     {1, 1, 1, 1},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},
    {{0, 2, 2, 0},
     {0, 2, 2, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},
    {{0, 3, 0, 0},
     {3, 3, 3, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},

    {{0, 4, 4, 0},
     {4, 4, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},

    {{5, 5, 0, 0},
     {0, 5, 5, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},

    {{6, 0, 0, 0},
     {6, 6, 6, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},

    {{0, 0, 7, 0},
     {7, 7, 7, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}}};


    
// spawn and place new shape
// controll spawn possibility
int spawnShape(int gameArr[20][10], int actualShape)
{
    int LeftSpawnX = rand() % 6;
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (gameArr[0 + y][LeftSpawnX + x] > 10)
            {
                return 1;
            }
        }
    }
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            gameArr[0 + y][LeftSpawnX + x] = shapes[actualShape][y][x];
        }
    }
    return 0;
}

// control and set dead shapes
int controlCollison(int gameArr[20][10])
{
    for (int y = 19; y > 0; y--)
    {
        for (int x = 0; x < 10; x++)
        {
            if (gameArr[y][x] > 0 && gameArr[y][x] < 10)
            {

                if (y == 19)
                {
                    return 1;
                }

                if (gameArr[y + 1][x] > 10)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}


// move shape down or set it as dead
void moveDown(int gameArr[20][10])
{

    int collison = controlCollison(gameArr);
    for (int y = 19; y >= 0; y--)
    {
        for (int x = 0; x < 10; x++)
        {

            if (gameArr[y][x] > 0 && gameArr[y][x] < 10)
            {

                if (collison == 1 || y == 19)
                {
                    gameArr[y][x] += 10;
                }
                else
                {
                    gameArr[y + 1][x] = gameArr[y][x];
                    gameArr[y][x] = 0;
                }
            }
        }
    }
}

// control if shape is active
// use in main loop
int shapeIsActive(int gameArr[20][10])
{
    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            if (gameArr[y][x] > 0 && gameArr[y][x] < 10)
            {

                return 1;
            }
        }
    }
    return 0;
}

// play move if possible
int playMove(int gameArr[20][10], int xMove, int yMove)
{
    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            if (gameArr[y][x] > 0 && gameArr[y][x] < 10)
            {

                if (gameArr[y + yMove][x + xMove] > 10 || x + xMove >= 10 || x + xMove < 0)
                {
                    return 0;
                }
            }
        }
    }

    for (int y = 0; y < 20; y++)
    {
        if (xMove > 0)
        {
            for (int x = 9; x >= 0; x--)
            {
                if (gameArr[y][x] > 0 && gameArr[y][x] < 10)
                {
                    gameArr[y + (yMove)][x + xMove] = gameArr[y][x];
                    gameArr[y][x] = 0;
                }
            }
        }
        else
        {
            
            for (int x = 0; x < 10; x++)
            {
                if (gameArr[y][x] > 0 && gameArr[y][x] < 10)
                {

                    gameArr[y + (yMove)][x + xMove] = gameArr[y][x];
                    gameArr[y][x] = 0;
                }
            }
        }
    }
    return 1;
}
// rotate shape if possible
void rotateShape(int gameArr[20][10])
{
    int minX = 10, minY = 20;
    int maxX = -1, maxY = -1;

    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 10; x++) {
            if (gameArr[y][x] > 0 && gameArr[y][x] < 10) {
                if (x < minX) minX = x;
                if (y < minY) minY = y;
                if (x > maxX) maxX = x;
                if (y > maxY) maxY = y;
            }
        }
    }

    if (minX == 10) return;

    int width = maxX - minX + 1;
    int height = maxY - minY + 1;

    if (width == 2 && height == 2) return;

    int size = 3;
    if (width == 4 || height == 4) size = 4;

    int temp[4][4] = {0};
    int rotated[4][4] = {0};
    int backupShape[4][4] = {0};
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (minY + y <= maxY && minX + x <= maxX) {
                if (gameArr[minY + y][minX + x] > 0 && gameArr[minY + y][minX + x] < 10) {
                    temp[y][x] = gameArr[minY + y][minX + x];
                    backupShape[y][x] = temp[y][x]; 
                    gameArr[minY + y][minX + x] = 0;
                }
            }
        }
    }

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            rotated[x][size - 1 - y] = temp[y][x];
        }
    }

    int offsetX = (width - height) / 2;
    int offsetY = (height - width) / 2;
    int targetX = minX + offsetX;
    int targetY = minY + offsetY;

    int collision = 0; 

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (rotated[y][x] != 0) { 
                int finalX = targetX + x;
                int finalY = targetY + y;

                if (finalX < 0 || finalX >= 10 || finalY >= 20) {
                    collision = 1; 
                }
                else if (finalY >= 0 && gameArr[finalY][finalX] > 10) {
                    collision = 1;
                }
            }
        }
    }

    if (collision == 0) {
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                if (rotated[y][x] != 0) {
                    gameArr[targetY + y][targetX + x] = rotated[y][x];
                }
            }
        }
    } else {
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                if (backupShape[y][x] != 0) {
                    gameArr[minY + y][minX + x] = backupShape[y][x];
                }
            }
        }
    }
}
// control and clear full lines
int controlLine(int gameArr[20][10])
{
    int doneLines = 0;
    for (int y = 0; y < 20; y++)
    {
        int full = 0;
        for (int x = 0; x < 10; x++)
        {
            if (gameArr[y][x] > 10)
            {
                full++;
            }
        }
        if (full == 10)
        {
            doneLines++;
            for (int row = y; row > 0; row--)
            {
                for (int x = 0; x < 10; x++)
                {
                    gameArr[row][x] = gameArr[row - 1][x];
                }
            }
            for (int x = 0; x < 10; x++)
            {
                gameArr[0][x] = 0;
            }
            y--;
        }
    }
    return doneLines;
}
// reset game state

void resetGame(int gameArr[20][10], int *score, int *iteration, int *actualShape, int *nextShape)
{
    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            gameArr[y][x] = 0;
        }
    }
    *score = 0;
    *iteration = 0;
    *actualShape = rand() % 7;
    *nextShape = rand() % 7;
}

// save high scores to file

void saveScore(int score, int highScore[5])
{
    for (int i = 0; i < 5; i++)
    {
        if (score > highScore[i])
        {
            int tmp = highScore[i];
            highScore[i] = score;
            score = tmp;
        }
    }

    FILE *file = fopen("scores.txt", "w");
    if (file)
    {
        for (int i = 0; i < 5; i++)
            fprintf(file, "%d\n", highScore[i]);
        fclose(file);
    }
}
