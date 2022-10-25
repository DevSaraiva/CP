#include "../include/utils.h"




void init(vector * points, cluster * clusters){

    srand(10);
    
    for(int i = 0; i < N; i++) {
        
        points[i].x = (float) rand() / RAND_MAX;
        points[i].y = (float) rand() / RAND_MAX;
    }
    for(int i = 0; i < K; i++) {

        clusters[i].centroid = points[i];
    }
    

}

void assignsCluster (vector * points, cluster * clusters) {
    
    for(int i = 0; i < N; i++) {

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

        if(clusters[id_cluster].max_size == clusters[id_cluster].actual_size){
            clusters[id_cluster].max_size = 1.2 * clusters[id_cluster].max_size;
            clusters[id_cluster].points = realloc(clusters[id_cluster].points,sizeof(vector) * clusters[id_cluster].max_size);
        }

        clusters[id_cluster].points[clusters[id_cluster].actual_size] = points[i];
        clusters[id_cluster].actual_size =  clusters[id_cluster].actual_size + 1;

    }
}


//recalcula os vetores do cluster com o centroide

int recalculateClusters(cluster * clusters){

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

    vector * points;
    cluster * clusters;


    //alloc

    points = (vector *) malloc(sizeof(vector) * N);
    clusters = (cluster *) malloc(sizeof(cluster) * K);

    for(int i = 0; i < K; i++){
        clusters[i].max_size = N/K;
        clusters[i].actual_size = 0;
        clusters[i].points = malloc(sizeof(vector)*clusters[i].max_size);

    }
    
    //init

    init(points,clusters);


    //------------------------------------------------------------------------------------------------------------------


    assignsCluster(points, clusters);

    int i = 0;


    int changed = recalculateClusters(clusters);  
       
    while(changed){
        
        resetClustersSize(clusters);
        assignsCluster(points, clusters);

        i++;
        changed = recalculateClusters(clusters);

    }

        printf("N = %d, K = %d\n",N ,K);
    
        for(int i = 0; i < K; i++){
            printf("Center: (%.3f,%.3f) : Size: %ld\n",clusters[i].centroid.x,clusters[i].centroid.y,clusters[i].actual_size);
        }
        printf("Iterations: %d\n",i);

    return 1;

}