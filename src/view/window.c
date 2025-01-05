/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:05:17 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:05:18 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Frees the resources allocated by the MLX library.
 * 
 * @param data Pointer to the data structure containing MLX pointers.
 */
void	free_resources(t_data *data)
{
	if (data->image_ptr)
		mlx_destroy_image(data->mlx_ptr, data->image_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
}

/**
 * @brief Closes the MLX window and exits the program.
 * 
 * @param data Pointer to the data structure containing MLX pointers.
 * @return int Always returns 0.
 */
int	close_window(t_data *data)
{
	free_resources(data);
	free_scene(data->scene);
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
	(void)button;
	return (0);
}
