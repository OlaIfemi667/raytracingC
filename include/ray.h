#ifndef RAY_H
#define RAY_H
#include "../include/datastructs.h"

typedef Vector3 Point3;

typedef struct
{
    Point3 origin;
    Vector3 direction;
} Ray;

Point3 rayAt(Ray ray, double t) 
{
    Point3 part_1 =  multVector3const(&ray.direction, t);
    return addVector3(&ray.origin, &part_1);
}

#endif
