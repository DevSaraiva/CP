#include "../include/utils.h"



vector * points;
cluster * clusters;


void alloc(){

    points = (vector *) malloc(sizeof(vector) * N);
    clusters = (cluster *) malloc(sizeof(cluster) * K);

    allocClusterPoints(clusters);
    
}

void init(){

    srand(10);
    
    for(int i = 0; i < N; i++) {
        
        points[i].x = (float) rand() / RAND_MAX;
        points[i].y = (float) rand() / RAND_MAX;
    }
    for(int i = 0; i < K; i++) {

        clusters[i].centroid = points[i];
    }
    

}

void assignsCluster () {
    
    int i = 0;
    for(i; i < N - 4; i = i + 5) {

        //loop unrolling

        int id_cluster = 0;
        float distance_near = euclideanDistance(points[i],clusters[0].centroid);
        float distance_aux;
        for (int j=1; j < K; j++){
            distance_aux = euclideanDistance(points[i],clusters[j].centroid);
            if (distance_aux < distance_near) {
                distance_near = distance_aux;
                id_cluster = j;
            }
        }

        // aqui temos o indice do cluster mais proximo do ponto

        add_cluster(points[i],&clusters[id_cluster]);

        id_cluster = 0;
        distance_near = euclideanDistance(points[i + 1],clusters[0].centroid);
        for (int j=1; j < K; j++){
            distance_aux = euclideanDistance(points[i + 1],clusters[j].centroid);
            if (distance_aux < distance_near) {
                distance_near = distance_aux;
                id_cluster = j;
            }
        }

        // aqui temos o indice do cluster mais proximo do ponto

        add_cluster(points[i + 1],&clusters[id_cluster]);


        id_cluster = 0;
        distance_near = euclideanDistance(points[i + 2],clusters[0].centroid);
        for (int j=1; j < K; j++){
            distance_aux = euclideanDistance(points[i + 2],clusters[j].centroid);
            if (distance_aux < distance_near) {
                distance_near = distance_aux;
                id_cluster = j;
            }
        }

        // aqui temos o indice do cluster mais proximo do ponto

        add_cluster(points[i + 2],&clusters[id_cluster]);



        id_cluster = 0;
        distance_near = euclideanDistance(points[i + 3],clusters[0].centroid);
        for (int j=1; j < K; j++){
            distance_aux = euclideanDistance(points[i + 3],clusters[j].centroid);
            if (distance_aux < distance_near) {
                distance_near = distance_aux;
                id_cluster = j;
            }
        }

        // aqui temos o indice do cluster mais proximo do ponto

        add_cluster(points[i + 3],&clusters[id_cluster]);




        id_cluster = 0;
        distance_near = euclideanDistance(points[i + 4],clusters[0].centroid);
        for (int j=1; j < K; j++){
            distance_aux = euclideanDistance(points[i + 4],clusters[j].centroid);
            if (distance_aux < distance_near) {
                distance_near = distance_aux;
                id_cluster = j;
            }
        }

        // aqui temos o indice do cluster mais proximo do ponto

        add_cluster(points[i + 4],&clusters[id_cluster]);

    }

    for(i; i<N;i++){

        int id_cluster = 0;
        float distance_near = euclideanDistance(points[i],clusters[0].centroid);
        float distance_aux;
        for (int j=1; j < K; j++){
            distance_aux = euclideanDistance(points[i],clusters[j].centroid);
            if (distance_aux < distance_near) {
                distance_near = distance_aux;
                id_cluster = j;
            }
        }

        // aqui temos o indice do cluster mais proximo do ponto

        add_cluster(points[i],&clusters[id_cluster]);

    }

  
}


//recalcula os vetores do cluster com o centroide

int recalculateClusters(){

    int changed = 0;

    //testar if para evitar comparação de inteiros

    for(int i = 0; i < K; i++){

        vector comparator = centroidCalculator(clusters[i]);

        if(comparator.x != clusters[i].centroid.x || comparator.y != clusters[i].centroid.y){
            clusters[i].centroid = comparator;
            changed = 1;
         }


    } 

    return changed;
}



int main(){

    alloc();
    init();
    assignsCluster();

    int i = 0;


    int changed = recalculateClusters();  
       
     while(changed){
        
        allocClusterPoints(clusters);
        assignsCluster();

        i++;
        changed = recalculateClusters();

    }


        printf("N = %d, K = %d\n",N ,K);
    
        for(int i = 0; i < K; i++){
            printf("Center: (%.3f,%.3f) : Size: %ld\n",clusters[i].centroid.x,clusters[i].centroid.y,clusters[i].actual_size);
        }
        printf("Iterations: %d\n",i);



    
    return 1;

  


}