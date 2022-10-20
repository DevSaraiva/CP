#include "../include/utils.h"


#define N 10000000
#define K 4


vector * points;
vector * clusters;
llist * cluster_points;

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

void assignsCluster () {
    for(int i = 0; i < N; i++) {

        int ind_cluster_prox = 0;
        float distance_m_prox = euclideanDistance(points[i],clusters[0]);
        float distance_aux;
        for (int j=1; j < K; j++){
            distance_aux = euclideanDistance(points[i],clusters[j]);
            if (distance_aux < distance_m_prox) {
                distance_m_prox = distance_aux;
                ind_cluster_prox = j;
            }
        }
        // aqui temos o indice do cluster mais proximo do ponto

     
        // t
       
    }
}


int main(){

    // alloc();
    // init();



    llist a = NULL;
    vector b;
    b.x = 1;
    b.y = 2;
    vector c;
    c.x = 3;
    c.y = 4;
    appendL(&a,b);

    appendL(&a,c);



   printList(a);


   deleteL(a->next,a);

      printList(a);




   



}