#ifndef UTILS
#define UTILS


#include <stdio.h>
#include <stdlib.h>




#define N 10000000
#define K 4


typedef struct Vector {       
    float x;
    float y;
} vector;


typedef struct Cluster {       
    
    size_t max_size;
    size_t actual_size;
    vector centroid;
    vector * points;
} cluster;






float euclideanDistance(vector a, vector b);
vector centroidCalculator(cluster cluster);
void add_cluster(vector v, cluster * c);
void freeClusterPoints(cluster * clusters);
void printPoints(vector * points);
void resetClustersSize(cluster * clusters);


#endif