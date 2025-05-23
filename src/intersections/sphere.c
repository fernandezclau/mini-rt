/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <claferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:08:39 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:08:41 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	intersect_ray_sphere(t_ray *r, t_sphere *sp, t_hit *hit);

/**
 * @brief Checks for intersections between a ray and a list of spheres.
 * If an intersection is found, updates the hit record with the distance to the 
 * closest intersection point and the color of the intersecting sphere.
 * 
 * @param r The ray being tested for intersections.
 * @param spheres A pointer to a linked list of spheres to test against.
 * @param l_hit A pointer to the hit record to update with intersection details.
 */
void	intersection_spheres(t_ray *r, t_sphere **spheres, t_hit *l_hit)
{
	t_sphere	*iter_spheres;

	iter_spheres = *spheres;
	while (iter_spheres != NULL)
	{
		if (intersect_ray_sphere(r, iter_spheres, l_hit))
		{
			if ((l_hit->dist > 0 && l_hit->dist < l_hit->min_dist) \
			|| l_hit->intersect == 0)
			{
				l_hit->min_dist = l_hit->dist;
				l_hit->final_color = iter_spheres->color;
				set_intersection_position(r, l_hit);
				set_sphere_normal(l_hit, iter_spheres);
			}
			l_hit->intersect = 1;
		}
		iter_spheres = iter_spheres->next;
	}
}

/**
 * @brief Intersects a ray with a sphere.
 *
 * @param r Ray structure containing the origin and direction of the ray.
 * @param sp Sphere structure containing the center and radius.
 * @param hit Hit structure that contains the intersection information.
 * @return Returns 1 if the ray intersects.
 *         Returns 0 if there is no intersection.
 */
int	intersect_ray_sphere(t_ray *r, t_sphere *sp, t_hit *hit)
{
	t_vector3	oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;

	oc = substract_v3(r->origin, sp->center);
	a = dot_product_v3(r->direction, r->direction);
	b = 2.0f * dot_product_v3(oc, r->direction);
	c = dot_product_v3(oc, oc) - (sp->radius * sp->radius);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	return (calculate_intersection_times(a, b, discriminant, &hit->dist));
}

/**
 * @brief Calculates the intersection times between a ray and a sphere.
 * 
 * @param a The quadratic coefficient of the intersection equation.
 * @param b The linear coefficient of the intersection equation.
 * @param discriminant The discriminant of the quadratic equation.
 * @param d Float that will store the intersection distance.
 * 
 * @return int Returns 1 if a valid intersection exists, or 0 if not.
 */
int	calculate_intersection_times(float a, float b, float discriminant, float *d)
{
	float	t1;
	float	t2;
	float	sqrt_disc;

	sqrt_disc = sqrt(discriminant);
	t1 = (-b - sqrt_disc) / (2 * a);
	t2 = (-b + sqrt_disc) / (2 * a);
	if (t1 > 0 && t2 > 0)
		*d = fmin(t1, t2);
	else if (t1 > 0)
		*d = t1;
	else if (t2 > 0)
		*d = t2;
	else
		return (0);
	return (1);
}

/**
 * @brief Adds a sphere to the end of the sphere linked list.
 *
 * @param head A pointer to a pointer to the head of the sphere linked list.
 * @param new_sphere A pointer to the new sphere to be added.
 */
void	add_sphere(t_sphere **head, t_sphere *new_sphere)
{
	t_sphere	*last;

	if (*head == NULL)
		*head = new_sphere;
	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_sphere;
	}
}

/**
 * @brief Frees the memory allocated for the sphere linked list.
 *
 * @param head A pointer to a pointer to the head of the sphere linked list.
 */
void	free_spheres(t_sphere **head)
{
	t_sphere	*current;
	t_sphere	*next;

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
