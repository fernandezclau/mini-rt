#include "../../include/minirt.h"

int is_in_shadow(vector3 point, light *light_source, scene *scene) {
    // Dirección hacia la luz desde el punto de intersección
    vector3 view_direction = normalize_v3(substract_v3(scene->camera.position, scene->hit.position));
	vector3 light_direction = normalize_v3(substract_v3(light_source->position, scene->hit.position));

    float light_distance = length_v3(substract_v3(light_source->position, scene->hit.position));

    // Crear el rayo de sombra con un pequeño desplazamiento (bias)
    ray shadow_ray;
    const float bias = 0.01f; // Ajusta este valor según el tamaño de la escena
	shadow_ray.origin = sum_v3(point, scale_v3(scene->hit.normal, bias));
    shadow_ray.direction = light_direction;

    // Guardar el hit original
    hit original_hit = scene->hit;

    // Comprobar si el rayo de sombra interseca algún objeto
    int in_shadow = 0;
	ray_intersection(shadow_ray, scene);
    if (scene->hit.intersect) {
        // Si hay una intersección y está antes de la luz, está en sombra
        if (scene->hit.dist < light_distance) {
            in_shadow = 1;
        }
    }

    // Restaurar el hit original
    //scene->hit = original_hit;

    return in_shadow;
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
