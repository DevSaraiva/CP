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
        struct Llist *next;
} *llist;

float euclideanDistance(vector a, vector b);
vector centroidCalculator(llist points);
void deleteL (llist *l);
void appendL(llist *l, vector value);
void printList(llist l);
size_t listSize(llist l);

#endif