#include "../../include/minirt.h"

void	init_ugh_cylinder(ugh *top_cap, ugh *cylinder_cap, ugh *bottom_cap, \
		cylinder *cl)
{
	cl->direction = normalize_v3(cl->direction);
	top_cap->distance = FLT_MAX;
	cylinder_cap->distance = FLT_MAX;
	bottom_cap->distance = FLT_MAX;
	top_cap->center = sum_v3(cl->center, scale_v3(cl->direction, cl->height));
	bottom_cap->center = cl->center;
	top_cap->direction = cl->direction;
	bottom_cap->direction = scale_v3(cl->direction, -1);
}

int	cylinder_calculations(vector3 d_perp, vector3 w_perp, \
		cylinder *cl, float *d)
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

int	select_dist_cylinder(ugh cylinder_body, ugh top_cap, \
		ugh bottom_cap, hit *hit)
{
	if (cylinder_body.distance <= top_cap.distance)
	{
		if (cylinder_body.distance <= bottom_cap.distance)
		{
			if (cylinder_body.distance != FLT_MAX)
			{
				hit->dist = cylinder_body.distance;
				hit->position = cylinder_body.position;
				return (1);
			}
		}
		else
		{
			if (bottom_cap.distance != FLT_MAX)
			{
				hit->dist = bottom_cap.distance;
				hit->position = bottom_cap.position;
				return (1);
			}
		}
	}
	return (0);
}

int	select_dist_cylinder2(ugh top_cap, ugh bottom_cap, hit *hit)
{
	if (top_cap.distance <= bottom_cap.distance)
	{
		if (top_cap.distance != FLT_MAX)
		{
			hit->dist = top_cap.distance;
			hit->position = top_cap.position;
			return (1);
		}
	}
	else
	{
		if (bottom_cap.distance != FLT_MAX)
		{
			hit->dist = bottom_cap.distance;
			hit->position = bottom_cap.position;
			return (1);
		}
	}
	return (0);
}

// Intersección de un rayo con un círculo
int	intersect_circle(ray *r, ugh *ugh, float radius)
{
	vector3	oc;
	float	denom;
	float	t;
	vector3	intersect_point;
	float	distance_center;

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
