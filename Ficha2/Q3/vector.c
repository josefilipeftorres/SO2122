#include <stdio.h>
#include <math.h>
#include "vector.h"

// Implementação dos métodos da API

vector* vector_new(double x, double y, double z) {
    vector* v = (vector*) malloc(sizeof(vector));
    v->x = x;
    v->y = y;
    v->z = z;
    return v;
}

vector* vector_add(vector* v1, vector* v2) {
    return vector_new(v1->x+v2->x, v1->y+v2->y, v1->z+v2->z);
}

vector* vector_sub(vector* v1, vector* v2) {
    return vector_new(v1->x-v2->x, v1->y-v2->y, v1->z-v2->z);
}

vector* vector_scale(double k, vector* v) {
    return vector_new(v->x*k, v->y*k, v->z*k);
}

vector* vector_vprod(vector* v1, vector* v2) {
    return vector_new(v1->y*v2->z - v1->z*v2->y,
                      v1->z*v2->x - v1->x*v2->z,
                      v1->x*v2->y - v1->y*v2->x);
}

double vector_sprod(vector* v1, vector* v2) {
    return v1->x*v2->x + v1->y*v2->y + v1->z*v2->z;
}

double vector_mod(vector* v) {
    return sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
}