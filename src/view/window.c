#include "minirt.h"

/**
 * @brief Frees the resources allocated by the MLX library.
 * 
 * @param data Pointer to the data structure containing MLX pointers.
 */
void	free_mlx_resources(t_data *data)
{
	if (data->image_ptr)
		mlx_destroy_image(data->mlx_ptr, data->image_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
}

/**
 * @brief Closes the MLX window and exits the program.
 * 
 * @param data Pointer to the data structure containing MLX pointers.
 * @return int Always returns 0.
 */
int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
	return (0);
}

/**
 * @brief Handles keyboard input and performs actions based on key presses.
 * 
 * @param keycode Integer representing the key pressed.
 * @param data Pointer to the data structure containing MLX pointers.
 * @return int Always returns 0.
 */
int	key_hook(int keycode, t_data *data)
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
		printf("Mover abajo");
	return (0);
}

/**
 * @brief Handles mouse button events for zooming.
 *  
 * @param button Integer representing the mouse button pressed.
 * @return int Always returns 0.
 */
int	mouse_hook(int button)
{
	if (button == 4)
		printf("Scroll: Ampliar zoom\n");
	else if (button == 5)
		printf("Scroll down: Alejar zoom\n");
	printf("Actualizar la ventana con la nueva posición si es necesario");
	return (0);
}
