
#include <stdio.h>
#include <stdlib.h>




int N;
int K;


void init(float * points, float * centroid_cluster){

    srand(10);
    
    for(int i = 0; i < 2 * N; i = i + 2) {
        
        points[i] = (float) rand() / RAND_MAX;
        points[i + 1] = (float) rand() / RAND_MAX;
    }
    
    for(int j = 0; j < 2*K; j = j + 2) {
        centroid_cluster[j] = points[j];
        centroid_cluster[j+1] = points[j + 1];
    }
    

}



int assignsCluster (float * points, int * actual_size, float * sum_cluster, float * centroid_cluster,int * points_cluster) {
    

    for(int i = 0; i < 2 * N; i = i + 2) {

        int id_cluster = 0;
        float distance_near = ((centroid_cluster[0]-points[i])*(centroid_cluster[0]-points[i])) + ((centroid_cluster[1]-points[i+1])*(centroid_cluster[1]-points[i+1]));
        float distance_aux;
        for( int j = 2; j < 2 * K; j= j + 2){
            distance_aux = ((centroid_cluster[j]-points[i])*(centroid_cluster[j]-points[i])) + ((centroid_cluster[j+1]-points[i+1])*(centroid_cluster[j+1]-points[i+1]));
            if (distance_aux < distance_near) {
                distance_near = distance_aux;
                id_cluster = j;
            }
        }

        // aqui da em id cluster *2 por exemplo se for o cluster 1 da 2 pq o j ta 2 se for o cluster 2 da 4 etc

        sum_cluster[id_cluster] += points[i];
        sum_cluster[id_cluster+1] += points[i+1];
        actual_size[(id_cluster/2)] += 1;
        points_cluster[i/2] = id_cluster/2;

    }



    // recalculate cluster
    int changed = 0;

    for(int i = 0; i < 2 * K; i= i + 2){

        float novo_centroide_x = sum_cluster[i] / actual_size[(i/2)];
        float novo_centroide_y = sum_cluster[i+1] / actual_size[(i/2)];

    
        if(novo_centroide_x != centroid_cluster[i] || novo_centroide_y != centroid_cluster[i+1]){
            centroid_cluster[i] = novo_centroide_x;
            centroid_cluster[i+1] = novo_centroide_y;
            changed = 1;
         }


    } 

    return changed;
}


//recalcula os vetores do cluster com o centroide

int recalculateClusters(int * actual_size, float * sum_cluster, float * centroid_cluster){

    int changed = 0;

    for(int i = 0; i < 2 * K; i= i + 2){

        float novo_centroide_x = sum_cluster[i] / actual_size[(i/2)];
        float novo_centroide_y = sum_cluster[i+1] / actual_size[(i/2)];

        if(novo_centroide_x != centroid_cluster[i] || novo_centroide_y != centroid_cluster[i+1]){
            centroid_cluster[i] = novo_centroide_x;
            centroid_cluster[i+1] = novo_centroide_y;
            changed = 1;
         }


    } 

    return changed;
}



int main(int argc, char ** argv){

    N = atoi(argv[1]);
    K = atoi(argv[2]);

    float * points;
    int * actual_size;
    float * sum_cluster;
    float * centroid_cluster;
    int * points_cluster;


    //alloc

    points = (float *) malloc(sizeof(float) * 2 * N);
    actual_size = (int *) malloc(sizeof(int) * K);
    sum_cluster = (float *) malloc(sizeof(float) * 2 * K);
    centroid_cluster = (float *) malloc(sizeof(float) * 2 * K);
    points_cluster = (int *) malloc(sizeof(int) * N);



    for(int i = 0; i < 2 * K; i+=2){
        actual_size[(i/2)] = 0;
        sum_cluster[i] = 0;
        sum_cluster[i+1] = 0;
    }
    
    //init

    init(points, centroid_cluster);


    //------------------------------------------------------------------------------------------------------------------


    int changed = assignsCluster(points, actual_size, sum_cluster, centroid_cluster,points_cluster);


    int it = 0;
       
    while(changed && it < 20){        
        for(int i = 0; i < 2*K; i= i +2){
        
        actual_size[i/2]= 0;
        sum_cluster[i] = 0;
        sum_cluster[i+1] = 0;

    }
    

        changed = assignsCluster(points, actual_size, sum_cluster, centroid_cluster,points_cluster);

        it++;

    }

        printf("N = %d, K = %d\n",N ,K);
    
        for(int j = 0; j < 2 * K; j = j + 2){
            printf("Center: (%.3f,%.3f) : Size: %d\n",centroid_cluster[j],centroid_cluster[j+1],actual_size[j/2]);
        }
        printf("Iterations: %d\n",it);

    return 1;

}