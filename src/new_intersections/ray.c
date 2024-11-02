/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <@student.42perpignan.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:21:40 by drenassi          #+#    #+#             */
/*   Updated: 2024/03/21 18:56:57 by drenassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 *	Returns the ray intersection point coordinates from the ray's origin.
*/
vector3	intersection_point(ray ray, double distance)
{
	vector3	intersection;

	intersection = sum_v3(ray.origin, \
		scale_v3(ray.direction, distance));
	return (intersection);
}

/*
 *	Returns the ray's direction and lenght.
*/
vector3	seray(vector3 base[3], double x, double y, double z)
{
	vector3	new;

	new.x = base[0].x * x + base[1].x * y + base[2].x * z;
	new.y = base[0].y * x + base[1].y * y + base[2].y * z;
	new.z = base[0].z * x + base[1].z * y + base[2].z * z;
	return (new);
}

/*
 *	Traces the primary ray. It will stop at the first intersection with
 *	an object, change the color of the intersection point, then reflect
 *	back in a recursive way.
*/
color	ray_trace(t_data *data, ray ray, int depth)
{
	hit	closest;
	vector3		closest_normal;
	color			color;
	vector3		inter;

	closest = closest_intersection(data->objs, ray);
	if (!closest.obj)
		return ((color){0, 0, 0, 0});
	inter = intersection_point(ray, closest.distance);
	closest_normal = get_obj_normal(closest.obj, inter, ray);
	color = light_effects(data, closest_normal, closest, ray);
	if (depth <= 0 || closest.reflect <= 0)
		return (color);
	// ray.origin = inter;
	// ray.dir = reflection_dir(closest_normal, \
	// 	substract_vect((vector3){0, 0, 0}, ray.dir));
	// refleccolor = ray_trace(data, ray, depth - 1);
	return color;//(reflection_color(color, refleccolor, closest.reflect, 0.75));
}
