/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:08:13 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:08:14 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	intersection_cylinders(ray *r, cylinder **cylinders, hit *l_hit)
{
	cylinder	*iter_cylinders;

	iter_cylinders = *cylinders;
	while (iter_cylinders != NULL)
	{
		if (intersect_ray_cylinder(r, l_hit, iter_cylinders))
		{
			if (l_hit->dist < l_hit->min_dist || l_hit->intersect == 0)
			{
				l_hit->min_dist = l_hit->dist;
				l_hit->final_color = iter_cylinders->color;
				set_cylinder_normal(r, iter_cylinders, l_hit);
			}
			l_hit->intersect = 1;
		}
		iter_cylinders = iter_cylinders->next;
	}
}

int	intersect_ray_cylinder(ray *r, hit *hit, cylinder *cl)
{
	ugh	top_cap;
	ugh	cylinder_body;
	ugh	bottom_cap;

	init_ugh_cylinder(&top_cap, &cylinder_body, &bottom_cap, cl);
	intersect_circle(r, &top_cap, cl->diameter / 2);
	intersect_cylinder(r, cl, &cylinder_body);
	intersect_circle(r, &bottom_cap, cl->diameter / 2);
	if (select_dist_cylinder(cylinder_body, top_cap, bottom_cap, hit))
		return (1);
	else if (select_dist_cylinder2(top_cap, bottom_cap, hit))
		return (1);
	return (0);
}

// Intersección de un rayo con el cuerpo de un cilindro
int	intersect_cylinder(ray *r, cylinder *cl, ugh *ugh)
{
	vector3	w;
	vector3	d_perp;
	vector3	w_perp;
	float	projection_axis;
	float	d;

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
void	add_cylinder(cylinder **head, cylinder *new_cylinder)
{
	cylinder	*last;

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
void	free_cylinder(cylinder **head)
{
	cylinder	*current;
	cylinder	*next;

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
