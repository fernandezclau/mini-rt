/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:02:56 by drenassi          #+#    #+#             */
/*   Updated: 2024/03/25 15:11:53 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Returns the distance from the ray's origin to the intersection point
 *	with a plane.
*/
double	pl_intersection(ray ray, plane pl)
{
	double		scalar;
	vector3	ray_to_pl;

	scalar = dot_product_v3(ray.direction, pl.normal);
	if (fabs(scalar) < 0.001)
		return (INFINITY);
	ray_to_pl = substract_v3(pl.point, ray.origin);
	return (dot_product_v3(pl.normal, ray_to_pl) / scalar);
}

/*
 *	Returns the distance from the ray's origin to the intersection point
 *	with a sphere.
*/
double	sp_intersection(ray ray, sphere sp)
{
	vector3	ray_to_sp;
	double		a;
	double		b;
	double		c;

	ray_to_sp = substract_v3(ray.origin, sp.center);
	a = dot_product_v3(ray.direction, ray.direction);
	b = 2 * dot_product_v3(ray_to_sp, ray.direction);
	c = dot_product_v3(ray_to_sp, ray_to_sp) - sp.radius * sp.radius;
	return (quadratic(a, b, c, 0));
}

/*
 *	Returns the distance from the ray's origin to the intersection point
 *	with an object.
*/
double	obj_intersection(ray ray, t_obj *obj)
{
	if (!obj)
		return (INFINITY);
	if (obj->pl)
		return (pl_intersection(ray, *obj->pl));
	else if (obj->sp)
		return (sp_intersection(ray, *obj->sp));
	else if (obj->cy)
		return (cy_intersection(ray, *obj->cy));
	else if (obj->co)
		return (cone_intersection(ray, *obj->co));
	return (INFINITY);
}

/*
 *	Returns the closest object from ray's origin and its distance from it.
*/
t_closest_obj	closest_intersection(t_obj *objs, ray ray)
{
	double			distance;
	t_obj			*obj;
	t_closest_obj	res;

	res.obj = NULL;
	res.distance = INFINITY;
	obj = objs;
	while (obj)
	{
		distance = obj_intersection(ray, obj);
		if (distance > 0.001 && distance < res.distance)
		{
			res.obj = obj;
			res.distance = distance;
		}
		obj = obj->next;
	}
	return (res);
}
