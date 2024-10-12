#include "minirt.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void    draw_tri(vector2 *a, vector2 *b, vector2 *c, t_data *img)
{
    a->x = 0.0f;
    a->y = 600.0f;

    b->x = 800.0f;
    b->y = 600.0f;

    c->x = 00.0f;
    c->y = 0.0f;
    
    float pendiente = (float) (c->x - a->x) / (float)(a->y - c->y);

    for (int i = a->y; i > c->y; i--)
    {
        int x1 = a->x + pendiente * i;
        my_mlx_pixel_put(img, x1, a->y - i, 0x00FF0000);
        for (int j = x1; j < c->x; j++)
        {
            my_mlx_pixel_put(img, j, a->y - i, 0x00FF0000);
        }
    }
}


// void    draw_triangle(vector2 *a, vector2 *b, vector2 *c, t_data *img)
// {
//     join_dots(a, b, img);
//     join_dots(b, c, img);
//     join_dots(c, a, img);
// }

// int main(int argc, char **argv)
// {
//     t_data  data;
//     scene scene;
//     (void)argc, (void) argv;

//     // if (get_scene(argc, argv[1], &scene))
//     // {
//         data.mlx_ptr = mlx_init();
//         data.win_ptr = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, W_TITLE);

//         data.image_ptr = mlx_new_image(data.mlx_ptr, W_WIDTH, W_HEIGHT);
//         data.image_data = mlx_get_data_addr(data.image_ptr, &data.bpp, &data.size_line,
//                                     &data.endian);
        
//         vector2 a= {0, 0};
//         vector2 b= {0, 0};
//         vector2 c= {0, 0};
//         draw_tri(&a, &b, &c, &data);
//         //my_mlx_pixel_put(&data, 5, 5, 0x00FF0000);
//         mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.image_ptr, 0, 0);
//         // HOOKS
//         mlx_key_hook(data.win_ptr, key_hook, &data);
//         mlx_hook(data.win_ptr, 17, 0, close_window, &data);
//         mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
//         mlx_loop(data.mlx_ptr);
//         free_scene(&scene);
//     //}
//     return 0;
// }

#include <stdio.h>
#include <math.h>
#include "../include/minirt.h"

#define M_PI 3.14159265358979323846

// int main(int argc, char **argv) {
//     scene scene;

//     // // Inicialización de la vista
//     // float near = 0.1f;
//     // float far = 1000.0f;
//     // float fov = 90.0f; // Campo de visión en grados
//     // int height = 600;  // Altura de la ventana
//     // int width = 800;   // Ancho de la ventana

//     //view v = view_p_init(near, far, fov, height, width);
//     get_scene(argc, argv[1], &scene);

//     // Inicialización de la cámara
//     //vector3 up = {0.0f, 1.0f, 0.0f};         // Vector hacia arriba
//     // vector3 position = {0.0f, 0.0f, -1.0f};   // Posición de la cámara
//     // vector3 direction = {0.0f, 0.0f, 1.0f}; // Dirección de la cámara

//     //camera c = camara_p_init(up, position, direction);

//     // Punto 3D a proyectar
//     vector3 point = {0.0f, 0.5f, 1.0f}; // Un punto en el espacio 3D

//     // Proyección del punto en el espacio de la pantalla
//     vector2 screen_point = project_point(&scene.camera, &scene.view, &point);

//     // Mostrar el resultado
//     printf("Point 3D: (%f, %f, %f)\n", point.x, point.y, point.z);
//     printf("Projected Screen Point: (%f, %f)\n", screen_point.x, screen_point.y);

//     return 0;
// }


int main(int argc, char **argv) {
//    scene scene;
    (void) argc;
    (void) argv;

    // // Inicialización de la vista
    float near = 0.1f;
    float far = 1000.0f;
    float fov = 90.0f; // Campo de visión en grados
    int height = 600;  // Altura de la ventana
    int width = 800;   // Ancho de la ventana

    view view = view_p_init(near, far, fov, height, width);

    // Inicialización de la cámara
    vector3 up = {0.0f, 1.0f, 0.0f};         // Vector hacia arriba
    vector3 position = {0.0f, 0.0f, -10.0f};   // Posición de la cámara
    vector3 direction = {0.0f, 0.0f, 1.0f}; // Dirección de la cámara

    camera cam = camara_p_init(up, position, direction);

    // Punto 3D a proyectar
    vector3 point = {0.0f, 0.0f, 15.0f}; // Un punto en el espacio 3D

    // Proyección del punto en el espacio de la pantalla
    vector2 screen_point = project_point(&cam, &view, &point);

    vector3 a = {-0.1f, -0.1f, 1.0f};   // Esquina superior izquierda
    vector3 b = {0.1f, -0.1f, 1.0f};    // Esquina superior derecha
    vector3 c = {-0.1f, 0.1f, 1.0f};    // Esquina inferior izquierda
    vector3 d = {0.1f, 0.1f, 1.0f};     // Esquina inferior derecha

    vector2 a2 = project_point(&cam, &view, &a);
    vector2 b2 = project_point(&cam, &view, &b);
    vector2 c2 = project_point(&cam, &view, &c);
    vector2 d2 = project_point(&cam, &view, &d);

    t_data  data;
    data.camera = cam;

    // Inicializar MiniLibX
    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, W_TITLE);
    data.image_ptr = mlx_new_image(data.mlx_ptr, W_WIDTH, W_WIDTH);
    data.image_data = mlx_get_data_addr(data.image_ptr, &data.bpp, &data.size_line, &data.endian);

    fill_triangle(&data, &a2, &b2, &c2, 0x00FF00);
    fill_triangle(&data, &a2, &c2, &d2, 0x00FF00);
    
    // Mostrar la imagen
    mlx_key_hook(data.win_ptr, key_hook, &data);
    mlx_hook(data.win_ptr, 17, 0, close_window, &data);
    mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
    mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.image_ptr, 0, 0);
    mlx_loop(data.mlx_ptr);
    
    // Mostrar el resultado
    printf("Point 3D: (%f, %f, %f)\n", point.x, point.y, point.z);
    printf("Projected Screen Point: (%f, %f)\n", screen_point.x, screen_point.y);

    return 0;
}