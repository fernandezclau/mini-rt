/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:08:13 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:17:15 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	intersect_ray_cylinder(t_ray *r, t_hit *hit, t_cylinder *cl);
int	intersect_cylinder(t_ray *r, t_cylinder *cl, t_ugh *ugh);

/**
 * @brief Calculates intersections between a ray and a list of cylinders.
 * 
 * @param r Ray structure containing the origin and direction of the ray.
 * @param cylinders List of cylinder structures to check for intersections.
 * @param l_hit Hit structure where the closest inters details are stored.
 */
void	intersection_cylinders(t_ray *r, t_cylinder **cylinders, t_hit *l_hit)
{
	t_cylinder	*iter_cylinders;

	iter_cylinders = *cylinders;
	while (iter_cylinders != NULL)
	{
		if (intersect_ray_cylinder(r, l_hit, iter_cylinders))
		{
			if ((l_hit->dist > 0 && l_hit->dist < l_hit->min_dist) \
			|| l_hit->intersect == 0)
			{
				l_hit->min_dist = l_hit->dist;
				l_hit->final_color = iter_cylinders->color;
				set_intersection_position(r, l_hit);
				set_cylinder_normal(iter_cylinders, l_hit);
			}
			l_hit->intersect = 1;
		}
		iter_cylinders = iter_cylinders->next;
	}
}

/**
 * @brief Checks if a ray intersects a specific cylinder, 
 * including its body and caps.
 * 
 * @param r Ray structure containing the origin and direction of the ray.
 * @param hit Hit structure where the intersection details are stored if found.
 * @param cl Pointer to the cylinder structure to test for intersection.
 * 
 * @return Returns 1 if the ray intersects any part; otherwise, returns 0.
 */
int	intersect_ray_cylinder(t_ray *r, t_hit *hit, t_cylinder *cl)
{
	t_ugh	top_cap;
	t_ugh	cylinder_body;
	t_ugh	bottom_cap;

	init_ugh_cylinder(&top_cap, &cylinder_body, &bottom_cap, cl);
	intersect_circle(r, &top_cap, cl->diameter / 2);
	intersect_cylinder(r, cl, &cylinder_body);
	intersect_circle(r, &bottom_cap, cl->diameter / 2);
	if (select_dist_cylinder(cylinder_body, top_cap, bottom_cap, hit))
		return (1);
	return (select_dist_cylinder2(top_cap, bottom_cap, hit));
}

/**
 * @brief Calculates the intersection between a ray and a cylinder.
 * 
 * @param r Ray structure containing the origin and direction of the ray.
 * @param cl Cylinder structure containing info of the cylinder.
 * @param ugh Structure where the intersection info will be stored.
 * 
 * @return Returns 1 if there is an intersection between ray and cylinder. 
 * Or 0 if no intersection is found or if it's outside the cylinder’s bounds.
 */
int	intersect_cylinder(t_ray *r, t_cylinder *cl, t_ugh *ugh)
{
	t_vector3	w;
	t_vector3	d_perp;
	t_vector3	w_perp;
	float		projection_axis;
	float		d;

	w = substract_v3(r->origin, cl->center);
	d_perp = substract_v3(r->direction, scale_v3(cl->direction, \
				dot_product_v3(r->direction, cl->direction)));
	w_perp = substract_v3(w, scale_v3(cl->direction, \
				dot_product_v3(w, cl->direction)));
	if (!cylinder_calculations(d_perp, w_perp, cl, &d))
		return (0);
	ugh->position = sum_v3(r->origin, scale_v3(r->direction, d));
	projection_axis = dot_product_v3(substract_v3(ugh->position, \
				cl->center), cl->direction);
	if (projection_axis < 0 || projection_axis > cl->height)
		return (0);
	ugh->distance = d;
	return (1);
}

/**
 * @brief Adds a cylinder to the end of the cylinder linked list.
 *
 * @param head A pointer to a pointer to the head of the cylinder linked list.
 * @param new_cylinder A pointer to the new cylinder to be added.
 */
void	add_cylinder(t_cylinder **head, t_cylinder *new_cylinder)
{
	t_cylinder	*last;

	if (*head == NULL)
		*head = new_cylinder;
	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_cylinder;
	}
}

/**
 * @brief Frees the memory allocated for the cylinder linked list.
 *
 * @param head A pointer to a pointer to the head of the cylinder linked list.
 */
void	free_cylinder(t_cylinder **head)
{
	t_cylinder	*current;
	t_cylinder	*next;

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
