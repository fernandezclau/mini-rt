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

static vector3	get_direction(camera *cam, float x_nds, float y_nds);

/**
 * @brief Calculates the intersections of a ray with scene objects 
 * (spheres, planes, and cylinders) and updates the closest hit point.
 * 
 * @param r The ray cast from the camera into the scene.
 * @param scene The structure containing the scene's objects 
 * (spheres, planes, and cylinders) and the intersection results.
 */
void	ray_intersection(ray r, scene *scene)
{
	init_hit_point(&scene->hit);
	intersection_spheres(&r, &scene->spheres, &scene->hit);
	interesection_planes(&r, &scene->planes, &scene->hit);
	intersection_cylinders(&r, &scene->cylinders, &scene->hit);
}

/**
 * @brief Computes the direction of a ray from the camera to a given pixel.
 * 
 * @param x Pixel x-coordinate on the screen.
 * @param y Pixel y-coordinate on the screen.
 * @param fov Camera's field of view in degrees.
 * @param cam Pointer to the camera structure with position and basis vectors.
 * @return vector3 Normalized direction vector of the ray.
 */
vector3	compute_ray_direction(int x, int y, float fov, camera *cam)
{
	float	fov_ratio;
	float	width_aspect_ratio;
	float	height_aspect_ratio;
	float	x_nds;
	float	y_nds;

	fov_ratio = fabs(2 * 1 * tanf(fov * (M_PI / 180.0) / 2.0));
	width_aspect_ratio = fov_ratio / W_WIDTH;
	height_aspect_ratio = (width_aspect_ratio * W_HEIGHT) / W_HEIGHT;
	x_nds = (x - W_WIDTH / 2) * width_aspect_ratio;
	y_nds = -(y - W_HEIGHT / 2) * height_aspect_ratio;
	return (get_direction(cam, x_nds, y_nds));
}

/**
 * @brief Calculates the final direction vector based on the camera basis vectors
 * and normalized device coordinates.
 * 
 * @param cam The camera structure containing its basis vectors.
 * @param x_nds The x-coordinate in normalized device coordinates.
 * @param y_nds The y-coordinate in normalized device coordinates.
 * @return The computed and normalized direction vector.
 */
static vector3	get_direction(camera *cam, float x_nds, float y_nds)
{
	float	z;
	vector3	direction;
	vector3	dir_x;
	vector3	dir_y;
	vector3	dir_z;

	z = 1;
	dir_x = scale_v3(cam->identity[0], x_nds);
	dir_y = scale_v3(cam->identity[1], y_nds);
	dir_z = scale_v3(cam->identity[2], z);
	direction = sum_v3(sum_v3(dir_x, dir_y), dir_z);
	return (normalize_v3(direction));
}
