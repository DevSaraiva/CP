#ifndef UTILS
#define UTILS


#include <stdio.h>
#include <stdlib.h>



typedef struct Vector {       
    float x;
    float y;
} vector;


typedef struct Lligada {
        vector valor;
        struct lligada *prox;
} *lligada;

float euclideanDistance(vector a, vector b);
vector centroidCalculator(vector * points, int size);
void deleteHead (lligada l);

#endif