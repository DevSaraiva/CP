#include "../include/utils.h"

float euclideanDistance(vector a, vector b){

    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return ((dx*dx) + (dy*dy));
}



vector centroidCalculator(vector * points, int size){

    float xSum, ySum;
    xSum = 0;
    ySum = 0;

    for(int i = 0; i < size; i++){
        xSum += points[i].x;
        ySum += points[i].y;
    }

    vector res;
    res.x =  xSum / size;
    res.y = ySum / size;

    return res;
}


// da delete a cabeca do l
void deleteL (llist *l){
    llist temp = (*l);
	(*l) = (*l)->next;
	free(temp);
}

// adiciona à cabeça da lista
void appendL(llist * l, vector value){
    llist aux = (llist) malloc(sizeof(struct Llist));
    aux->value = value;
    aux->next = (*l);
    *l = aux;
}


void printList(llist l){
    while(l!= NULL){
        printf("%f %f \n",l->value.x,l->value.y);
        l = l -> next;
    }
}
