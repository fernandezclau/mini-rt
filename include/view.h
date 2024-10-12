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

typedef struct ambient_light {
    float   ratio;
    color color;
}           ambient_light;

typedef struct light
{
    vector3 position;
    float   brightness;
    color   color;
}           light;

// INIT
void    init_camera(camera *c);
void    init_light(light *l);
void    init_ambient_light(ambient_light *al);

#endif // VIEW_H