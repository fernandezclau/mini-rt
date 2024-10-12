#ifndef SHAPES_H
    #define SHAPES_H

#include "./view.h"
#include "./minirt.h"

typedef struct plane
{
    vector3         point;
    vector3         normal;
    color           color;
    struct plane    *next;
}                   plane;

typedef struct sphere
{
    vector3         center;
    float           diameter;
    color           color;
    struct sphere   *next;
}                   sphere;

typedef struct cylinder
{
    vector3         center;
    vector3         direction;
    float          diameter;
    float          height;
    color           color;
    struct cylinder *next;
}                   cylinder;

// INSERTION
int     insert_vector3(vector3 *v, char **tokens, int is_normalized);
int     insert_color(color *c, char **tokens);
int     insert_angle(float *fov, char *value);
int     insert_ratio(float *ratio, char *value);
int     insert_magnitude(float *magnitude, char *value);

// LIST HANDLING
void    add_sphere(sphere **head, sphere *new_sphere);
void    add_plane(plane **head, plane *new_plain);
void    add_cylinder(cylinder **head, cylinder *new_cylinder);

// INTERSECTIONS
int intersect_ray_plane(ray *r, vector3 *point_on_plane, vector3 *normal, float *t);
int intersect_ray_sphere(ray *r, vector3 *center, float radius, float *t);
int intersect_ray_cylinder(ray *r, vector3 *center, float radius, float height, float *t);

// MEMORY RELEASING
void    free_spheres(sphere **head);
void    free_plane(plane **head);
void    free_cylinder(cylinder **head);

// PRINTING
void    display_color(color c);
void    display_v3(vector3 v);
void    display_camera(camera c);
void    display_ambient_light(ambient_light al);
void    display_light(light l);
void    display_spheres(sphere *sp);
void    display_planes(plane *pl);
void    display_cylinders(cylinder *cl);

#endif  // SHAPES_H