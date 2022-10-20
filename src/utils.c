#include "../include/utils.h"

float euclideanDistance(vector a, vector b){

    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return ((dx*dx) + (dy*dy));
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


// da free a cabeça e devolve a cauda
void deleteHead (lligada l){
    lligada aux = l;
    l = l->prox;
    free(aux);
}