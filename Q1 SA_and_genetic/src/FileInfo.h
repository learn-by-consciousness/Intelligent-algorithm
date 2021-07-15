#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <math.h>
#include <stdlib.h>
using namespace std;

#include "parameter.h"



#ifdef DATASET0
#define FILENAME "../tc/a280.tsp"
#define BEST_FILENAME "../tc/a280.opt.tour"
#define OUTFILE "../result/ans.txt"
#define SIZE 280
#define PASSNUM 6
#define ANS_PASSNUM 4
#define INIT_RAND_TIME 100
#endif



#ifdef DATASET1
#define FILENAME "../tc/kroC100.tsp"
#define BEST_FILENAME "../tc/kroC100.opt.tour"
#define OUTFILE "../result/tcp.txt"
#define SIZE 100
#define PASSNUM 6
#define ANS_PASSNUM 4
#define INIT_RAND_TIME 100
#endif


struct point{
    int x,y;
};


typedef struct{
    int point[SIZE];
    double length;
}path;

double getDist(point A, point B);
void InitDist();
void calLength(path * p);
void showBest();
path getRandPath(path p);
path init();
void checkAnswer(path *p);
void saveFile(path *p);
void showPath(path *p);