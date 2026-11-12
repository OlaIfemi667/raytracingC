#include "../include/datastructs.h"
#include <stdio.h>



/*double getVector3x(Vector3 v)
{
    return v.x;
}

double getVector3y(Vector3 v)
{
    return v.y;
}
double getVector3z(Vector3 v)
{
    return v.z;
}*/

Vector3 addVector3(Vector3 *v, Vector3* w)
{
    return (Vector3){
        .x = v->x + w->x,
        .y = v->y + w->y,
        .z = v->z + w->z
    };
}
Vector3 subVector3(Vector3 *v, Vector3* w)
{
    return  (Vector3){
        .x = v->x - w->x,
        .y = v->y - w->y,
        .z = v->z - w->z
    };
}
Vector3 multVector3(Vector3 *v, Vector3 *w)
{
    return  (Vector3){
        .x = v->x * w->x,
        .y = v->y * w->y,
        .z = v->z * w->z
    };
}

Vector3 multVector3const(Vector3 *v, double k)
{
    
    return (Vector3){
        .x = v->x * k,
        .y = v->y * k,
        .z = v->z * k
    };
}

Vector3 divideVector3(Vector3 *v, double k)
{
    return  (Vector3){
        .x = v->x / k,
        .y = v->y / k,
        .z = v->z / k
    };
}

void printfVector3(Vector3 v)
{
    printf("{%f, %f, %f}", v.x, v.y, v.z);
}

double length(Vector3 v){
        return sqrt(length_squared(v));
}

double length_squared(Vector3 v){
        return v.x*v.x + v.y*v.y + v.z*v.z;
}

Vector3 unit_vector(Vector3 v) {
    return divideVector3(&v, length(v));
}
double vector_dot(const Vector3* u, const Vector3* v) {
    return u->x * v->x
         + u->y * v->y
         + u->z * v->z;
}

