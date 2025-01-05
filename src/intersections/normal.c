/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:08:21 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:08:22 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Adjusts the normal of a plane at the intersection point to ensure
 * it faces against the ray direction for correct shading.
 * 
 * @param r The ray intersecting with the plane.
 * @param l_hit The hit record.
 * @param pl The plane structure.
 */
void	set_plane_normal(t_ray *r, t_hit *l_hit, t_plane *pl)
{
	l_hit->normal = normalize_v3(pl->normal);
	if (dot_product_v3(r->direction, pl->normal) > 0)
		l_hit->normal = scale_v3(l_hit->normal, -1);
}

/**
 * @brief Adjusts the normal of a sphere at the intersection point to ensure
 * it faces against the ray direction for correct shading.
 * 
 * @param l_hit The hit record.
 * @param pl The sphere structure.
 */
void	set_sphere_normal(t_hit *l_hit, t_sphere *sp)
{
	l_hit->normal = normalize_v3(substract_v3(l_hit->position, sp->center));
}

/**
 * @brief Sets the normal vector at the hit point on a cylinder.
 * 
 * @param cy The cylinder with which the ray intersects.
 * @param l_hit The hit structure storing the intersection details,
 * including the position of the hit and the normal to be calculated.
 */
void	set_cylinder_normal(t_cylinder *cy, t_hit *l_hit)
{
	t_vector3	base_to_point;
	float		distance;
	t_vector3	projected_point;

	base_to_point = substract_v3(l_hit->position, cy->center);
	distance = dot_product_v3(base_to_point, cy->direction);
	if (distance <= EPSILON_4)
		l_hit->normal = scale_v3(normalize_v3(cy->direction), -1);
	else if (distance < cy->height - EPSILON_4)
	{
		projected_point = sum_v3(cy->center, scale_v3(cy->direction, distance));
		l_hit->normal = normalize_v3(substract_v3(l_hit->position, \
					projected_point));
	}
	else if (distance >= cy->height - EPSILON_4)
		l_hit->normal = normalize_v3(cy->direction);
}

/**
 * @brief Sets the normal vector at the hit point on a cone.
 * 
 * @param cn The cone with which the ray intersects.
 * @param l_hit The hit structure storing the intersection details,
 * including the position of the hit and the normal to be calculated.
 */
void	set_cone_normal(t_cone *cn, t_hit *l_hit)
{
	t_vector3	bp;
	t_vector3	ap;
	t_vector3	ab;
	t_vector3	apab_perp;

	bp = substract_v3(l_hit->position, cn->center);
	if (dot_product_v3(bp, cn->direction) <= EPSILON_4)
		l_hit->normal = scale_v3(cn->direction, -1);
	else
	{
		ap = normalize_v3(substract_v3(l_hit->position, cn->apex));
		ab = normalize_v3(substract_v3(cn->center, cn->apex));
		apab_perp = cross_product_v3(ap, ab);
		l_hit->normal = scale_v3(normalize_v3(cross_product_v3(apab_perp, \
						ap)), -1);
	}
}
