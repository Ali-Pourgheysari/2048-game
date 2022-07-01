// In the name of Allah
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <windows.h>
using namespace std;

int console[11][11], temp[11][11], temp2[11][11];
long score = 0, score2;

struct gamerec //This is a structure for saving the score of players
{
    char name[20];
    int scoresave;
};


void movedown(int rows, int cols, bool &jlag);
void moveup(int rows, int cols, bool &jlag);
void moveright(int rows, int cols, bool &jlag);
void moveleft(int rows, int cols, bool &jlag);
void newgame(int rows, int cols);
void printgame(int rows,int cols);
int gameover(int rows, int cols);
int win(int rows, int cols);