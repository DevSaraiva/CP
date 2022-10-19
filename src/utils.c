#include "../include/utils.h"

float euclideanDistance(vector a, vector b){
   
}



vector centroidCalculator(vector * points, int size){

    float xSum, ySum;
    xSum = 0;
    ySum = 0;

    for(int i = 0; i < size; i++){
        xSum += points[i].x;
        ySum += points[i].y;
    }

    vector res;
    res.x =  xSum / size;
    res.y = ySum / size;

    return res;
}