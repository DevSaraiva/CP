#include "../include/utils.h"

float euclideanDistance(vector a, vector b){

    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return ((dx*dx) + (dy*dy));
}



vector centroidCalculator(vector * points){

    float xSum, ySum;
    xSum = 0;
    ySum = 0;

    int size = 0;

    for(int i = 0; i < N; i++){
        xSum += points[i].x;
        ySum += points[i].y;
        size++;

    }

    vector res;

    res.x =  xSum / size;
    res.y = ySum / size;

    return res;
}


