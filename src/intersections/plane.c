/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:08:24 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:08:25 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Checks for intersections between a ray and a list of planes.
 * If an intersection is found, updates the hit record with the distance to the 
 * closest intersection point and the color of the intersecting plane.
 * 
 * @param r The ray being tested for intersections.
 * @param planes A pointer to a linked list of planes to test against.
 * @param l_hit A pointer to the hit record to update with intersection details.
 */
void	intersection_planes(t_ray *r, t_plane **planes, t_hit *l_hit)
{
	t_plane	*iter_planes;

	iter_planes = *planes;
	while (iter_planes != NULL)
	{
		if (intersect_ray_plane(r, iter_planes, l_hit))
		{
			if ((l_hit->dist > 0 && l_hit->dist < l_hit->min_dist) \
			|| l_hit->intersect == 0)
			{
				l_hit->min_dist = l_hit->dist;
				l_hit->final_color = iter_planes->color;
				l_hit->reflection = 0;
				set_intersection_position(r, l_hit);
				set_plane_normal(r, l_hit, iter_planes);
			}
			l_hit->intersect = 1;
		}
		iter_planes = iter_planes->next;
	}
}

/**
 * @brief Intersects a ray with a plane.
 *
 * @param r Ray structure containing the origin and direction of the ray.
 * @param point_on_plane Vector3 structure representing a point on the plane.
 * @param normal Vector3 structure representing the normal of the plane.
 * @param hit Hit structure with intersection information.
 * @return Returns 1 if the ray intersects.
 *         Returns 0 if there is no intersection.
 */
int	intersect_ray_plane(t_ray *r, t_plane *pl, t_hit *hit)
{
	float		denom;
	float		t;
	t_vector3	point_origin;

	pl->normal = normalize_v3(pl->normal);
	denom = dot_product_v3(r->direction, pl->normal);
	if (fabs(denom) < EPSILON_4)
		return (0);
	point_origin = substract_v3(pl->point, r->origin);
	t = dot_product_v3(point_origin, pl->normal) / denom;
	if (t < 0)
		return (0);
	hit->dist = t;
	return (1);
}

/**
 * @brief Adds a plane to the end of the plane linked list.
 *
 * @param head A pointer to a pointer to the head of the plane linked list.
 * @param new_plane A pointer to the new plane to be added.
 */
void	add_plane(t_plane **head, t_plane *new_plane)
{
	t_plane	*last;

	if (*head == NULL)
		*head = new_plane;
	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_plane;
	}
}

/**
 * @brief Frees the memory allocated for the plane linked list.
 *
 * @param head A pointer to a pointer to the head of the plane linked list.
 */
void	free_plane(t_plane **head)
{
	t_plane	*current;
	t_plane	*next;

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
