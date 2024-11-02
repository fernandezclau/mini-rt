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
    float           radius;
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

// LIST INTERSECTIONS
void    interesection_planes(ray *r, plane **planes, hit *l_hit);
void    intersection_spheres(ray *r, sphere **spheres, hit *l_hit);
void    intersection_cylinders(ray *r, cylinder **cylinders, hit *l_hit);

// SINGLE INTERSECTIONS
int intersect_ray_plane(ray* r, plane* pl, hit* hit);
int     intersect_ray_sphere(ray *r, sphere *sphere, float *t);
int     intersect_ray_cylinder(ray *r, cylinder *cl, float *t);

// NORMAL
void    set_cylinder_normal(ray *r, cylinder *cy, hit *l_hit);
void    set_plane_normal(ray *r, hit *l_hit, plane *pl);

// ON OBJECT
int     is_on_plane(plane plane, vector3 point);
int     is_on_cylinder(cylinder cylinder, vector3 point);
int     is_on_sphere(sphere sphere, vector3 point);

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

// MEMORY RELEASING
void    free_spheres(sphere **head);
void    free_plane(plane **head);
void    free_cylinder(cylinder **head);

// DISPLAY
void    display_spheres(sphere *sp);
void    display_planes(plane *pl);
void    display_cylinders(cylinder *cl);

#endif  // SHAPES_H