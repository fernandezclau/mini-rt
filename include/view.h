#ifndef VIEW_H
#define VIEW_H

#include "./minirt.h"

typedef struct camera
{  
    vector3 position;
    vector3 direction;
    float   fov;
    vector3 identity[3];
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
    struct light   *next;
}           light;

typedef struct hit
{
    float   dist;
    float   min_dist;
    int     intersect;
    color   final_color;
    vector3 position;
    vector3 normal;
    int     reflection;
}               hit;


// CAMERA
void compute_camera_basis(camera *cam);
vector3 compute_ray_direction(int x, int y, float fov, camera *cam);

// LIGHT
color calculate_ambient_light(ambient_light light);

// AMBIENT LIGHT

// INITIALIZATION
void    init_camera(camera *c);
void    init_light(light *l);
void    init_ambient_light(ambient_light *al);
void    init_hit_point(hit   *hit);

// LIST
void    add_light(light **head, light *new_plain);

// MEMORY RELEASING
void    free_lights(light **head);

// DISPLAY
void    display_camera(camera c);
void    display_ambient_light(ambient_light al);
void    display_light(light *l);

#endif // VIEW_H