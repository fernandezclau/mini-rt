#ifndef VIEW_H
#define VIEW_H

#include "./minirt.h"

typedef struct camera
{  
    vector3 position;
    vector3 direction;
    float   fov;
}           camera;

typedef struct ray
{
    vector3 origin;
    vector3 direction;
}           ray;

typedef struct ambient_light
{
    float   ratio;
    color color;
}           ambient_light;

typedef struct light
{
    vector3 position;
    float   brightness;
    color   color;
}           light;

typedef struct hit
{
    float   dist;
    float   min_dist;
    int     intersect;
    color   final_color;
}               hit;


// INIT
void    init_camera(camera *c);
void    init_light(light *l);
void    init_ambient_light(ambient_light *al);
void    init_hit_point(hit   *hit);
vector3 compute_direction(int x, int y, float fov);

// LIGHT
void    calculate_ambient_light(color *color, ambient_light light);



#endif // VIEW_H