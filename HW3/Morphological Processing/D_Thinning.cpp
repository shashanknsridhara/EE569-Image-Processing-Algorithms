#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <math.h>

using namespace std;

#define PI 3.14159265
#define COS(x) cos(x)
#define SIN(x) sin(x)

unsigned char Thin[42][9] ={{255,255,255,0,0,0,0,0,255},{255,0,255,255,255,0,0,0,0},{255,0,0,0,255,255,255,0,0},{255,0,0,0,0,0,255,255,255},{255,255,0,255,255,0,0,0,0},{255,255,0,255,0,0,0,0,255},{255,0,255,255,0,255,0,0,0},{255,255,255,0,0,0,0,255,0},{255,255,255,255,0,0,0,0,0},{255,0,0,255,255,255,0,0,0},{255,0,0,0,0,255,255,255,0},{255,255,0,0,0,0,0,255,255},{255,255,0,255,255,0,0,0,255},{255,0,255,255,0,255,255,0,0},{255,255,255,255,255,0,0,0,0},{255,255,255,255,0,0,0,0,255},{255,0,255,255,255,255,0,0,0},{255,0,0,255,255,255,255,0,0},{255,0,0,0,255,255,255,255,0},{255,0,0,0,0,255,255,255,255},{255,255,0,0,0,0,255,255,255},{255,255,255,0,0,0,0,255,255},{255,255,255,255,255,0,0,0,255},{255,0,255,255,255,255,255,0,0},{255,0,0,0,255,255,255,255,255},{255,255,255,0,0,0,255,255,255},{255,255,255,255,0,0,0,255,255},{255,255,255,255,255,255,0,0,0},{255,0,0,255,255,255,255,255,0},{255,255,0,0,0,255,255,255,255},{255,255,255,255,255,0,0,255,255},{255,255,255,255,0,0,255,255,255},{255,255,255,255,255,255,255,0,0},{255,255,255,255,255,255,0,0,255},{255,0,255,255,255,255,255,255,0},{255,0,0,255,255,255,255,255,255},{255,255,0,0,255,255,255,255,255},{255,255,255,0,0,255,255,255,255},{255,255,255,255,255,0,255,255,255},{255,255,255,255,255,255,255,0,255},{255,0,255,255,255,255,255,255,255},{255,255,255,0,255,255,255,255,255}};
//unsigned char Pattern[110][9] = {{1,0,1,0,0,0,0,0,0},{1,0,0,0,1,0,0,0,0},{1,0,0,0,0,0,0,1,0},{1,1,0,0,0,0,0,0,0},{1,1,1,0,0,0,0,0,0},{1,0,1,1,0,0,0,0,0},{1,0,0,1,1,0,0,0,0},{1,0,0,0,1,1,0,0,0},{1,0,0,0,0,1,1,0,0},{1,0,0,0,0,0,1,1,0},{1,0,0,0,0,0,0,1,1},{1,1,0,0,0,0,0,0,1},{1,0,1,1,0,1,0,0,0},{1,1,0,1,1,0,0,0,0},{1,1,0,1,0,0,0,0,1},{1,1,1,0,0,0,0,1,0},{1,1,1,0,0,0,1,0,0},{1,0,1,1,0,0,1,0,0},{1,1,1,1,0,0,1,0,0},{1,0,0,1,1,0,0,0,1},{1,0,0,0,1,1,0,0,1},{1,0,0,1,1,1,0,0,1},{1,0,1,0,0,0,1,1,0},{1,0,1,0,0,1,1,0,0},{1,0,1,0,0,1,1,1,0},{1,1,0,0,1,0,0,0,1},{1,0,0,0,1,0,0,1,1},{1,1,0,0,1,0,0,1,1},{1,0,0,1,1,1,0,0,0},{1,1,1,1,1,1,1,1,1},{1,1,0,1,0,1,0,0,0},{1,1,0,1,1,1,1,0,0},{1,1,0,1,0,1,0,0,0},{1,1,1,1,0,1,0,0,1},{1,1,0,0,0,1,0,1,0},{1,1,1,0,0,1,0,1,1},{1,1,0,0,0,1,0,1,0},{1,1,0,0,1,1,1,1,0},{1,0,0,1,0,1,0,1,0},{1,0,1,1,1,1,0,1,0},{1,0,0,1,0,1,0,1,0},{1,0,0,1,0,1,1,1,1},{1,1,0,1,0,0,0,1,0},{1,1,0,1,0,0,1,1,1},{1,1,0,1,0,0,0,1,0},{1,1,1,1,1,0,0,1,0},{1,1,0,1,0,0,1,0,0},{1,1,0,1,1,0,1,0,1},{1,0,0,1,0,1,0,0,1},{1,0,1,1,0,1,1,0,1},{1,0,1,0,0,1,0,1,0},{1,0,1,0,1,1,0,1,1},{1,1,0,0,1,0,0,1,0},{1,1,1,0,1,0,1,1,0},{1,0,1,0,1,0,0,0,1},{1,1,1,1,1,1,0,0,1},{1,0,1,0,1,0,0,1,0},{1,1,1,1,1,1,0,1,0},{1,0,1,0,1,0,0,1,1},{1,1,1,1,1,1,0,1,1},{1,0,1,0,1,0,1,0,0},{1,1,1,1,1,1,1,0,0},{1,0,1,0,1,0,1,0,1},{1,1,1,1,1,1,1,0,1},{1,0,1,0,1,0,1,1,0},{1,1,1,1,1,1,1,1,0},{1,0,1,0,1,0,1,1,1},{1,1,1,1,1,1,1,1,1},{1,0,1,0,1,0,1,0,0},{1,0,1,1,1,1,1,1,0},{1,1,0,0,1,0,1,0,0},{1,1,0,1,1,1,1,1,0},{1,1,1,0,1,0,1,0,0},{1,1,1,1,1,1,1,1,0},{1,0,0,0,1,0,0,0,1},{1,0,0,1,1,1,1,1,1},{1,0,1,0,1,0,1,0,1},{1,0,1,1,1,1,1,1,1},{1,1,0,0,1,0,1,0,1},{1,1,0,1,1,1,1,1,1},{1,1,1,0,1,0,1,0,1},{1,1,1,1,1,1,1,1,1},{1,0,0,0,1,0,1,0,1},{1,1,0,0,1,1,1,1,1},{1,0,0,1,0,0,1,0,1},{1,1,0,1,0,1,1,1,1},{1,0,0,1,1,0,1,0,1},{1,1,0,1,1,1,1,1,1},{1,0,1,0,0,0,1,0,1},{1,0,1,0,0,1,1,1,1},{1,0,1,0,1,0,1,0,1},{1,1,1,0,1,1,1,1,1},{1,0,1,1,0,0,1,0,1},{1,1,1,1,0,1,1,1,1},{1,0,1,1,1,0,1,0,1},{1,1,1,1,1,1,1,1,1},{1,0,1,0,0,0,1,0,1},{1,1,1,1,0,0,1,1,1},{1,0,1,0,0,1,0,0,1},{1,1,1,1,0,1,0,1,1},{1,0,1,0,0,1,1,0,1},{1,1,1,1,0,1,1,1,1},{1,0,1,0,1,0,0,0,1},{1,1,1,1,1,0,0,1,1},{1,0,1,0,1,0,1,0,1},{1,1,1,1,1,0,1,1,1},{1,0,1,0,1,1,0,0,1},{1,1,1,1,1,1,0,1,1},{1,0,1,0,1,1,1,0,1},{1,1,1,1,1,1,1,1,1}};
unsigned char Pattern[332][9]={{0, 0, 1, 0, 1, 0, 0, 0, 0, },
{1, 0, 0, 0, 1, 0, 0, 0, 0, },
{0, 0, 0, 0, 1, 0, 0, 1, 0, },
{0, 0, 0, 0, 1, 1, 0, 0, 0, },
{0, 0, 1, 0, 1, 1, 0, 0, 0, },
{0, 1, 1, 0, 1, 0, 0, 0, 0, },
{1, 1, 0, 0, 1, 0, 0, 0, 0, },
{1, 0, 0, 1, 1, 0, 0, 0, 0, },
{0, 0, 0, 1, 1, 0, 0, 0, 0, },
{0, 0, 0, 0, 1, 0, 1, 1, 0, },
{0, 0, 0, 0, 1, 0, 0, 1, 1, },
{0, 0, 0, 0, 1, 1, 0, 0, 1, },
{0, 1, 1, 1, 1, 0, 0, 0, 0, },
{1, 1, 0, 0, 1, 1, 0, 0, 0, },
{0, 1, 0, 0, 1, 1, 0, 0, 1, },
{0, 0, 1, 0, 1, 1, 0, 1, 0, },
{0, 0, 1, 0, 1, 1, 1, 0, 0, },
{1, 1, 0, 0, 1, 0, 0, 0, 1, },
{0, 0, 1, 0, 1, 0, 1, 1, 0, },
{1, 0, 0, 0, 1, 1, 0, 0, 1, },
{0, 1, 1, 0, 1, 0, 1, 0, 0, },
{1, 0, 0, 1, 1, 0, 0, 0, 1, },
{0, 0, 1, 1, 1, 0, 1, 0, 0, },
{1, 0, 0, 0, 1, 0, 0, 1, 1, },
{0, 1, 1, 0, 1, 1, 1, 0, 0, },
{1, 1, 0, 1, 1, 0, 0, 0, 1, },
{0, 0, 1, 1, 1, 0, 1, 1, 0, },
{1, 0, 0, 0, 1, 1, 0, 1, 1, },
{0, 1, 0, 1, 1, 1, 0, 0, 0, },
{0, 1, 0, 1, 1, 1, 0, 0, 0, },
{0, 0, 0, 1, 1, 1, 0, 1, 0, },
{0, 0, 0, 1, 1, 1, 0, 1, 0, },
{0, 1, 0, 1, 1, 0, 0, 1, 0, },
{0, 1, 0, 1, 1, 0, 0, 1, 0, },
{0, 1, 0, 0, 1, 1, 0, 1, 0, },
{0, 1, 0, 0, 1, 1, 0, 1, 0, },
{0, 1, 0, 0, 1, 1, 1, 0, 0, },
{0, 1, 0, 1, 1, 0, 0, 0, 1, },
{0, 0, 1, 1, 1, 0, 0, 1, 0, },
{1, 0, 0, 0, 1, 1, 0, 1, 0, },
{1, 1, 0, 1, 1, 0, 0, 0, 0, },
{1, 1, 0, 1, 1, 0, 0, 0, 1, },
{1, 1, 0, 1, 1, 0, 0, 1, 0, },
{1, 1, 0, 1, 1, 0, 0, 1, 1, },
{1, 1, 0, 1, 1, 0, 1, 0, 0, },
{1, 1, 0, 1, 1, 0, 1, 0, 1, },
{1, 1, 0, 1, 1, 0, 1, 1, 0, },
{1, 1, 0, 1, 1, 0, 1, 1, 1, },
{0, 1, 0, 1, 1, 1, 1, 0, 0, },
{0, 1, 0, 1, 1, 1, 0, 0, 1, },
{0, 0, 0, 1, 1, 1, 0, 1, 1, },
{0, 0, 0, 1, 1, 1, 1, 1, 0, },
{0, 1, 1, 1, 1, 0, 0, 1, 0, },
{0, 1, 0, 1, 1, 0, 0, 1, 1, },
{0, 1, 0, 0, 1, 1, 0, 1, 1, },
{0, 1, 1, 0, 1, 1, 0, 1, 0, },
{0, 1, 0, 0, 1, 1, 1, 0, 1, },
{0, 1, 0, 1, 1, 0, 1, 0, 1, },
{0, 0, 1, 1, 1, 0, 0, 1, 1, },
{1, 0, 0, 0, 1, 1, 1, 1, 0, },
{1, 1, 0, 1, 1, 1, 0, 0, 0, },
{1, 1, 0, 1, 1, 1, 0, 0, 1, },
{1, 1, 0, 1, 1, 1, 0, 1, 0, },
{1, 1, 0, 1, 1, 1, 0, 1, 1, },
{1, 1, 0, 1, 1, 1, 1, 0, 0, },
{1, 1, 0, 1, 1, 1, 1, 0, 1, },
{1, 1, 0, 1, 1, 1, 1, 1, 0, },
{1, 1, 0, 1, 1, 1, 1, 1, 1, },
{1, 1, 0, 1, 1, 1, 0, 0, 0, },
{0, 1, 1, 1, 1, 1, 0, 0, 0, },
{0, 0, 1, 1, 1, 1, 0, 1, 0, },
{1, 0, 0, 1, 1, 1, 0, 1, 0, },
{1, 1, 0, 1, 1, 0, 0, 1, 0, },
{0, 1, 0, 1, 1, 0, 1, 1, 0, },
{0, 1, 0, 0, 1, 1, 1, 1, 0, },
{1, 1, 0, 0, 1, 1, 0, 1, 0, },
{1, 1, 0, 0, 1, 1, 1, 0, 0, },
{0, 1, 1, 1, 1, 0, 0, 0, 1, },
{1, 0, 1, 1, 1, 0, 0, 1, 0, },
{1, 0, 1, 0, 1, 1, 0, 1, 0, },
{1, 1, 1, 1, 1, 0, 0, 0, 0, },
{1, 1, 1, 1, 1, 0, 0, 0, 1, },
{1, 1, 1, 1, 1, 0, 0, 1, 0, },
{1, 1, 1, 1, 1, 0, 0, 1, 1, },
{1, 1, 1, 1, 1, 0, 1, 0, 0, },
{1, 1, 1, 1, 1, 0, 1, 0, 1, },
{1, 1, 1, 1, 1, 0, 1, 1, 0, },
{1, 1, 1, 1, 1, 0, 1, 1, 1, },
{1, 1, 0, 1, 1, 1, 1, 0, 0, },
{0, 1, 1, 1, 1, 1, 0, 0, 1, },
{0, 0, 1, 1, 1, 1, 0, 1, 1, },
{1, 0, 0, 1, 1, 1, 1, 1, 0, },
{1, 1, 1, 1, 1, 0, 0, 1, 0, },
{0, 1, 0, 1, 1, 0, 1, 1, 1, },
{0, 1, 0, 0, 1, 1, 1, 1, 1, },
{1, 1, 1, 0, 1, 1, 0, 1, 0, },
{1, 1, 0, 0, 1, 1, 1, 0, 1, },
{0, 1, 1, 1, 1, 0, 1, 0, 1, },
{1, 0, 1, 1, 1, 0, 0, 1, 1, },
{1, 0, 1, 0, 1, 1, 1, 1, 0, },
{1, 1, 1, 1, 1, 1, 0, 0, 0, },
{1, 1, 1, 1, 1, 1, 0, 0, 1, },
{1, 1, 1, 1, 1, 1, 0, 1, 0, },
{1, 1, 1, 1, 1, 1, 0, 1, 1, },
{1, 1, 1, 1, 1, 1, 1, 0, 0, },
{1, 1, 1, 1, 1, 1, 1, 0, 1, },
{1, 1, 1, 1, 1, 1, 1, 1, 0, },
{1, 1, 1, 1, 1, 1, 1, 1, 1, },
{1, 0, 1, 0, 1, 0, 0, 0, 1, },
{1, 0, 1, 0, 1, 0, 1, 0, 0, },
{1, 0, 0, 0, 1, 0, 1, 0, 1, },
{0, 0, 1, 0, 1, 0, 1, 0, 1, },
{1, 0, 1, 0, 1, 1, 0, 0, 1, },
{1, 0, 1, 0, 1, 0, 1, 1, 0, },
{1, 0, 0, 0, 1, 0, 1, 1, 1, },
{0, 0, 1, 0, 1, 0, 1, 1, 1, },
{1, 0, 1, 1, 1, 0, 0, 0, 1, },
{1, 0, 1, 1, 1, 0, 1, 0, 0, },
{1, 0, 0, 0, 1, 1, 1, 0, 1, },
{0, 0, 1, 0, 1, 1, 1, 0, 1, },
{1, 0, 1, 1, 1, 1, 0, 0, 1, },
{1, 0, 1, 1, 1, 0, 1, 1, 0, },
{1, 0, 0, 0, 1, 1, 1, 1, 1, },
{0, 0, 1, 0, 1, 1, 1, 1, 1, },
{1, 1, 1, 0, 1, 0, 0, 0, 1, },
{1, 1, 1, 0, 1, 0, 1, 0, 0, },
{1, 0, 0, 1, 1, 0, 1, 0, 1, },
{0, 1, 1, 0, 1, 0, 1, 0, 1, },
{1, 1, 1, 0, 1, 1, 0, 0, 1, },
{1, 1, 1, 0, 1, 0, 1, 1, 0, },
{1, 0, 0, 1, 1, 0, 1, 1, 1, },
{0, 1, 1, 0, 1, 0, 1, 1, 1, },
{1, 1, 1, 1, 1, 0, 0, 0, 1, },
{1, 1, 1, 1, 1, 0, 1, 0, 0, },
{1, 0, 0, 1, 1, 1, 1, 0, 1, },
{0, 1, 1, 0, 1, 1, 1, 0, 1, },
{1, 1, 1, 1, 1, 1, 0, 0, 1, },
{1, 1, 1, 1, 1, 0, 1, 1, 0, },
{1, 0, 0, 1, 1, 1, 1, 1, 1, },
{0, 1, 1, 0, 1, 1, 1, 1, 1, },
{1, 0, 1, 0, 1, 0, 0, 1, 0, },
{1, 0, 0, 0, 1, 1, 1, 0, 0, },
{0, 1, 0, 0, 1, 0, 1, 0, 1, },
{0, 0, 1, 1, 1, 0, 0, 0, 1, },
{1, 0, 1, 0, 1, 1, 0, 1, 0, },
{1, 0, 0, 0, 1, 1, 1, 1, 0, },
{0, 1, 0, 0, 1, 0, 1, 1, 1, },
{0, 0, 1, 1, 1, 0, 0, 1, 1, },
{1, 0, 1, 1, 1, 0, 0, 1, 0, },
{1, 0, 0, 1, 1, 1, 1, 0, 0, },
{0, 1, 0, 0, 1, 1, 1, 0, 1, },
{0, 0, 1, 1, 1, 1, 0, 0, 1, },
{1, 0, 1, 1, 1, 1, 0, 1, 0, },
{1, 0, 0, 1, 1, 1, 1, 1, 0, },
{0, 1, 0, 0, 1, 1, 1, 1, 1, },
{0, 0, 1, 1, 1, 1, 0, 1, 1, },
{1, 1, 1, 0, 1, 0, 0, 1, 0, },
{1, 1, 0, 0, 1, 1, 1, 0, 0, },
{0, 1, 0, 1, 1, 0, 1, 0, 1, },
{0, 1, 1, 1, 1, 0, 0, 0, 1, },
{1, 1, 1, 0, 1, 1, 0, 1, 0, },
{1, 1, 0, 0, 1, 1, 1, 1, 0, },
{0, 1, 0, 1, 1, 0, 1, 1, 1, },
{0, 1, 1, 1, 1, 0, 0, 1, 1, },
{1, 1, 1, 1, 1, 0, 0, 1, 0, },
{1, 1, 0, 1, 1, 1, 1, 0, 0, },
{0, 1, 0, 1, 1, 1, 1, 0, 1, },
{0, 1, 1, 1, 1, 1, 0, 0, 1, },
{1, 1, 1, 1, 1, 1, 0, 1, 0, },
{1, 1, 0, 1, 1, 1, 1, 1, 0, },
{0, 1, 0, 1, 1, 1, 1, 1, 1, },
{0, 1, 1, 1, 1, 1, 0, 1, 1, },
{1, 0, 1, 0, 1, 0, 0, 1, 1, },
{1, 0, 1, 0, 1, 1, 1, 0, 0, },
{1, 1, 0, 0, 1, 0, 1, 0, 1, },
{0, 0, 1, 1, 1, 0, 1, 0, 1, },
{1, 0, 1, 0, 1, 1, 0, 1, 1, },
{1, 0, 1, 0, 1, 1, 1, 1, 0, },
{1, 1, 0, 0, 1, 0, 1, 1, 1, },
{0, 0, 1, 1, 1, 0, 1, 1, 1, },
{1, 0, 1, 1, 1, 0, 0, 1, 1, },
{1, 0, 1, 1, 1, 1, 1, 0, 0, },
{1, 1, 0, 0, 1, 1, 1, 0, 1, },
{0, 0, 1, 1, 1, 1, 1, 0, 1, },
{1, 0, 1, 1, 1, 1, 0, 1, 1, },
{1, 0, 1, 1, 1, 1, 1, 1, 0, },
{1, 1, 0, 0, 1, 1, 1, 1, 1, },
{0, 0, 1, 1, 1, 1, 1, 1, 1, },
{1, 1, 1, 0, 1, 0, 0, 1, 1, },
{1, 1, 1, 0, 1, 1, 1, 0, 0, },
{1, 1, 0, 1, 1, 0, 1, 0, 1, },
{0, 1, 1, 1, 1, 0, 1, 0, 1, },
{1, 1, 1, 0, 1, 1, 0, 1, 1, },
{1, 1, 1, 0, 1, 1, 1, 1, 0, },
{1, 1, 0, 1, 1, 0, 1, 1, 1, },
{0, 1, 1, 1, 1, 0, 1, 1, 1, },
{1, 1, 1, 1, 1, 0, 0, 1, 1, },
{1, 1, 1, 1, 1, 1, 1, 0, 0, },
{1, 1, 0, 1, 1, 1, 1, 0, 1, },
{0, 1, 1, 1, 1, 1, 1, 0, 1, },
{1, 1, 1, 1, 1, 1, 0, 1, 1, },
{1, 1, 1, 1, 1, 1, 1, 1, 0, },
{1, 1, 0, 1, 1, 1, 1, 1, 1, },
{0, 1, 1, 1, 1, 1, 1, 1, 1, },
{1, 0, 1, 0, 1, 0, 1, 0, 0, },
{1, 0, 0, 0, 1, 0, 1, 0, 1, },
{0, 0, 1, 0, 1, 0, 1, 0, 1, },
{1, 0, 1, 0, 1, 0, 0, 0, 1, },
{1, 0, 1, 0, 1, 1, 1, 0, 0, },
{1, 0, 0, 0, 1, 0, 1, 1, 1, },
{0, 0, 1, 0, 1, 0, 1, 1, 1, },
{1, 0, 1, 0, 1, 0, 0, 1, 1, },
{1, 0, 1, 1, 1, 0, 1, 0, 0, },
{1, 0, 0, 1, 1, 0, 1, 0, 1, },
{0, 0, 1, 0, 1, 1, 1, 0, 1, },
{1, 0, 1, 0, 1, 1, 0, 0, 1, },
{1, 0, 1, 1, 1, 1, 1, 0, 0, },
{1, 0, 0, 1, 1, 0, 1, 1, 1, },
{0, 0, 1, 0, 1, 1, 1, 1, 1, },
{1, 0, 1, 0, 1, 1, 0, 1, 1, },
{1, 1, 1, 0, 1, 0, 1, 0, 0, },
{1, 1, 0, 0, 1, 0, 1, 0, 1, },
{0, 0, 1, 1, 1, 0, 1, 0, 1, },
{1, 1, 1, 0, 1, 0, 0, 0, 1, },
{1, 1, 1, 0, 1, 1, 1, 0, 0, },
{1, 1, 0, 0, 1, 0, 1, 1, 1, },
{0, 0, 1, 1, 1, 0, 1, 1, 1, },
{1, 1, 1, 0, 1, 0, 0, 1, 1, },
{1, 1, 1, 1, 1, 0, 1, 0, 0, },
{1, 1, 0, 1, 1, 0, 1, 0, 1, },
{0, 0, 1, 1, 1, 1, 1, 0, 1, },
{1, 1, 1, 0, 1, 1, 0, 0, 1, },
{1, 1, 1, 1, 1, 1, 1, 0, 0, },
{1, 1, 0, 1, 1, 0, 1, 1, 1, },
{0, 0, 1, 1, 1, 1, 1, 1, 1, },
{1, 1, 1, 0, 1, 1, 0, 1, 1, },
{1, 0, 1, 0, 1, 0, 1, 0, 1, },
{1, 0, 1, 0, 1, 0, 1, 0, 1, },
{1, 0, 1, 0, 1, 0, 1, 0, 1, },
{1, 0, 1, 0, 1, 0, 1, 0, 1, },
{1, 0, 1, 0, 1, 1, 1, 0, 1, },
{1, 0, 1, 0, 1, 0, 1, 1, 1, },
{1, 0, 1, 0, 1, 0, 1, 1, 1, },
{1, 0, 1, 0, 1, 0, 1, 1, 1, },
{1, 0, 1, 1, 1, 0, 1, 0, 1, },
{1, 0, 1, 1, 1, 0, 1, 0, 1, },
{1, 0, 1, 0, 1, 1, 1, 0, 1, },
{1, 0, 1, 0, 1, 1, 1, 0, 1, },
{1, 0, 1, 1, 1, 1, 1, 0, 1, },
{1, 0, 1, 1, 1, 0, 1, 1, 1, },
{1, 0, 1, 0, 1, 1, 1, 1, 1, },
{1, 0, 1, 0, 1, 1, 1, 1, 1, },
{1, 1, 1, 0, 1, 0, 1, 0, 1, },
{1, 1, 1, 0, 1, 0, 1, 0, 1, },
{1, 0, 1, 1, 1, 0, 1, 0, 1, },
{1, 1, 1, 0, 1, 0, 1, 0, 1, },
{1, 1, 1, 0, 1, 1, 1, 0, 1, },
{1, 1, 1, 0, 1, 0, 1, 1, 1, },
{1, 0, 1, 1, 1, 0, 1, 1, 1, },
{1, 1, 1, 0, 1, 0, 1, 1, 1, },
{1, 1, 1, 1, 1, 0, 1, 0, 1, },
{1, 1, 1, 1, 1, 0, 1, 0, 1, },
{1, 0, 1, 1, 1, 1, 1, 0, 1, },
{1, 1, 1, 0, 1, 1, 1, 0, 1, },
{1, 1, 1, 1, 1, 1, 1, 0, 1, },
{1, 1, 1, 1, 1, 0, 1, 1, 1, },
{1, 0, 1, 1, 1, 1, 1, 1, 1, },
{1, 1, 1, 0, 1, 1, 1, 1, 1, },
{1, 0, 1, 0, 1, 0, 1, 1, 0, },
{1, 0, 0, 0, 1, 1, 1, 0, 1, },
{0, 1, 1, 0, 1, 0, 1, 0, 1, },
{1, 0, 1, 1, 1, 0, 0, 0, 1, },
{1, 0, 1, 0, 1, 1, 1, 1, 0, },
{1, 0, 0, 0, 1, 1, 1, 1, 1, },
{0, 1, 1, 0, 1, 0, 1, 1, 1, },
{1, 0, 1, 1, 1, 0, 0, 1, 1, },
{1, 0, 1, 1, 1, 0, 1, 1, 0, },
{1, 0, 0, 1, 1, 1, 1, 0, 1, },
{0, 1, 1, 0, 1, 1, 1, 0, 1, },
{1, 0, 1, 1, 1, 1, 0, 0, 1, },
{1, 0, 1, 1, 1, 1, 1, 1, 0, },
{1, 0, 0, 1, 1, 1, 1, 1, 1, },
{0, 1, 1, 0, 1, 1, 1, 1, 1, },
{1, 0, 1, 1, 1, 1, 0, 1, 1, },
{1, 1, 1, 0, 1, 0, 1, 1, 0, },
{1, 1, 0, 0, 1, 1, 1, 0, 1, },
{0, 1, 1, 1, 1, 0, 1, 0, 1, },
{1, 1, 1, 1, 1, 0, 0, 0, 1, },
{1, 1, 1, 0, 1, 1, 1, 1, 0, },
{1, 1, 0, 0, 1, 1, 1, 1, 1, },
{0, 1, 1, 1, 1, 0, 1, 1, 1, },
{1, 1, 1, 1, 1, 0, 0, 1, 1, },
{1, 1, 1, 1, 1, 0, 1, 1, 0, },
{1, 1, 0, 1, 1, 1, 1, 0, 1, },
{0, 1, 1, 1, 1, 1, 1, 0, 1, },
{1, 1, 1, 1, 1, 1, 0, 0, 1, },
{1, 1, 1, 1, 1, 1, 1, 1, 0, },
{1, 1, 0, 1, 1, 1, 1, 1, 1, },
{0, 1, 1, 1, 1, 1, 1, 1, 1, },
{1, 1, 1, 1, 1, 1, 0, 1, 1, },
{1, 0, 1, 0, 1, 0, 1, 1, 1, },
{1, 0, 1, 0, 1, 1, 1, 0, 1, },
{1, 1, 1, 0, 1, 0, 1, 0, 1, },
{1, 0, 1, 1, 1, 0, 1, 0, 1, },
{1, 0, 1, 0, 1, 1, 1, 1, 1, },
{1, 0, 1, 0, 1, 1, 1, 1, 1, },
{1, 1, 1, 0, 1, 0, 1, 1, 1, },
{1, 0, 1, 1, 1, 0, 1, 1, 1, },
{1, 0, 1, 1, 1, 0, 1, 1, 1, },
{1, 0, 1, 1, 1, 1, 1, 0, 1, },
{1, 1, 1, 0, 1, 1, 1, 0, 1, },
{1, 0, 1, 1, 1, 1, 1, 0, 1, },
{1, 0, 1, 1, 1, 1, 1, 1, 1, },
{1, 0, 1, 1, 1, 1, 1, 1, 1, },
{1, 1, 1, 0, 1, 1, 1, 1, 1, },
{1, 0, 1, 1, 1, 1, 1, 1, 1, },
{1, 1, 1, 0, 1, 0, 1, 1, 1, },
{1, 1, 1, 0, 1, 1, 1, 0, 1, },
{1, 1, 1, 1, 1, 0, 1, 0, 1, },
{1, 1, 1, 1, 1, 0, 1, 0, 1, },
{1, 1, 1, 0, 1, 1, 1, 1, 1, },
{1, 1, 1, 0, 1, 1, 1, 1, 1, },
{1, 1, 1, 1, 1, 0, 1, 1, 1, },
{1, 1, 1, 1, 1, 0, 1, 1, 1, },
{1, 1, 1, 1, 1, 0, 1, 1, 1, },
{1, 1, 1, 1, 1, 1, 1, 0, 1, },
{1, 1, 1, 1, 1, 1, 1, 0, 1, },
{1, 1, 1, 1, 1, 1, 1, 0, 1, },
{1, 1, 1, 1, 1, 1, 1, 1, 1, },
{1, 1, 1, 1, 1, 1, 1, 1, 1, },
{1, 1, 1, 1, 1, 1, 1, 1, 1, },
{1, 1, 1, 1, 1, 1, 1, 1, 1, }};

