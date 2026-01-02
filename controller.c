#include <stdlib.h>
#include <stdio.h>
#include "controller.h"
#include "controller.h" // nebo tvůj hlavičkový soubor

// Definice tvarů s ID barev podle tvého switche
const int shapes[7][4][4] = {
    // 1. I (Tyčka) - Azurová
    // Hodnota 1
    {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}},
    // 2. O (Čtverec) - Žlutá
    // Hodnota 2
    {
        {0, 2, 2, 0},
        {0, 2, 2, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}},
    // 3. T (Téčko) - Fialová
    // Hodnota 3
    {
        {0, 3, 0, 0},
        {3, 3, 3, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}},
    // 4. S (Esíčko) - Zelená
    // Hodnota 4
    {
        {0, 4, 4, 0},
        {4, 4, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}},
    // 5. Z (Zetko) - Červená
    // Hodnota 5
    {
        {5, 5, 0, 0},
        {0, 5, 5, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}},
    // 6. J (Hák doleva) - Modrá
    // Hodnota 6
    {
        {6, 0, 0, 0},
        {6, 6, 6, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}},
    // 7. L (Hák doprava) - Oranžová
    // Hodnota 7
    {
        {0, 0, 7, 0},
        {7, 7, 7, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}}};
int spawnShape(int gameArr[20][10])
{
    int randomShape = rand() % 7;
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
            gameArr[0 + y][LeftSpawnX + x] = shapes[randomShape][y][x];
        }
    }
    return 0;
}
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

void rotateShape(int gameArr[20][10])
{
    int minX = 10, minY = 20;
    int maxX = -1, maxY = -1;
    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            if (gameArr[y][x] > 0 && gameArr[y][x] < 10)
            {
                if (x < minX)
                    minX = x;
                if (y < minY)
                    minY = y;
                if (x > maxX)
                    maxX = x;
                if (y > maxY)
                    maxY = y;
            }
        }
    }

    if (minX == 10)
        return;
    int width = maxX - minX + 1;
    int height = maxY - minY + 1;
    int size = 3;
    if (width == 4 || height == 4)
    {
        size = 4;
    }
    else if (width == 2 && height == 2)
    {
        return;
    }
    int temp[4][4] = {0};
    int rotated[4][4] = {0};
    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            if (minY + y < 20 && minX + x < 10)
            {
                if (gameArr[minY + y][minX + x] > 0 && gameArr[minY + y][minX + x] < 10)
                {
                    temp[y][x] = gameArr[minY + y][minX + x];
                    gameArr[minY + y][minX + x] = 0;
                }
            }
        }
    }
    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            rotated[x][size - 1 - y] = temp[y][x];
        }
    }
    int collision = 0;
    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            if (rotated[y][x] != 0)
            {
                int targetX = minX + x;
                int targetY = minY + y;

                if (targetX < 0 || targetX >= 10 || targetY >= 20)
                {
                    collision = 1;
                }
                else if (gameArr[targetY][targetX] != 0)
                {
                    collision = 1;
                }
            }
        }
    }
    if (collision == 0)
    {
        for (int y = 0; y < size; y++)
        {
            for (int x = 0; x < size; x++)
            {
                if (rotated[y][x] != 0)
                {
                    if (minY + y < 20 && minX + x < 10)
                        gameArr[minY + y][minX + x] = rotated[y][x];
                }
            }
        }
    }
    else
    {
        for (int y = 0; y < size; y++)
        {
            for (int x = 0; x < size; x++)
            {
                if (temp[y][x] != 0)
                {
                    if (minY + y < 20 && minX + x < 10)
                        gameArr[minY + y][minX + x] = temp[y][x];
                }
            }
        }
    }
}

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