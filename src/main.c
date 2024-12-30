/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:04:16 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:04:18 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_scene	scene;

	(void)argc, (void) argv;
	if (get_scene(argc, argv[1], &scene))
	{
		data.scene = &scene;
		data.mlx_ptr = mlx_init();
		data.win_ptr = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, W_TITLE);
		data.image_ptr = mlx_new_image(data.mlx_ptr, W_WIDTH, W_HEIGHT);
		data.image_data = mlx_get_data_addr(data.image_ptr, &data.bpp, \
				&data.size_line, &data.endian);
		render(&data, &scene);
		mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, \
				data.image_ptr, 0, 0);
		mlx_key_hook(data.win_ptr, key_hook, &data);
		mlx_hook(data.win_ptr, 17, 0, close_window, &data);
		// mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
		mlx_loop(data.mlx_ptr);
		free_scene(&scene);
	}
	return (0);
}
