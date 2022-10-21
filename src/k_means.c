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


    for(int i = 0; i < K; i++){
        cluster_points[i] = NULL;
    }
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

        
        llist *aux = &cluster_points[i];

        while(*aux){
            
        
            int id_cluster = 0;
            float distance_near = euclideanDistance((*aux)->value,clusters[0]);
            float distance_aux;
            for (int j=1; j < K; j++){
                distance_aux = euclideanDistance((*aux)->value,clusters[j]);
                if (distance_aux < distance_near) {
                    distance_near = distance_aux;
                    id_cluster = j;
                }
            }
            if (id_cluster != i) {
                appendL(&cluster_points[id_cluster],(*aux)->value);
                deleteL(aux);  

                //printf("moved from %d to %d\n",i,id_cluster);
            }else{
                aux = &((*aux)->next);
            }

        
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
            clusters[i] = comparator;
            changed = 1;
         }


       // printf("centroid : %f %f\n",clusters[i].x,clusters[i].y);
    } 

    return changed;
}



int main(){

     alloc();
     init();



     assignsCluster();

     int changed = 1;
     int i = 0;

     while(changed ){
        
        changed = recalculateClusters();    
        i++;
        printf("%d\n",i);
        
        reAssignsCluster(); 


        // for(int i = 0; i < K; i++){

        // printList(cluster_points[i]);
        // printf("\n\n\n\n\n\n"); 
           
        // }


        

    }


    printf("N = %d, K = %d\n",N ,K);
    
    for(int i = 0; i < K; i++){
        printf("Center: (%f,%f) : Size: %ld\n",clusters[i].x,clusters[i].y,listSize(cluster_points[i]));
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