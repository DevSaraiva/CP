#ifndef UTILS
#define UTILS


#include <stdio.h>
#include <stdlib.h>




#define N 10000000
#define K 4


/*

typedef struct Vector {       
    float x;
    float y;
} vector;


typedef struct Cluster {       
    
    size_t actual_size;
    float xSum;
    float ySum;
    vector centroid;

} cluster;

*/



float euclideanDistance(float x, float y, float x1, float y1);
//vector centroidCalculator(cluster cluster);
//void add_cluster(vector v, cluster * c);
//void freeClusterPoints(cluster * clusters);
//void printPoints(vector * points);
void resetClustersSize(int * actual_size,float * sum_cluster);


#endif