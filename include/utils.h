#ifndef UTILS
#define UTILS


#include <stdio.h>
#include <stdlib.h>


typedef struct Vector {       
    float x;
    float y;
} vector;


float euclideanDistance(vector a, vector b);
vector centroidCalculator(vector * points, int size);


#endif