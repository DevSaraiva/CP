#include "../include/utils.h"

float euclideanDistance(vector a, vector b){
   float dx = a.x - b.x;
   float dy = a.y - b.y;
   return ((dx*dx) + (dy*dy))
}