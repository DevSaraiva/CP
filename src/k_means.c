#include "../include/utils.h"


#define N 10000000
#define K 4


vector * points;
vector * clusters;
llist * cluster_points;

void alloc(){
    points = (vector *) malloc(sizeof(vector) * N);
    clusters = (vector *) malloc(sizeof(vector) * K);
    cluster_points = (llist *) malloc(sizeof(struct Llist) * K);
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

        int id_cluster = 0;
        float distance_near = euclideanDistance(points[i],clusters[0]);
        float distance_aux;
        for (int j=1; j < K; j++){
            distance_aux = euclideanDistance(points[i],clusters[j]);
            if (distance_aux < distance_near) {
                distance_near = distance_aux;
                id_cluster = j;
            }
        }

        // aqui temos o indice do cluster mais proximo do ponto

        appendL(&cluster_points[id_cluster],points[i]);
    }
}


void reAssignsCluster () {
    // percorre a lista ligada de cada cluster
    for(int i = 0; i < K; i++) {

        llist aux = cluster_points[i];
        while(aux){
            
            int id_cluster = 0;
            float distance_near = euclideanDistance(aux->value,clusters[0]);
            float distance_aux;
            for (int j=1; j < K; j++){
                distance_aux = euclideanDistance(aux->value,clusters[j]);
                if (distance_aux < distance_near) {
                    distance_near = distance_aux;
                    id_cluster = j;
                }
            }
            if (id_cluster != i) {
                appendL(&cluster_points[id_cluster],aux->value);
                deleteL(&(aux));
            }

            aux = aux->next;
        }
    
    }
}

//recalcula os vetores do cluster com o centroide

int recalculateClusters(){

    int changed = 0;

    //testar if para evitar comparação de inteiros

    for(int i = 0; i < K; i++){

        vector comparator = centroidCalculator(cluster_points[i]);

         if(comparator.x != clusters[i].x || comparator.y != clusters[i].y){
            clusters[i] = centroidCalculator(cluster_points[i]);
            changed = 1;
         }

    } 

    return changed;
}



int main(){

    alloc();
    init();
    assignsCluster();

    int changed = 1;
    int i = 0;

    while(changed){

        changed = recalculateClusters();
        reAssignsCluster();
        i++;
        printf("%d\n",i);
      

    }


    
    return 1;

    // for(int i = 0; i < K; i++){
    //     printList(cluster_points[i]);
    // }


}