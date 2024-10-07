#include "minirt.h"

// int main(int argc, char **argv)
// {
//     t_data  data;
//     scene scene;

//     if (get_scene(argc, argv[1], &scene))
//     {
//         data.mlx_ptr = mlx_init();
//         data.win_ptr = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, W_TITLE);

//         data.image_ptr = mlx_new_image(data.mlx_ptr, W_WIDTH, W_HEIGHT);
//         data.image_data = mlx_get_data_addr(data.image_ptr, &data.bpp, &data.size_line,
//                                     &data.endian);
        
//         my_mlx_pixel_put(&data, 5, 5, 0x00FF0000);
//         mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.image_ptr, 0, 0);
//         // HOOKS
//         mlx_key_hook(data.win_ptr, key_hook, &data);
//         mlx_hook(data.win_ptr, 17, 0, close_window, &data);
//         mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
//         mlx_loop(data.mlx_ptr);
//         free_scene(&scene);
//     }

    

//     return 0;
// }

#include <stdio.h>
#include <math.h>
#include "../include/minirt.h"

#define M_PI 3.14159265358979323846

int main(int argc, char **argv) {
    scene scene;

    // // Inicialización de la vista
    // float near = 0.1f;
    // float far = 1000.0f;
    // float fov = 90.0f; // Campo de visión en grados
    // int height = 600;  // Altura de la ventana
    // int width = 800;   // Ancho de la ventana

    //view v = view_p_init(near, far, fov, height, width);
    get_scene(argc, argv[1], &scene);

    // Inicialización de la cámara
    //vector3 up = {0.0f, 1.0f, 0.0f};         // Vector hacia arriba
    // vector3 position = {0.0f, 0.0f, -1.0f};   // Posición de la cámara
    // vector3 direction = {0.0f, 0.0f, 1.0f}; // Dirección de la cámara

    //camera c = camara_p_init(up, position, direction);

    // Punto 3D a proyectar
    vector3 point = {0.0f, 0.5f, 1.0f}; // Un punto en el espacio 3D

    // Proyección del punto en el espacio de la pantalla
    vector2 screen_point = project_point(&scene.camera, &scene.view, &point);

    // Mostrar el resultado
    printf("Point 3D: (%f, %f, %f)\n", point.x, point.y, point.z);
    printf("Projected Screen Point: (%f, %f)\n", screen_point.x, screen_point.y);

    return 0;
}
