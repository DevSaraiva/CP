#include "../include/utils.h"


#define N 10000000
#define K 4


vector * points;
vector * clusters;


void alloc(){
    points = (vector *) malloc(sizeof(vector) * N);
    clusters = (vector *) malloc(sizeof(vector) * K);
}


void init(){

    srand(10);
    
    for(int i = 0; i < N; i++) {
        
        points[i].x = (float) rand() / RAND_MAX;
        points[i].y = (float) rand() / RAND_MAX;
    }
    for(int i = 0; i < K; i++) {
        clusters[i].x = points[i].x;
        clusters[i].y = points[i].y;
    }

}



int main(){

    alloc();
    init();
    printf("ola");



}