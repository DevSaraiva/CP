#ifndef UTILS
#define UTILS


#include <stdio.h>
#include <stdlib.h>




typedef struct Point {       
    float x;
    float y;
} point;


typedef struct Cluster {       
    
    size_t actual_size;
    point centroid;
    point sum;
    
} cluster;



#endif