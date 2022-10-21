#include "../include/utils.h"



vector * points;
cluster * clusters;


void alloc(){
    points = (vector *) malloc(sizeof(vector) * N);
    clusters = (cluster *) malloc(sizeof(cluster) * K);


    for(int i = 0; i < K; i++){
        clusters[i].max_size = N/K;
        clusters[i].actual_size = 0;
        clusters[i].points = malloc(sizeof(vector)*clusters[i].max_size);

    }


    
}

void init(){

    srand(10);
    
    for(int i = 0; i < N; i++) {
        
        points[i].x = (float) rand() / RAND_MAX;
        points[i].y = (float) rand() / RAND_MAX;
    }
    for(int i = 0; i < K; i++) {


        printf("%f %f\n",points[i].x,points[i].y);

        clusters[i].centroid = points[i];

        printf("%f %f\n",clusters[i].centroid.x,clusters[i].centroid.y);
    }
    

}

void assignsCluster () {
    

        
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



    int changed = recalculateClusters();  
      int i = 0;
       

     while(changed){
        
        allocClusterPoints(clusters);
        assignsCluster();

        i++;
        printf("%d\n",i);


        changed = recalculateClusters();

    }


    printf("N = %d, K = %d\n",N ,K);
    
    for(int i = 0; i < K; i++){
        printf("Center: (%f,%f) : Size: %ld\n",clusters[i].centroid.x,clusters[i].centroid.y,clusters[i].actual_size);
    }
    printf("Iterations: %d\n",i);





    // llist * lista = malloc(sizeof(struct Llist));
    // *lista = NULL;

    // vector a;
    // a.x = 1;
    // a.y = 2;

    // vector c;
    // c.x = 3;
    // c.y = 4;


    // vector d;
    // d.x = 5;
    // d.y = 6;


    // vector e;
    // e.x = 7;
    // e.y = 8;

    // appendL(lista,a);
    // appendL(lista,c);
    // appendL(lista,d);
    // appendL(lista,e);


    // vector res = centroidCalculator(*lista);

    // printf("%f %f\n",res.x,res.y);

    // while(*lista){
        

    //      deleteL(lista);

    //      //lista = &((*lista)->next);

    //      printList(*lista);

    //      printf("\n\n");
    // }


// N = 10000000, K = 4
// Center: (0.250, 0.750) : Size: 2499108
// Center: (0.250, 0.250) : Size: 2501256
// Center: (0.750, 0.250) : Size: 2499824
// Center: (0.750, 0.750) : Size: 2499812
// Iterations: 39

    
    return 1;

  


}