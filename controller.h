
#ifndef controller_h
#define controller_h

int spawnShape(int gameArr[20][10], int actualShape);
int controlCollison(int gameArr[20][10]);
void moveDown(int gameArr[20][10]);
int shapeIsActive(int gameArr[20][10]);
int playMove(int gameArr[20][10], int xMove, int yMove);
void rotateShape(int gameArr[20][10]);
int controlLine(int gameArr[20][10]);
void resetGame(int gameArr[20][10], int *score, int *iteration, int *actualShape, int *nextShape);
void saveScore(int score, int highScore[5]);

typedef enum
{
    MENU,
    GAME,
    HIGHSCORES,
    QUIT
} GameState;



#endif