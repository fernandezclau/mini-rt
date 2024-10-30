#include "../../include/minirt.h"

int is_in_shadow(vector3 point, light *light_source, scene *scene)
{
    ray ray;
    ray.origin = point;
    ray.direction = normalize_v3(substract_v3(light_source->position, point));

    init_hit_point(&scene->hit);

    ray_intersection(ray, scene);
    if (scene->hit.is_plane)
		return 1;
    if (scene->hit.intersect && scene->hit.min_dist > 0)
		return 1;
    return 0;
}


int	is_on_plane(plane plane, vector3 point)
{
	vector3	normal;
	vector3	point_to_pl;

	normal = plane.normal;
	point_to_pl = normalize_v3(substract_v3(plane.point, point));
	if (fabs(dot_product_v3(point_to_pl, normal)) < 0)
		return (1);
	return (0);
}

int	is_on_sphere(sphere sphere, vector3 point)
{
	vector3	point_to_sp;
	double		radius;
	double		distance;

	point_to_sp = substract_v3(sphere.center, point);
	radius = sphere.radius;
	distance = fabs(length_v3(point_to_sp));
	if (distance <= radius + 0.01 && distance >= radius - 0.01)
		return (1);
	return (0);
}

int	is_on_cylinder(cylinder cylinder, vector3 point)
{
	vector3	center;
	vector3	axis;
	double		param;
	vector3	proj;

	center = cylinder.center;
	axis = cylinder.direction;
	param = (axis.x * (point.x - center.x) + axis.y * (point.y - center.y) \
		+ axis.z * (point.z - center.z)) \
		/ (axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
	proj = sum_v3(center, scale_v3(axis, param));
	if (length_v3(substract_v3(proj, point)) <= cylinder.diameter / 2 + 0.01
		&& length_v3(substract_v3(proj, center)) \
		<= cylinder.height + 0.01)
		return (1);
	return (0);
}
