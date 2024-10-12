#include "minirt.h"

void	destroy_and_render(t_data *img)
{
     float near = 0.1f;
    float far = 1000.0f;
    float fov = 90.0f; // Campo de visión en grados
    int height = 600;  // Altura de la ventana
    int width = 800;   // Ancho de la ventana

    view view = view_p_init(near, far, fov, height, width);

	mlx_destroy_image(img->mlx_ptr, img->image_ptr);
	
    img->image_ptr = mlx_new_image(img->mlx_ptr, W_WIDTH, W_WIDTH);
    img->image_data = mlx_get_data_addr(img->image_ptr, &img->bpp, &img->size_line, &img->endian);
	
    vector3 a = {-0.1f, -0.1f, 1.0f};   // Esquina superior izquierda
    vector3 b = {0.1f, -0.1f, 1.0f};    // Esquina superior derecha
    vector3 c = {-0.1f, 0.1f, 1.0f};    // Esquina inferior izquierda
    vector3 d = {0.1f, 0.1f, 1.0f};     // Esquina inferior derecha

    vector2 a2 = project_point(&img->camera, &view, &a);
    vector2 b2 = project_point(&img->camera, &view, &b);
    vector2 c2 = project_point(&img->camera, &view, &c);
    vector2 d2 = project_point(&img->camera, &view, &d);
    fill_triangle(img, &a2, &b2, &c2, 0x00FF00);
    fill_triangle(img, &a2, &c2, &d2, 0x00FF00);
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, \
			img->image_ptr, 1, 1);
}

void free_mlx_resources(t_data *data)
{
    if (data->image_ptr)
        mlx_destroy_image(data->mlx_ptr, data->image_ptr);
    if (data->win_ptr)
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    // if (data->mlx_ptr)
    //     free(data->mlx_ptr);
}

// Close window with x key.
int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
 //   free_mlx_resources(data);
    exit(0);
    return (0);
}

int key_hook(int keycode, t_data *data)
{
    if (keycode == ESC_KEY)
        close_window(data);
    else if (keycode == A_KEY)
    {
        printf("Mover izquierda");
        data->camera.position.z += 0.2f;
        calculate_view_matrix(&data->camera);
    }
    else if (keycode == D_KEY)
        printf("Mover derecha");
    else if (keycode == W_KEY)
        printf("Mover arriba");
    else if (keycode == S_KEY)
        printf("Mover abaAjo");
    destroy_and_render(data);
    return (0);
}

int mouse_hook(int button)
{
    if (button == 4) // Scroll 
        printf("Ampliar zoom\n");
    else if (button == 5) // Scroll Down
        printf("Alejar zoom\n");
    // Actualizar la ventana con la nueva posición si es necesario
    return (0);
}