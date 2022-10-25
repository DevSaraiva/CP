#include "../include/utils.h"
#include <math.h>

float euclideanDistance(vector a, vector b){

    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return ((dx*dx) + (dy*dy));
}



vector centroidCalculator(cluster cluster){

    float xSum, ySum;
    xSum = 0.0f;
    ySum = 0.0f;

    for(int i = 0; i < cluster.actual_size; i++){
        
        xSum += cluster.points[i].x;
        ySum += cluster.points[i].y;

    }

    vector res;

    res.x =  xSum / cluster.actual_size;
    res.y = ySum / cluster.actual_size;

    return res;
}


void freeClusterPoints(cluster * clusters){

    for(int i = 0; i < K; i++){
        free(clusters[i].points); 
    }
}


void resetClustersSize(cluster * clusters){
    
    for(int i = 0; i < K; i++){
        clusters[i].actual_size =  0;
    }
    
}



void printPoints(vector * points){
    
    for(int i = 0; i < N; i++){

        printf("%f %f \n",points[i].x,points[i].y);


    }
}