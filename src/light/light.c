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

t_vector3	final_intensity(t_light light, t_vector3 normal, t_vector3 p_to_l);

t_vector3	intersection_point(t_ray ray, double distance)
{
	t_vector3	intersection;

	intersection = sum_v3(ray.origin, \
		scale_v3(ray.direction, distance));
	return (intersection);
}

t_color	calculate_light(t_ray r, t_scene *scene)
{
	t_vector3	intensity;
	t_light	*iter_light;
	t_hit	hit;
	t_ambient_light	al;
	t_vector3	point_to_l;
	t_vector3	p_intensity;
	t_vector3	c = {0, 0, 0};
    
	al = scene->ambient_light;
	hit = scene->hit;
	iter_light = scene->lights;
	intensity = calculate_ambient_light(al);
	while (iter_light != NULL)
	{
		point_to_l = normalize_v3(substract_v3(iter_light->position, hit.position));
		p_intensity = final_intensity(*iter_light, scene->hit.normal, point_to_l);
		intensity = sum_v3(intensity, p_intensity);
		iter_light = iter_light->next;
	}
	c.x = hit.final_color.r * intensity.x;
	c.y = hit.final_color.g * intensity.y;
	c.z = hit.final_color.b * intensity.z;
	return (vector3_to_color(c));
}

t_vector3	final_intensity(t_light light, t_vector3 normal, t_vector3 p_to_l)
{
	t_vector3	light_intensity;
	t_vector3	diffuse;
	t_vector3	specular;
	t_vector3	intensity;

	light_intensity = calculate_intensity(light.color, light.brightness);
	specular = specular_intensity(normal, p_to_l, light_intensity);
	diffuse = diffuse_intensity(normal, p_to_l, light_intensity);
	return (sum_v3(specular, diffuse));
}

/**
 * @brief Calculates the effect of ambient light on a given color.
 *
 * @param color Pointer to the color structure that will be modified to 
 *              incorporate the ambient light effect.
 * @param light The ambient light structure containing the color and ratio 
 *              of the ambient light.
*/
t_vector3	calculate_intensity(t_color colour, float ratio)
{
	t_vector3	intensity;
	int		sum_color;

	sum_color = colour.r + colour.g + colour.b;
	intensity.x = INTENSITY_RATIO * 3 * ratio * colour.r / sum_color;
	intensity.y = INTENSITY_RATIO * 3 * ratio * colour.g / sum_color;
	intensity.z = INTENSITY_RATIO * 3 * ratio * colour.b / sum_color;
	return (intensity);
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

/**
 * @brief Displays the details of a light structure.
 *
 * @param l The light structure to be displayed.
 */
void	display_light(t_light *l)
{
	int		i;
	t_light	*current;

	current = l;
	i = 1;
	printf(" %s____ LIGHT ____ %s\n\n", WH, RE);
	while (current)
	{
		printf("%s %d. %s\n\n", WH, i, RE);
		printf("%s > Position %s", WH, RE);
		display_v3(current->position);
		printf("\n");
		printf("%s > Brightness %s", WH, RE);
		printf("%s[%f]%s\n\n", CY, current->brightness, RE);
		printf("%s > Color %s", WH, RE);
		display_color(current->color);
		printf("\n");
		current = current->next;
		i++;
	}
}
