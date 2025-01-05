/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:08:35 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:08:36 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Renders the entire scene by casting rays from the camera through 
 * each pixel, calculating intersections with scene objects, and coloring 
 * pixels based on the hit results.
 * 
 * @param data The rendering data structure for pixel output.
 * @param scene The scene data containing camera, objects, and light sources.
 */
void	render(t_data *data, t_scene *scene)
{
	t_ray			r;
	unsigned int	x;
	unsigned int	y;
	t_hit			initial_hit;

	x = 0;
	while (x < W_WIDTH)
	{
		y = 0;
		while (y < W_HEIGHT)
		{
			r.direction = calculate_ray_direction(scene, x, y);
			r.origin = scene->camera.position;
			ray_intersection(r, scene, &initial_hit);
			if (initial_hit.intersect)
			{
				calculate_light(scene, &initial_hit);
				pixel_put(data, x, y, rgb_to_hex(&initial_hit.final_color));
			}
			y += PPP;
		}
		x += PPP;
	}
}

/**
 * @brief Puts a pixel in the image at the specified position
 * with the given color.
 *
 * @param data Pointer to the image data structure.
 * @param x X-coordinate of the pixel to draw.
 * @param y Y-coordinate of the pixel to draw.
 * @param color Color of the pixel in hexadecimal format.
 */
void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	while (i < PPP)
	{
		j = 0;
		while (j < PPP)
		{
			dst = data->image_data + ((y + j) * \
					data->size_line + (x + i) * (data->bpp / 8));
			*(unsigned int *)dst = color;
			j++;
		}
		i++;
	}
}

/**
 * @brief Calculates the intersection position of a ray with an object 
 * and updates the hit position.
 * 
 * @param r Ray that intersects the object. 
 *          Contains the origin and direction of the ray.
 * @param hit Hit record where the intersection position 
 *            will be stored. This structure should contain the distance
 *            from the origin of the ray to the intersection point.
 */
void	set_intersection_position(t_ray *r, t_hit *hit)
{
	hit->position = sum_v3(r->origin, scale_v3(r->direction, hit->dist));
}
