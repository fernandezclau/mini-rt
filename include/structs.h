#ifndef STRUCTS_H
    #define STRUCTS_H

#include "./camera.h"

// typedef struct vector3 {
//     float   x;
//     float   y;
//     float   z;
// }           vector3;

// typedef struct vector2 {
//     float   x;
//     float   y;
// }           vector2;

// typedef struct camera {
//     vector3 position;
//     vector3 direction;
//     int     fov;
// }           camera;

typedef struct color
{
    int r;
    int g;
    int b;
}       color;

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

typedef struct sphere
{
    vector3         center;
    float           diameter;
    color           color;
    struct sphere   *next;
}                   sphere;

typedef struct plane
{
    vector3         point;
    vector3         normal;
    color           color;
    struct plane    *next;
}                   plane;

typedef struct cylinder
{
    vector3         center;
    vector3         direction;
    float          diameter;
    float          height;
    color           color;
    struct cylinder *next;
}                   cylinder;

typedef struct scene
{
    view            view;
    ambient_light   ambient;
    camera          camera;
    light           light;
    sphere          *spheres;
    plane           *planes;
    cylinder        *cylinders;
    int             num_spheres;
    int             num_planes;
    int             num_cylinders;
}               scene;

// INIT
void    init_scene(scene *scene);

// INSERTION
int insert_vector3(vector3 *v, char **tokens, int is_normalized);
int insert_color(color *c, char **tokens);
int insert_angle(float *fov, char *value);
int insert_ratio(float *ratio, char *value);
int insert_magnitude(float *magnitude, char *value);

// LIST HANDLING
void    add_sphere(sphere **head, sphere *new_sphere);
void    add_plane(plane **head, plane *new_plain);
void    add_cylinder(cylinder **head, cylinder *new_cylinder);

void    free_scene(scene *scene);
void    free_spheres(sphere **head);
void    free_plane(plane **head);
void    free_cylinder(cylinder **head);

// PRINTING
void    print_color(color c);
void    print_vector3(vector3 v);
void    print_camera(camera c);
void    print_ambient_light(ambient_light al);
void    print_light(light l);
void    print_spheres(sphere *sp);
void    print_planes(plane *pl);
void    print_cylinders(cylinder *cl);
void    print_scene(scene scene);
#endif