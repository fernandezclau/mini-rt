/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <claferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:09:52 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:09:54 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vector3	calculate_spotlight(t_light light, t_vector3 normal, \
		t_vector3 p_to_l);
int			apply_shadow(t_light *light, t_scene *scene, t_hit *hit);

/**
 * @brief Calculates the combined light at a given hit point, including 
 * ambient and spotlight contributions.
 * 
 * @param scene The scene containing lights, ambient light, and other objects.
 * @param hit Pointer to the hit structure which holds the intersection details.
 * 
 * @return The combined light color at the hit point.
 */
void	calculate_light(t_scene *scene, t_hit *hit)
{
	t_vector3	final_light;
	t_light		*i_light;
	t_vector3	l_point;
	t_vector3	spotlight;

	final_light = calculate_ambient_light(scene->ambient_light);
	i_light = scene->lights;
	while (i_light != NULL)
	{
		if (apply_shadow(i_light, scene, hit))
		{
			l_point = normalize_v3(substract_v3(i_light->position, \
						hit->position));
			spotlight = calculate_spotlight(*i_light, hit->normal, l_point);
			final_light = sum_v3(final_light, spotlight);
		}
		i_light = i_light->next;
	}
	hit->final_color = multiply_color(hit->final_color, final_light);
}

/**
 * @brief Determines if a shadow ray from a light source to the hit point
 * is obstructed by another object.
 * 
 * @param light The light source to check for shadows.
 * @param scene The scene containing all objects.
 * @param hit The hit structure containing the intersection position.
 * 
 * @return `true` if the hit point is in shadow, `false` otherwise.
 */
int	apply_shadow(t_light *light, t_scene *scene, t_hit *hit)
{
	t_ray	shadow_r;
	t_hit	new_hit;

	shadow_r.origin = light->position;
	shadow_r.direction = normalize_v3(substract_v3(hit->position, \
				light->position));
	ray_intersection(shadow_r, scene, &new_hit);
	if (hit->intersect && \
			length_v3(substract_v3(new_hit.position, hit->position)) \
			<= EPSILON_2)
		return (1);
	return (0);
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
