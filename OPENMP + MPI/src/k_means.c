
#include <stdio.h>
#include <stdlib.h>
#include<omp.h>
#include <unistd.h>
#include "../include/utils.h"
#include <mpi.h>
#include <stddef.h>

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


void assignsCluster (point * points, int chunkSize, cluster * clusters, int *points_cluster) {
    
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
    for(int i = 0; i < chunkSize; i++) {

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

    
}

int main(int argc, char ** argv){


    point * points;
    cluster * clusters;
    int * points_cluster;
    point * centroids;

    N = atoi(argv[1]);
    K = atoi(argv[2]);

    if(argc == 3){
       N_THREADS = 1;
    }else{
        N_THREADS = atoi(argv[3]);
    }
    
    // MPI

    int rank, nProc;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size (MPI_COMM_WORLD,&nProc); // Find out number of processes
    MPI_Comm_rank( MPI_COMM_WORLD, &rank ); // gets this process rank
  

    const int nitems=2;
    int          blocklengths[2] = {1,1};
    MPI_Datatype types[2] = {MPI_FLOAT, MPI_FLOAT};
    MPI_Datatype mpi_point_type;
    MPI_Aint     offsets[2];

    offsets[0] = offsetof(point, x);
    offsets[1] = offsetof(point, y);

    MPI_Type_create_struct(nitems, blocklengths, offsets, types, &mpi_point_type);
    MPI_Type_commit(&mpi_point_type);

     //alloc

    points = (point *) malloc(sizeof(point) * N);
    clusters = (cluster *) malloc(sizeof(cluster) * K);
    centroids = (point *) malloc(sizeof(point) * K);

    if(rank == 0){        
        //init
        init(points, clusters);
    }

    
    point * chunk_points = malloc(sizeof(point) * N/nProc);
    points_cluster = (int *) malloc(sizeof(cluster) * N/nProc);

    MPI_Scatter(points, N/nProc, mpi_point_type, chunk_points, N/nProc, mpi_point_type , 0, MPI_COMM_WORLD);

    int changed = 1;

    int it = 0;
       
    while(changed && it < 20){        
    
        for(int i = 0; i < K; i++){
            clusters[i].actual_size = 0;
            clusters[i].sum.x = 0;
            clusters[i].sum.y = 0;
            
            if(rank == 0){
                centroids[i] = clusters[i].centroid;
            }
            
        }

        MPI_Bcast(centroids, K, mpi_point_type , 0, MPI_COMM_WORLD);

        if(rank != 0){
            for(int i = 0; i < K; i++){
                clusters[i].centroid  = centroids[i];
            }
        }

        assignsCluster(chunk_points, N/nProc, clusters, points_cluster);

        point * calculatedSumGathered = NULL;
        int * calculatedSizeGathered = NULL;
        int * points_cluster_gathered = NULL;
        
        if (rank == 0) {
          calculatedSumGathered = malloc(sizeof(point) * nProc * K);
          calculatedSizeGathered = malloc(sizeof(int) * nProc * K);
          points_cluster_gathered = malloc(sizeof(int) * N);
        }


        point * calculatedSum =  malloc(sizeof(point) * K);
        int * calculatedSize =  malloc(sizeof(int) * K);
        

        for(int i = 0; i < K; i++){
            calculatedSum[i] = clusters[i].sum;
            calculatedSize[i] = clusters[i].actual_size;
        }

        MPI_Gather(calculatedSum, K, mpi_point_type, calculatedSumGathered, K, mpi_point_type, 0,MPI_COMM_WORLD);
        MPI_Gather(calculatedSize, K, MPI_INT, calculatedSizeGathered, K, MPI_INT, 0,MPI_COMM_WORLD);
        MPI_Gather(points_cluster, N/nProc, MPI_INT,points_cluster_gathered , N/nProc, MPI_INT, 0,MPI_COMM_WORLD);

        // Compute the centroid
        if (rank == 0) {
        
            for(int i = 0; i < K; i++){
                clusters[i].actual_size = 0;
                clusters[i].sum.x = 0;
                clusters[i].sum.y = 0;
            }


            for(int i = 0; i < K; i++){
                for(int j = 0; j < nProc; j++){
                    clusters[i].actual_size += calculatedSizeGathered[j * K + i];
                    clusters[i].sum.x += calculatedSumGathered[j * K + i].x; 
                    clusters[i].sum.y += calculatedSumGathered[j * K + i].y; 
                }        
            }

            //recalcula os vetores do cluster com o centroide

            for(int i = 0; i < K; i++){

                float novo_centroide_x = clusters[i].sum.x / clusters[i].actual_size;
                float novo_centroide_y = clusters[i].sum.y / clusters[i].actual_size;

                if(novo_centroide_x != clusters[i].centroid.x || novo_centroide_y != clusters[i].centroid.y){
                    clusters[i].centroid.x = novo_centroide_x;
                    clusters[i].centroid.y = novo_centroide_y;
                    changed = 1;
                 }
            } 

        }
            it++;
        }

      
    if(rank == 0){

        printf("N = %d, K = %d\n",N ,K);
    
        for(int j = 0; j < K; j++){
            printf("Center: (%.3f,%.3f) : Size: %ld\n",clusters[j].centroid.x,clusters[j].centroid.y,clusters[j].actual_size);
        }
        printf("Iterations: %d\n",it);
    }  


    MPI_Finalize();


    return 0;
      
     

}