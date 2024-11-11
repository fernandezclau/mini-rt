/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:05:12 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:05:13 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Initializes a scene by setting all its geometric shapes to NULL.
 *
 * @param scene A pointer to the scene structure to be initialized.
 */
void	init_scene(t_scene *scene)
{
	init_camera(&scene->camera);
	scene->lights = NULL;
	init_ambient_light(&scene->ambient_light);
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
}

/**
 * @brief Initializes a hit structure by setting all its parameters to NULL.
 *
 * @param hit A pointer to the hit structure to be initialized.
 */
void	init_hit_point(t_hit *hit)
{
	hit->intersect = 0;
	hit->dist = INFINITY;
	hit->intersect = 0;
	hit->min_dist = INFINITY;
	hit->reflection = REFLECT_RATIO;
	init_r_color(&hit->final_color);
	init_r_v3(&hit->position);
	init_r_v3(&hit->normal);
}

/**
 * @brief Frees all allocated resources in the scene.
 *
 * @param scene A pointer to the scene structure to be freed.
 */
void	free_scene(t_scene *scene)
{
	free_lights(&scene->lights);
	free_spheres(&scene->spheres);
	free_plane(&scene->planes);
	free_cylinder(&scene->cylinders);
}

/**
 * @brief Prints the details of the scene to the standard output.
 *
 * @param scene The scene structure containing all the scene elements 
 * to be displayed.
 */
void	print_scene(t_scene scene)
{
	display_camera(scene.camera);
	display_ambient_light(scene.ambient_light);
	display_light(scene.lights);
	display_spheres(scene.spheres);
	display_cylinders(scene.cylinders);
	display_planes(scene.planes);
}
