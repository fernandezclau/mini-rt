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

int	select_dist_cone(t_ugh base, t_ugh body, t_hit *hit)
{
	if (base.distance <= body.distance)
	{
		if (base.distance != FLT_MAX)
		{
			hit->dist = base.distance;
			return (1);
		}
	}
	else
	{
		if (body.distance != FLT_MAX)
		{
			hit->dist = body.distance;
			return (1);
		}
	}
	return (0);
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
	int		ret;
	t_ugh	base;
	t_ugh	body;

	(void)r;(void)hit;(void)cn;
	cn->apex = sum_v3(cn->center, scale_v3(cn->direction, cn->height));
	init_ugh_cone(&base, &body, cn);
	intersect_circle(r, &base, cn->diameter / 2);
	intersect_cone(r, cn, &body);
	ret = select_dist_cone(base, body, hit);
	return (ret);
	// return (intersect_circle(r, &base, cn->diameter / 2));
	return (intersect_cone(r, cn, &body));
	// return (select_dist_cone(body, base, hit));
}

int	cone_calculations(t_ray *r, float tantheta2, t_cone *cn, float vaxis, t_vector3 oc, float *d)
{
	float	a;
	float	b;
	float	c;
	float	ocaxis;
	float	discriminant;

	ocaxis = dot_product_v3(oc, cn->direction);
	a = pow_v3(r->direction) - (1.0f + tantheta2) * pow(vaxis,2);
	b = 2.0f * (dot_product_v3(r->direction, oc) - (1.0f + tantheta2) * vaxis * ocaxis);
	c = pow_v3(oc) - (1.0f + tantheta2) * pow(ocaxis, 2);
	discriminant = b * b - 4.0f * a * c;
	if (discriminant <= 0.0f)
		return (0);
	calculate_intersection_times(a, b, discriminant, d);
	return (1);
}

// int	intersect_cone(t_ray *r, t_cone *cn, t_ugh *ugh, t_vector3 apex)
// {
// 	(void)ugh;
// 	t_vector3	oc = substract_v3(r->origin, apex);
// 	float		slope = (cn->diameter / 2) / cn->height;
// 	float		k = 1.0f + pow(slope, 2);
// 	float		vaxis = dot_product_v3(r->direction, cn->direction);
// 	float		ocaxis = dot_product_v3(oc, cn->direction);
// 	t_vector3	rd_perp = substract_v3(r->direction, scale_v3(cn->direction, vaxis));
// 	t_vector3	oc_perp = substract_v3(oc, scale_v3(cn->direction, ocaxis));
// 	float		a = pow_v3(rd_perp) - k * pow(vaxis, 2);
// 	float		b = 2.0f * (dot_product_v3(rd_perp, oc_perp) - k * vaxis * ocaxis);
// 	float		c = pow_v3(oc_perp) - k * pow(ocaxis, 2);
// 	float discriminant = b * b - 4.0f * a * c;
// 	if (discriminant <= 0.0f)
// 		return (0);
// 	float		t1 = (-b - sqrt(discriminant)) / (2.0f * a);
// 	float		t2 = (-b + sqrt(discriminant)) / (2.0f * a);
// 	if (
// 		!(
// 			dot_product_v3(substract_v3(sum_v3(r->origin, scale_v3(r->direction, t1)), apex), cn->direction) >= 0 && \
// 			dot_product_v3(substract_v3(sum_v3(r->origin, scale_v3(r->direction, t1)), apex), cn->direction) <= cn->height \
// 		) && \
// 		!(
// 			dot_product_v3(substract_v3(sum_v3(r->origin, scale_v3(r->direction, t2)), apex), cn->direction) >= 0 && \
// 			dot_product_v3(substract_v3(sum_v3(r->origin, scale_v3(r->direction, t2)), apex), cn->direction) <= cn->height \
// 		)
// 	)
// 		return (0);
// 	return (1);
// }

int	intersect_cone(t_ray *r, t_cone *cn, t_ugh *ugh)
{
	float		tantheta2;
	float		vaxis;
	t_vector3	oc;
	// float		ocaxis;
	// float		a;
	// float		b;
	// float		c;
	// float		discriminant;
	float		projection_axis;
	float		d;

	tantheta2 = pow(cn->diameter / 2, 2) / pow(cn->height, 2);
	oc = substract_v3(r->origin, cn->apex);
	vaxis = dot_product_v3(r->direction, cn->direction);

	if (!cone_calculations(r, tantheta2, cn, vaxis, oc, &d))
		return (0);
	// a = pow_v3(r->direction) - (1.0f + tantheta2) * pow(vaxis,2);
	// b = 2.0f * (dot_product_v3(r->direction, oc) - (1.0f + tantheta2) * vaxis * ocaxis);
	// c = pow_v3(oc) - (1.0f + tantheta2) * pow(ocaxis, 2);
	// discriminant = b * b - 4.0f * a * c;
	// if (discriminant <= 0.0f)
	// 	return (0);

	// float		t1 = (-b - sqrt(discriminant)) / (2.0f * a);
	// float		t2 = (-b + sqrt(discriminant)) / (2.0f * a);

	ugh->position = sum_v3(r->origin, scale_v3(r->direction, d));
	projection_axis = dot_product_v3(substract_v3(ugh->position, \
				cn->center), cn->direction);
	if (projection_axis < 0 || projection_axis > cn->height)
		return (0);
	ugh->distance = d;

	// if (
	// 	!(
	// 		dot_product_v3(substract_v3(sum_v3(r->origin, scale_v3(r->direction, t1)), apex), cn->direction) >= 0 && \
	// 		dot_product_v3(substract_v3(sum_v3(r->origin, scale_v3(r->direction, t1)), apex), cn->direction) <= cn->height \
	// 	) && \
	// 	!(
	// 		dot_product_v3(substract_v3(sum_v3(r->origin, scale_v3(r->direction, t2)), apex), cn->direction) >= 0 && \
	// 		dot_product_v3(substract_v3(sum_v3(r->origin, scale_v3(r->direction, t2)), apex), cn->direction) <= cn->height \
	// 	)
	// )
	// 	return (0);
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
