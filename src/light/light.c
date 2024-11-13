/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:09:52 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:09:54 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vector3	calculate_spotlight(t_light light, t_vector3 normal, t_vector3 p_to_l);

void	calculate_light(t_ray r, t_scene *scene, t_hit *hit)
{
	t_vector3	intensity;
	t_light	*iter_light;
	t_vector3	point_to_l;
	t_vector3	p_intensity;
	t_ray	shadow_r;
	t_hit new_hit;
	
	intensity = calculate_ambient_light(scene->ambient_light);

	iter_light = scene->lights;
	while (iter_light != NULL)
	{
		shadow_r.origin = iter_light->position;
		shadow_r.direction = normalize_v3(substract_v3(hit->position, iter_light->position));
		ray_intersection(shadow_r, scene, &new_hit);
		if (scene->hit.intersect && length_v3(substract_v3(new_hit.position, hit->position)) <= 0.01f)
		{
			point_to_l = normalize_v3(substract_v3(iter_light->position, hit->position));
			p_intensity = calculate_spotlight(*iter_light, hit->normal, point_to_l);
			intensity = sum_v3(intensity, p_intensity);	
		}
		iter_light = iter_light->next;
	}
	hit->final_color = multiply_color(hit->final_color, intensity);
}

/**
 * @brief Initializes a light structure to default values.
 *
 * @param l A pointer to the light structure to be initialized.
 */
void	init_light(t_light *l)
{
	init_r_v3(&l->position);
	init_r_color(&l->color);
	l->brightness = 0;
}

/**
 * @brief Adds a plane to the end of the plane linked list.
 *
 * @param head A pointer to a pointer to the head of the plane linked list.
 * @param new_light A pointer to the new plane to be added.
 */
void	add_light(t_light **head, t_light *new_light)
{
	t_light	*last;

	if (*head == NULL)
		*head = new_light;
	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_light;
	}
}

/**
 * @brief Frees the memory allocated for the light linked list.
 *
 * @param head A pointer to a pointer to the head of the light linked list.
 */
void	free_lights(t_light **head)
{
	t_light	*current;
	t_light	*next;

	current = *head;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}
// #include <stdbool.h>  // For using bool type

// /**
//  * @brief Calculates the combined light intensity at a given hit point, including ambient and spotlight contributions.
//  * 
//  * @param r The ray that intersects the object.
//  * @param scene The scene containing lights, ambient light, and other objects.
//  * @param hit Pointer to the hit structure which holds the intersection details.
//  * 
//  * @return The combined light intensity at the hit point.
//  */
// t_vector3 calculate_light_intensity(t_ray r, t_scene *scene, t_hit *hit) {
//     t_vector3 intensity = calculate_ambient_light(scene->ambient_light);
//     t_light *iter_light = scene->lights;

//     while (iter_light != NULL) {
//         if (!apply_shadow(iter_light, scene, hit)) {
//             t_vector3 point_to_l = normalize_v3(substract_v3(iter_light->position, hit->position));
//             t_vector3 p_intensity = calculate_spotlight(*iter_light, hit->normal, point_to_l);
//             intensity = sum_v3(intensity, p_intensity);
//         }
//         iter_light = iter_light->next;
//     }
//     return intensity;
// }

// /**
//  * @brief Determines if a shadow ray from a light source to the hit point is obstructed by another object.
//  * 
//  * @param light The light source to check for shadows.
//  * @param scene The scene containing all objects.
//  * @param hit The hit structure containing the intersection position.
//  * 
//  * @return `true` if the hit point is in shadow, `false` otherwise.
//  */
// bool apply_shadow(t_light *light, t_scene *scene, t_hit *hit) {
//     t_ray shadow_r;
//     t_hit new_hit;

//     // Set up a shadow ray from the light source to the hit point
//     shadow_r.origin = light->position;
//     shadow_r.direction = normalize_v3(substract_v3(hit->position, light->position));

//     // Check if the shadow ray intersects any object before reaching the hit point
//     ray_intersection(shadow_r, scene, &new_hit);
//     if (scene->hit.intersect && length_v3(substract_v3(new_hit.position, hit->position)) <= 0.01f) {
//         return true;  // The hit point is in shadow
//     }
//     return false;  // No obstruction, light reaches the hit point
// }

// /**
//  * @brief Calculates the final color at the hit point after considering all light sources.
//  * 
//  * @param r The ray that intersects the object.
//  * @param scene The scene containing lights and other objects.
//  * @param hit Pointer to the hit structure where the final color will be stored.
//  */
// void calculate_light(t_ray r, t_scene *scene, t_hit *hit) {
//     t_vector3 intensity = calculate_light_intensity(r, scene, hit);
//     hit->final_color = multiply_color(hit->final_color, intensity);
// }
