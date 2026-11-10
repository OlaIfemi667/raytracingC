#ifndef COLORS_H
#define COLORS_H
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include "../include/datastructs.h"
typedef Vector3 Color;


void printfColor(Color v)
{
    printf("%d %d %d\n", (int)(255.999 * v.x), (int)(255.999 * v.y), (int)(255.999 * v.z));
}

#endif
