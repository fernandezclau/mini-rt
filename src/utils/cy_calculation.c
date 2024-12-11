/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_calculation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:04:24 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:31:48 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Initializes intersection data for the cylinder caps and body.
 * 
 * @param top_cap Ugh structure representing the top cap of the cylinder.
 * @param cylinder_cap Ugh structure representing the cylinder body.
 * @param bottom_cap Ugh structure representing the bottom cap of the cylinder.
 * @param cl Cylinder structure to initialize intersection data for.
 */
void	init_ugh_cylinder(t_ugh *top_cap, t_ugh *cylinder_body, \
		t_ugh *bottom_cap, t_cylinder *cl)
{
	cl->direction = normalize_v3(cl->direction);
	top_cap->distance = FLT_MAX;
	cylinder_body->distance = FLT_MAX;
	bottom_cap->distance = FLT_MAX;
	top_cap->center = sum_v3(cl->center, scale_v3(cl->direction, cl->height));
	bottom_cap->center = cl->center;
	top_cap->direction = cl->direction;
	bottom_cap->direction = scale_v3(cl->direction, -1);
}

/**
 * @brief Performs calculations for ray-cylinder intersection.
 * 
 * @param d_perp The perpendicular component of the ray’s direction
 *  relative to the cylinder.
 * @param w_perp The perpendicular component of the vector from the ray origin
 *  to the cylinder’s center.
 * @param cl Pointer to the cylinder structure to perform calculations for.
 * @param d Pointer to store the resulting intersection distance.
 * 
 * @return Returns 1 if an intersection occurs; otherwise, returns 0.
 */
int	cylinder_calculations(t_vector3 d_perp, t_vector3 w_perp, \
		t_cylinder *cl, float *d)
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	radius;

	radius = cl->diameter / 2;
	a = dot_product_v3(d_perp, d_perp);
	b = 2 * dot_product_v3(w_perp, d_perp);
	c = dot_product_v3(w_perp, w_perp) - radius * radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	calculate_intersection_times(a, b, discriminant, d);
	return (1);
}

/**
 * @brief Selects the closest valid intersection distance among 
 * cylinder body and caps.
 *  
 * @param cylinder_body The ugh structure representing the intersection data 
 * for the cylinder body.
 * @param top_cap The ugh structure representing the intersection data 
 * for the top cap.
 * @param bottom_cap The ugh structure representing the intersection data 
 * for the bottom cap.
 * @param hit Pointer to the hit structure to update with 
 * the closest intersection details.
 * 
 * @return Returns 1 if a valid intersection is found; otherwise, returns 0.
 */
int	select_dist_cylinder(t_ugh cylinder_body, t_ugh top_cap, \
		t_ugh bottom_cap, t_hit *hit)
{
	if (cylinder_body.distance <= top_cap.distance)
	{
		if (cylinder_body.distance <= bottom_cap.distance)
		{
			if (cylinder_body.distance != FLT_MAX)
			{
				hit->dist = cylinder_body.distance;
				return (1);
			}
		}
		else
		{
			if (bottom_cap.distance != FLT_MAX)
			{
				hit->dist = bottom_cap.distance;
				return (1);
			}
		}
	}
	return (0);
}

/**
 * @brief Selects the closest intersection distance between the cylinder caps.
 * 
 * @param top_cap The ugh structure representing the intersection data 
 * for the top cap.
 * @param bottom_cap The ugh structure representing the intersection data 
 * for the bottom cap.
 * @param hit Pointer to the hit structure to update with the closest
 *  intersection details.
 * 
 * @return Returns 1 if a valid intersection is found; otherwise, returns 0.
 */
int	select_dist_cylinder2(t_ugh top_cap, t_ugh bottom_cap, t_hit *hit)
{
	if (top_cap.distance <= bottom_cap.distance)
	{
		if (top_cap.distance != FLT_MAX)
		{
			hit->dist = top_cap.distance;
			return (1);
		}
	}
	else
	{
		if (bottom_cap.distance != FLT_MAX)
		{
			hit->dist = bottom_cap.distance;
			return (1);
		}
	}
	return (0);
}

/**
 * @brief Checks if a ray intersects a circular cap of a cylinder.
 * 
 * @param r Pointer to the ray structure containing the origin and direction 
 * of the ray.
 * @param ugh Pointer to the ugh structure where the intersection data will be 
 * stored if an intersection occurs.
 * @param radius The radius of the circular cap.
 * 
 * @return Returns 1 if the ray intersects the circular cap; otherwise, 0.
 */
int	intersect_circle(t_ray *r, t_ugh *ugh, float radius)
{
	t_vector3	oc;
	float		denom;
	float		t;
	t_vector3	intersect_point;
	float		distance_center;

	oc = substract_v3(ugh->center, r->origin);
	denom = dot_product_v3(r->direction, ugh->direction);
	if (fabs(denom) < EPSILON_6)
		return (0);
	t = dot_product_v3(oc, ugh->direction) / denom;
	if (t < 0)
		return (0);
	intersect_point = sum_v3(r->origin, scale_v3(r->direction, t));
	distance_center = length_v3(substract_v3(intersect_point, ugh->center));
	if (distance_center > radius)
		return (0);
	ugh->position = intersect_point;
	ugh->distance = t;
	return (1);
}
