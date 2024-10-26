#include "minirt.h"

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
    //free_mlx_resources(data);
    exit(0);
    return (0);
}

int key_hook(int keycode, t_data *data)
{
    if (keycode == ESC_KEY)
        close_window(data);
    else if (keycode == A_KEY)
        printf("Mover izquierda");
    else if (keycode == D_KEY)
        printf("Mover derecha");
    else if (keycode == W_KEY)
        printf("Mover arriba");
    else if (keycode == S_KEY)
        printf("Mover abaAjo");
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