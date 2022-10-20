#ifndef UTILS
#define UTILS


#include <stdio.h>
#include <stdlib.h>


typedef struct Vector {       
    float x;
    float y;
} vector;


typedef struct Llist {
        vector value;
        struct llist *next;
} *llist;

float euclideanDistance(vector a, vector b);
vector centroidCalculator(vector * points, int size);
void deleteL (llist l,llist prev);

#endif