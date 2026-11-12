#include "include/datastructs.h"
#include "include/colors.h"
#include "include/ray.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>



bool hitSquare(Point3* coordA, Point3* coordB, Point3* coordD, Ray *r)
{
    return  (r->direction.y <= coordA->y) &
            (r->direction.y >= coordD->y) &
            (r->direction.x <= coordB->x) &
            (r->direction.x >= coordA->x) &
            (r->direction.z <= 1);
}



double hit_sphere(Point3* center, double radius, Ray* r) {
    Vector3 oc = subVector3(center, &r->origin);
    double a = vector_dot(&r->direction, &r->direction);

    double b = -2.0 * vector_dot(&r->direction, &oc);
    double c = vector_dot(&oc, &oc) - radius*radius;
    double discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - sqrt(discriminant) ) / (2.0*a);
    }
}



Color rayColor(Ray r)
{
    Point3 p_part1 = {0,0,-1};
    double t = hit_sphere(&p_part1, 0.5, &r);
    if (t > 0.0) {
        Point3 p_part2 = rayAt(r, t); 
        Vector3 w = (Vector3){0, 0, -1};
        Vector3 N_part1 = subVector3(&p_part2, &w);
        Vector3 N = unit_vector(N_part1);
        Vector3 final = (Color){N.x+1, N.y+1, N.z+1};
        Vector3 to_return = multVector3const(&final , 0.5);
        return to_return;
    }


    if (hitSquare(&(Point3){0.5, 0.5, 1},
                  &(Point3){1, 0.5, 1},
                  &(Point3){0.5, 0, 1}, &r))
        return (Color){0, 0, 1.0};

    Color start = {1.0, 1.0, 1.0};
    Color end = {0.5, 0.7, 1.0};

    Vector3 unit_direction = unit_vector(r.direction);
    double a = 0.5*(unit_direction.y + 1.0);

    Vector3 part_1 = multVector3const(&start, (1.0-a));
    Vector3 part_2 = multVector3const(&end, a);
    return addVector3(
        &part_1,
        &part_2
    );
}


int main(void)
{

    /*Vector3 position = {
        .x = 50,
        .y = 100,
        .z = 200,
    };

    multVector3const(&position, 6);
    printfVector3(position);*/
    
    float aspect_ratio = 16.0 / 9.0;

    int width = 1600;
    // Calcule de height et s'assurer qu'il des différents de zéro
    
    int height = (int)(width / aspect_ratio);
    height = (height < 1) ? 1: height;

    // Camera

    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * ((double)width/height);
    Point3 camera_center = {0};

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    Vector3 viewport_u = {
                            .x = viewport_width,
                            .y = 0,
                            .z = 0
                        };
    Vector3 viewport_v = {
                            .x = 0,
                            .y = -viewport_height,
                            .z = 0
                        };


    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    Vector3 pixel_delta_u = divideVector3(&viewport_u, width);   
    Vector3 pixel_delta_v = divideVector3(&viewport_v, height);

    // Calculate the location of the upper left pixel.
    Vector3 vup_part1 = divideVector3(&viewport_u, 2);
    Vector3 vup_part2 = divideVector3(&viewport_v, 2);
    Vector3 vup_part3 = addVector3(&vup_part1, &vup_part2);
    Vector3 vup_part4 =  addVector3(&(Vector3){0, 0, focal_length}, &vup_part3);

    Vector3 viewport_upper_left = subVector3(&camera_center, &vup_part4);

    Vector3 pxi100_part1 = addVector3(&pixel_delta_u, &pixel_delta_v);
    Vector3 pxi100_part2 = multVector3const(&pxi100_part1,0.5);
    Vector3 pixel00_loc = addVector3(&viewport_upper_left, &pxi100_part2);


    printf("P3\n%d %d\n255\n", width, height);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Vector3 pc_part1 = multVector3const(&pixel_delta_v, i);
            Vector3 pc_part2 = multVector3const(&pixel_delta_u, j);
            Vector3 pc_part3 = addVector3(&pc_part1, &pc_part2); 

            Vector3 pixel_center = addVector3(&pixel00_loc, &pc_part3);

            Vector3 ray_direction = subVector3(&pixel_center, &camera_center);
            Ray r = {
                .origin = camera_center,
                .direction = ray_direction
            };

            Color pixel_color = rayColor(r);
            printfColor(pixel_color);
        }
    }
    return 0;
}