unsigned char find_thin(unsigned char mask[9]){
    int flag;
    for(int i=0; i<42;++i){
        flag =0;
        for(int j=0; j<9;++j){
            if(mask[j]!= Thin[i][j]){
                flag =1;
                break;
            }
        }
        if(flag==0){
            return 1;
        }
    }
    return 0;
}

unsigned char find_pattern(unsigned char mask[9]){
    int flag;
    for(int i=0; i<332;++i){
        flag =0;
        for(int j=0; j<9;++j){
            if(mask[j]!= Pattern[i][j]){
                flag =1;
                break;
            }
        }
        if(flag==0){
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Size = 400;

	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}

	// Check if image is grayscale or color
	if (argc < 4){
		BytesPerPixel = 1; // default is grey image
	}
	else {
		BytesPerPixel = atoi(argv[3]);
		// Check if size is specified
		if (argc >= 5){
			Size = atoi(argv[4]);
		}
	}

    int height = 558;
    int width = 558;
	// Allocate image data array
	unsigned char Imagedata[height][width][BytesPerPixel];
	//unsigned char ImageOriginal[height][width][1];
	unsigned char OutputImage[height][width][1];
	unsigned char Reimage[height+2][width+2][1];
    unsigned char Map[height][width];
    unsigned char mask[9];
    unsigned char Map_extended[height+2][width+2];
    //unsigned char PMap[height][width];
    unsigned char** PMap = new unsigned char*[height];
	for(int i=0; i<height; ++i){
        PMap[i] = new unsigned char[width];
	}
	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(OutputImage, sizeof(unsigned char), height*width*BytesPerPixel, file);
	fclose(file);

	for(int i=0;i<height;++i){
        for(int j=0; j<width; ++j){
            if(OutputImage[i][j][0] < 128){
                OutputImage[i][j][0] = 0;
            }
            else{
                OutputImage[i][j][0] = 255;
            }
        }
    }
 //   cout<<"Hi"<<endl;

    bool flag=false;
    int x,m,p,g,k;
    int count=0;
    //while(!flag){
    for(int c=0; c<30; ++c){
        count+=1;
        for(int i=0;i<height;++i){
            for(int j=0; j<width; ++j){
                Imagedata[i][j][0] = OutputImage[i][j][0];
            }
        }

        for(int i=0; i<width+2;++i){
            Reimage[0][i][0] = 0;
            Reimage[height+1][i][0] = 0;
        }

        for(int i=0;i<height+2;++i){
            Reimage[i][0][0] = 0;
            Reimage[i][width+1][0] = 0;
        }

        for(int i=0;i<height; ++i){
            for(int j=0; j<width;++j){
                Reimage[i+1][j+1][0] = Imagedata[i][j][0];
            }
        }

        for(int i=1;i<=height;++i){
            for(int j=1;j<=width;++j){
                mask[0] = Reimage[i][j][0];
                mask[1] = Reimage[i][j+1][0];
                mask[2] = Reimage[i-1][j+1][0];
                mask[3] = Reimage[i-1][j][0];
                mask[4] = Reimage[i-1][j-1][0];
                mask[5] = Reimage[i][j-1][0];
                mask[6] = Reimage[i+1][j-1][0];
                mask[7] = Reimage[i+1][j][0];
                mask[8] = Reimage[i+1][j+1][0];
                Map[i-1][j-1] = find_thin(mask);
            }
        }

        for(int i=0; i<width+2;++i){
            Map_extended[0][i] = 0;
            Map_extended[height+1][i] = 0;
        }

        for(int i=0;i<height+2;++i){
            Map_extended[i][0] = 0;
            Map_extended[i][width+1] = 0;
        }

        for(int i=0;i<height; ++i){
            for(int j=0; j<width;++j){
                Map_extended[i+1][j+1] = Map[i][j];
            }
        }

        for(int i=1;i<=height;++i){
            for(int j=1;j<=width;++j){
                mask[0] = Map_extended[i-1][j-1];
                mask[1] = Map_extended[i-1][j];
                mask[2] = Map_extended[i-1][j+1];
                mask[3] = Map_extended[i][j-1];
                mask[4] = Map_extended[i][j];
                mask[5] = Map_extended[i][j+1];
                mask[6] = Map_extended[i+1][j-1];
                mask[7] = Map_extended[i+1][j];
                mask[8] = Map_extended[i+1][j+1];
                PMap[i-1][j-1] = find_pattern(mask);
            }
        }

        for(int i=0; i< height; ++i){
            for(int j=0; j<width; ++j){
                if(Imagedata[i][j][0] == 255){
                    x=1;
                }
                else{
                    x=0;
                }
                m = Map[i][j];
                p = PMap[i][j];
                g = x && ((!m) || p);
                OutputImage[i][j][0] = (unsigned char) (g*255);
                //if(g==1){
                  //  OutputImage[i][j][0] = 255;
                //}
                //else{
                  //  OutputImage[i][j][0] = 0;
                //}
            }
        }
        k=0;
        for(int i=0;i<height;++i){
            for(int j=0;j<width; ++j){
                if(OutputImage[i][j][0]!=Imagedata[i][j][0]){
                    k=1;
                    break;
                }
            }
            if(k==1){
                break;
            }
        }
    }



	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] <<endl;
		exit(1);
	}
	fwrite(OutputImage, sizeof(unsigned char), height*width*BytesPerPixel, file);
	fclose(file);

	cout<<"written"<<endl;
    cout<<count<<endl;

	return 0;
}