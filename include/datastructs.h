#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H
#include <math.h>
#include <stdio.h>
typedef struct {
    double x;
    double y;
    double z;
} Vector3 ;

/*double getVector3x(Vector3 v);
double getVector3y(Vector3 v);
double getVector3z(Vector3 v);*/
double length(Vector3 v);
double length_squared(Vector3 v);

Vector3 addVector3(Vector3 *v, Vector3* w);
Vector3 subVector3(Vector3 *v, Vector3* w);
Vector3 multVector3(Vector3 *v, Vector3* w);
Vector3 multVector3const(Vector3 *v, double k);
Vector3 divideVector3(Vector3 *v, double k);

Vector3 unit_vector(Vector3 v);
void printfVector3(Vector3 v);
double vector_dot(const Vector3* u, const Vector3* v); 
#endif
