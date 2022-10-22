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

    float size = 0.0f;

    for(int i = 0; i < cluster.actual_size; i++){
        
        xSum += cluster.points[i].x;
        ySum += cluster.points[i].y;
        size++;

    }

    vector res;

    res.x =  xSum / size;
    res.y = ySum / size;



    return res;
}


void add_cluster(vector v, cluster * c){

    if(c->max_size == c->actual_size){
        c->max_size = 1.2 * c->max_size;
        c->points = realloc(c->points,sizeof(vector) * c->max_size);
    }


   

    c->points[c->actual_size] = v;
    c->actual_size = c->actual_size + 1;


}



void allocClusterPoints(cluster * clusters){

     for(int i = 0; i < K; i++){
        clusters[i].max_size = N/K;
        clusters[i].actual_size = 0;
        clusters[i].points = malloc(sizeof(vector)*clusters[i].max_size);

    }

}



void freeClusterPoints(cluster * clusters){

    for(int i = 0; i < K; i++){
        free(clusters[i].points); 
    }

}



void printPoints(vector * points){
    
    for(int i = 0; i < N; i++){

        printf("%f %f \n",points[i].x,points[i].y);


    }
}