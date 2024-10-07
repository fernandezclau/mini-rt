#include "../include/minirt.h"
#define M_PI 3.14159265358979323846

view    view_p_init(float near, float far, float fov, int height, int width)
{
    view    v;
    float   aspect_ratio = (float) width / (float) height;
    float   tan_middle_fov = tan(fov *0.5f * M_PI / 180.0f);

    v.near = near;
    v.far = far;
    //v.fov = fov;
    v.height = height;
    v.width = width;

    // formula matrix proyeccion 
    v.projection_matrix.a.x = 1.0f / aspect_ratio * tan_middle_fov;
    v.projection_matrix.b.y = tan_middle_fov;
    v.projection_matrix.c.z = -1.0f * (far + near) / (far - near);
    v.projection_matrix.c.k = -2.0f * far * near / (far- near);
    v.projection_matrix.d.z = -1.0f;
    
    return v;
}

// calcular la matriz de vista
void    calculate_view_matrix(camera *c)
{
    vector3 f = v3_normalize(v3_substract(c->direction, c->position));
    vector3 r = v3_normalize(v3_cross_product(f, c->up));
    vector3 u = v3_cross_product(r, f);

    c->view_matrix.a.x = r.x;
    c->view_matrix.a.y = u.x;
    c->view_matrix.a.z = -f.x;
    c->view_matrix.a.k = 0.0f;

    c->view_matrix.b.x = r.y;
    c->view_matrix.b.y = u.y;
    c->view_matrix.b.z = -f.y;
    c->view_matrix.b.k = 0.0f;

    c->view_matrix.c.x = r.z;
    c->view_matrix.c.y = u.z;
    c->view_matrix.c.z = -f.z;
    c->view_matrix.c.k = 0.0f;

    c->view_matrix.d.x = -v3_dot_product(r, c->position);
    c->view_matrix.d.y = -v3_dot_product(u, c->position);
    c->view_matrix.d.z = v3_dot_product(f, c->position);
    c->view_matrix.d.k = 1.0f;
}

camera  camara_p_init(vector3 up, vector3 position, vector3 direction)
{
    camera  c;

    c.up = up;
    c.position = position;
    c.direction = direction;
    calculate_view_matrix(&c);

    return c;
}

vector2 project_point(camera *cam, view *view, vector3 * v3)
{
    mat4 pv_matrix = mac4_multiple(view->projection_matrix, cam->view_matrix);
    vector4 point_4d = init_p_v4(v3->x, v3->y, v3->z, 1.0f);
    vector4 clip_space_point = multiple_v4_mat4(pv_matrix, point_4d);
    print_v4(clip_space_point);
    printf("\n");
    vector3 ndc;
    if (clip_space_point.k != 0.0f)
    {
        ndc.x = clip_space_point.x / clip_space_point.k;
        ndc.y = clip_space_point.y / clip_space_point.k;
        ndc.z = clip_space_point.z / clip_space_point.k;
    }
    print_v3(ndc);

    vector2 screen_point;
    screen_point.x = (ndc.x * 0.5f + 0.5f) * view->width;
    screen_point.y = (1.0f - (ndc.y * 0.5f + 0.5f)) * view->height;

    return screen_point;
}



