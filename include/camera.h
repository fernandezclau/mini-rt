#ifndef CAMERA_H
#define CAMERA_H
#include "./vectors.h"


typedef struct view
{
    // inmutables
    float near;     // punto más cercano
    float far;      // punto más lejano
    float fov;      // angulo 
    int     height; // window height
    int     width;  // window with
    mat4    projection_matrix;
}           view;

typedef struct camera
{
    vector3 up;        // no sabemos  
    vector3 position;  // coordinates
    vector3 direction; // target
    float   fov;       //  va en view
    mat4    view_matrix;
}           camera;

view    view_p_init(float near, float far, float fov, int height, int width);
void    calculate_view_matrix(camera *c);
camera  camara_p_init(vector3 up, vector3 position, vector3 direction);
vector2 project_point(camera *cam, view *view, vector3 * v3);

#endif // CAMERA_H