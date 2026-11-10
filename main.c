#include "include/datastructs.h"
#include "include/colors.h"
#include "include/ray.h"
#include <stdio.h>

Color rayColor(Ray r)
{
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

    int width = 400;
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
