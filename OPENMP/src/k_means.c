
#include <stdio.h>
#include <stdlib.h>
#include<omp.h>
#include <unistd.h>
#include "../include/utils.h"

int N;
int K;
int N_THREADS;

void init(point * points, cluster * clusters){
    srand(10);
    
    for(int i = 0; i < N; i++) {
        points[i].x = (float) rand() / RAND_MAX;
        points[i].y = (float) rand() / RAND_MAX;
    }
    for(int i = 0; i < K; i++) {

        clusters[i].centroid = points[i];
    }
}


int assignsCluster (point * points, cluster * clusters, int *points_cluster) {
    
    #pragma omp parallel num_threads(N_THREADS)
    {

    //inicializar estruturas privadas

    int * actual_size_private = (int *) malloc(sizeof(int) * K);
    point * sum_cluster_private = (point *) malloc(sizeof(point) * K);

    for(int i = 0; i < K; i++){
        
        sum_cluster_private[i].x = 0;
        sum_cluster_private[i].y = 0;
        actual_size_private[i] = 0;
    }

    #pragma omp for 
    for(int i = 0; i <  N; i++) {

        int id_cluster = 0;
        float distance_near = ((clusters[0].centroid.x-points[i].x)*(clusters[0].centroid.x-points[i].x)) + ((clusters[0].centroid.y-points[i].y)*(clusters[0].centroid.y-points[i].y));
        float distance_aux;
        
        for( int j = 1; j < K; j++){
            distance_aux = ((clusters[j].centroid.x-points[i].x)*(clusters[j].centroid.x-points[i].x)) + ((clusters[j].centroid.y-points[i].y)*(clusters[j].centroid.y-points[i].y));
            if (distance_aux < distance_near) {
                distance_near = distance_aux;
                id_cluster = j;
            }
        }

        // aqui da em id cluster *2 por exemplo se for o cluster 1 da 2 pq o j ta 2 se for o cluster 2 da 4 etc
        //COMO OS ARRAYS PRIVADOS INICIALIZAM A ZERO O PONTO 5001 NÃO É SOMADO AO 5000 O QUE FAZ COM QUE O RESULTADO VARIE POR CAUSA DOS ARREDONDAMENTOS

        sum_cluster_private[id_cluster].x += points[i].x;
        sum_cluster_private[id_cluster].y += points[i].y;
        actual_size_private[id_cluster] += 1;
        points_cluster[i] = id_cluster;

    }
  
        #pragma omp critical
        {   
            for(int i = 0; i < K; i++){
                
                clusters[i].sum.x += sum_cluster_private[i].x;
                clusters[i].sum.y += sum_cluster_private[i].y;
                clusters[i].actual_size += actual_size_private[i];
            }
        }
    }

    //recalcula os vetores do cluster com o centroide

    int changed = 0;

    for(int i = 0; i < K; i++){

        float novo_centroide_x = clusters[i].sum.x / clusters[i].actual_size;
        float novo_centroide_y = clusters[i].sum.y / clusters[i].actual_size;

        if(novo_centroide_x != clusters[i].centroid.x || novo_centroide_y != clusters[i].centroid.y){
            clusters[i].centroid.x = novo_centroide_x;
            clusters[i].centroid.y = novo_centroide_y;
            changed = 1;
         }
    } 

    return changed;
}

int main(int argc, char ** argv){

    
    N = atoi(argv[1]);
    K = atoi(argv[2]);

    if(argc == 3){
       N_THREADS = 1;
    }else{
        N_THREADS = atoi(argv[3]);
    }
    
    point * points;
    cluster * clusters;
    int * points_cluster;
    
    //alloc

    points = (point *) malloc(sizeof(point) * N);
    clusters = (cluster *) malloc(sizeof(cluster) * K);
    points_cluster = (int *) malloc(sizeof(cluster) * N);
   
    for(int i = 0; i < K; i++){
        clusters[i].actual_size = 0;
        clusters[i].sum.x = 0;
        clusters[i].sum.y = 0;

    }
    
    //init

    init(points, clusters);

    //------------------------------------------------------------------------------------------------------------------
    if(argc == 3){

    }
    int changed = assignsCluster(points, clusters,points_cluster);


    int it = 0;
       
    while(changed && it < 20){        
    
        for(int i = 0; i < K; i++){
        clusters[i].actual_size = 0;
        clusters[i].sum.x = 0;
        clusters[i].sum.y = 0;

        }
        changed = assignsCluster(points, clusters, points_cluster);

        it++;
    }

      printf("N = %d, K = %d\n",N ,K);
    
        for(int j = 0; j < K; j++){
            printf("Center: (%.3f,%.3f) : Size: %ld\n",clusters[j].centroid.x,clusters[j].centroid.y,clusters[j].actual_size);
        }
        printf("Iterations: %d\n",it);

      
    return 0;

}