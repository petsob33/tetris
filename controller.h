
#ifndef controller_h   
#define controller_h   


int spawnShape(int gameArr[20][10]);
int controlCollison(int gameArr[20][10]);
void moveDown( int gameArr[20][10]);
int shapeIsActive(int gameArr[20][10]);
int playMove(int gameArr[20][10], int xMove, int yMove);
void rotateShape(int gameArr[20][10]);
int controlLine(int gameArr[20][10]);





#endif 