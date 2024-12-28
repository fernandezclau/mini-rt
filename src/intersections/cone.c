/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:48:14 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/12/11 19:48:16 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	intersect_ray_cone(t_ray *r, t_hit *hit, t_cone *cn);
int	intersect_cone(t_ray *r, t_cone *cn, t_ugh *ugh);

/**
 * @brief Calculates intersections between a ray and a list of cones.
 * 
 * @param r Ray structure containing the origin and direction of the ray.
 * @param cones List of cone structures to check for intersections.
 * @param l_hit Hit structure where the closest inters details are stored.
 */
void	intersection_cones(t_ray *r, t_cone **cones, t_hit *l_hit)
{
	t_cone	*iter_cones;

	iter_cones = *cones;
	while (iter_cones != NULL)
	{
		if (intersect_ray_cone(r, l_hit, iter_cones))
		{
			if ((l_hit->dist > 0 && l_hit->dist < l_hit->min_dist) \
			|| l_hit->intersect == 0)
			{
				l_hit->min_dist = l_hit->dist;
				l_hit->final_color = iter_cones->color;
				set_intersection_position(r, l_hit);
				set_cone_normal(iter_cones, l_hit); //TODO implement this
			}
			l_hit->intersect = 1;
		}
		iter_cones = iter_cones->next;
	}
}

/**
 * @brief Intersects a ray with a cone.
 *
 * @param r Ray structure containing the origin and direction of the ray.
 * @param cn cone structure containing the center and radius.
 * @param hit Hit structure that contains the intersection information.
 * @return Returns 1 if the ray intersects.
 *         Returns 0 if there is no intersection.
 */
int	intersect_ray_cone(t_ray *r, t_hit *hit, t_cone *cn)
{
	t_ugh	base;
	t_ugh	body;

	cn->apex = sum_v3(cn->center, scale_v3(cn->direction, cn->height));
	init_ugh_cone(&base, &body, cn);
	intersect_circle(r, &base, cn->diameter / 2);
	intersect_cone(r, cn, &body);
	return (select_dist_cone(body, base, hit));
}

int	intersect_cone(t_ray *r, t_cone *cn, t_ugh *ugh)
{
	float		tantheta2;
	float		vaxis;
	float		projection_axis;
	float		d;

	tantheta2 = pow(cn->diameter / 2, 2) / pow(cn->height, 2);
	vaxis = dot_product_v3(r->direction, cn->direction);
	if (!cone_calculations(r, tantheta2, cn, &d))
		return (0);
	ugh->position = sum_v3(r->origin, scale_v3(r->direction, d));
	projection_axis = dot_product_v3(substract_v3(ugh->position, \
				cn->center), cn->direction);
	if (projection_axis < 0 || projection_axis > cn->height)
		return (0);
	ugh->distance = d;
	return (1);
}

/**
 * @brief Adds a cone to the end of the cone linked list.
 *
 * @param head A pointer to a pointer to the head of the cone linked list.
 * @param new_cone A pointer to the new cone to be added.
 */
void	add_cone(t_cone **head, t_cone *new_cone)
{
	t_cone	*last;

	if (*head == NULL)
		*head = new_cone;
	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_cone;
	}
}

/**
 * @brief Frees the memory allocated for the cone linked list.
 *
 * @param head A pointer to a pointer to the head of the cone linked list.
 */
void	free_cone(t_cone **head)
{
	t_cone	*current;
	t_cone	*next;

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
