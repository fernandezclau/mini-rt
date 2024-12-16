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
int	intersect_cone(t_ray *r, t_cone *cn, t_vector3 apex);

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
				set_cone_normal(iter_cones, l_hit);
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
	t_ugh		base;
	t_ugh		body;

	(void)r;(void)hit;(void)cn;
	init_ugh_cone(&base, &body, cn);
	intersect_circle(r, &base, cn->diameter / 2);
	return (intersect_cone(r, cn, sum_v3(cn->center, scale_v3(cn->direction, cn->height))));
	// return (0);
	// return (select_dist_cone(body, base, hit));
}

int	intersect_cone(t_ray *r, t_cone *cn, t_vector3 apex)
{
	float		tantheta2 = ((cn->diameter / 2) * (cn->diameter / 2)) / (cn->height * cn->height);
	t_vector3	oc = substract_v3(r->origin, apex);
	float		vaxis = dot_product_v3(r->direction, cn->direction);
	float		ocaxis = dot_product_v3(oc, cn->direction);
	float		a = dot_product_v3(r->direction, r->direction) - (1.0f + tantheta2) * (vaxis * vaxis);
	float		b = 2.0f * (dot_product_v3(r->direction, oc) - (1.0f + tantheta2) * vaxis * ocaxis);
	float		c = dot_product_v3(oc, oc) - (1.0f + tantheta2) * (ocaxis * ocaxis);
	float		discriminant = b * b - 4.0f * a * c;
	if (discriminant <= 0.0f)
		return (0);
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
