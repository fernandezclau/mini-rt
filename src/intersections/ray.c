/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:08:31 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:08:32 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

float		get_tan_fov(float fov);
float		get_aspect_ratio(void);

/**
 * @brief Calculates the intersections of a ray with scene objects 
 * (spheres, planes, and cylinders) and updates the closest hit point.
 * 
 * @param r The ray cast from the camera into the scene.
 * @param scene The structure containing the scene's objects 
 * (spheres, planes, and cylinders) and the intersection results.
 */
void	ray_intersection(t_ray r, t_scene *scene, t_hit *hit)
{
	init_hit_point(hit);
	intersection_planes(&r, &scene->planes, hit);
	intersection_spheres(&r, &scene->spheres, hit);
	intersection_cylinders(&r, &scene->cylinders, hit);
	intersection_cones(&r, &scene->cones, hit);
}

/**
 * @brief Calculates the ray direction for a specific pixel on the screen.
 * 
 * @param scene The `t_scene` structure containing the camera and 
 * scene parameters.
 * @param x The horizontal coordinate of the pixel on the screen (X axis).
 * @param y The vertical coordinate of the pixel on the screen (Y axis).
 * 
 * @return A normalized `t_vector3` vector representing the ray direction 
 * from the camera toward the `(x, y)` pixel in 3D space.
 */
t_vector3	calculate_ray_direction(t_scene *scene, unsigned x, unsigned y)
{
	t_vector3	ray_direction;
	float		screen_x;
	float		screen_y;

	screen_x = (1.0f - 2.0f * ((x + 0.5f) / W_WIDTH)) * \
		get_aspect_ratio() * \
		get_tan_fov(scene->camera.fov);
	screen_y = (1.0f - 2.0f * ((y + 0.5f) / W_HEIGHT)) * \
		get_tan_fov(scene->camera.fov);
	ray_direction = sum_v3(sum_v3(scale_v3(scene->camera.right, screen_x), \
				scale_v3(scene->camera.true_up, screen_y)), \
			get_foward(scene->camera));
	return (normalize_v3(ray_direction));
}

float	get_tan_fov(float fov)
{
	return (tan(fov * M_PI / 360.0f));
}

float	get_aspect_ratio(void)
{
	return ((float)(W_WIDTH) / (float)(W_HEIGHT));
}

t_vector3	get_foward(t_camera camera)
{
	return (normalize_v3(camera.direction));
}
