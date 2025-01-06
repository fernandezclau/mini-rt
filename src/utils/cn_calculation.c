/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cn_calculation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:07:10 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/12/16 19:07:12 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Initializes intersection data for the cone caps and body.
 * 
 * @param base Ugh structure representing the base of the cone.
 * @param body Ugh structure representing the cone body.
 * @param cn cone structure to initialize intersection data for.
 */
void	init_ugh_cone(t_ugh *base, t_ugh *body, t_cone *cn)
{
	cn->direction = normalize_v3(cn->direction);
	body->distance = FLT_MAX;
	base->distance = FLT_MAX;
	base->position = cn->center;
	base->direction = scale_v3(cn->direction, -1);
}

/**
 * @brief Performs calculations for ray-cone intersection.
 * 
 * @param r Pointer to the ray structure containing the origin and direction 
 * of the ray.
 * @param tantheta2 The cone slope factor
 * @param cn Pointer to the cone structure to perform calculations for.
 * @param d Pointer to store the resulting intersection distance.
 * 
 * @return Returns 1 if an intersection occurs; otherwise, returns 0.
 */
int	cone_calculations(t_ray *r, float tantheta2, t_cone *cn, float *d)
{
	float	a;
	float	b;
	float	c;
	float	ocaxis;
	float	vaxis;

	vaxis = dot_product_v3(r->direction, cn->direction);
	ocaxis = dot_product_v3(substract_v3(r->origin, cn->apex), cn->direction);
	a = pow_v3(r->direction) - (1.0f + tantheta2) * pow(vaxis, 2);
	b = 2 * (dot_product_v3(r->direction, substract_v3(r->origin, cn->apex)) - \
			(1.0f + tantheta2) * vaxis * ocaxis);
	c = pow_v3(substract_v3(r->origin, cn->apex)) - \
			(1.0f + tantheta2) * pow(ocaxis, 2);
	if (b * b - 4.0f * a * c <= 0.0f)
		return (0);
	calculate_intersection_times(a, b, b * b - 4.0f * a * c, d);
	return (1);
}

/**
 * @brief Selects the closest valid intersection distance among 
 * cone body and caps.
 *  
 * @param base The ugh structure representing the intersection data 
 * for the base.
 * @param body The ugh structure representing the intersection data 
 * for the cone body.
 * @param hit Pointer to the hit structure to update with 
 * the closest intersection details.
 * 
 * @return Returns 1 if a valid intersection is found; otherwise, returns 0.
 */
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
