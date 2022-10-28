#include "../include/utils.h"





float euclideanDistance(float x, float y, float x1 , float y1){

    float dx =  x1 - x;
    float dy = y1 - y;
    return ((dx*dx) + (dy*dy));
}

/*
vector centroidCalculator(cluster cluster){

    vector res;

    res.x =  cluster.xSum / cluster.actual_size;
    res.y =  cluster.ySum / cluster.actual_size;

    return res;
}
*/

void resetClustersSize(int * actual_size,float * sum_cluster){
    
    for(int i = 0; i < 2*K; i= i +2){
        
        actual_size[i/2]= 0;
        sum_cluster[i] = 0;
        sum_cluster[i+1] = 0;

    }
    
}

/*
void printPoints(vector * points){
    
    for(int i = 0; i < N; i++){

        printf("%f %f \n",points[i].x,points[i].y);


    }
}
*/