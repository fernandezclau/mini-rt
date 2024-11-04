#include "../../include/minirt.h"

/**
 * @brief Calculates the diffuse intensity of light at a point.
 * 
 * @param normal Vector representing the surface normal at the point.
 * @param p_to_l Vector pointing from the point to the light source.
 * @param light Vector representing the light intensity.
 * @return vector3 The diffuse intensity vector at the point.
 */
vector3	diffuse_intensity(vector3 normal, vector3 p_to_l, vector3 light)
{
	vector3	diffuse;
	float	ratio;

	ratio = fmax(dot_product_v3(p_to_l, normal), 0);
	diffuse = scale_v3(light, ratio);
	return (diffuse);
}

/**
 * @brief Calculates the specular intensity of light at a point.
 * 
 * @param normal Vector representing the surface normal at the point.
 * @param p_to_l Vector pointing from the point to the light source.
 * @param light Vector representing the light intensity.
 * @return vector3 The specular intensity vector at the point.
 */
vector3	specular_intensity(vector3 normal, vector3 p_to_l, vector3 light)
{
	float	ratio;
	vector3	specular;

	ratio = fmax(dot_product_v3(p_to_l, normal), 0);
	specular = scale_v3(light, pow(ratio, 70) * 3);
	return (specular);
}
/*
int is_in_shadow(vector3 point, light *light_source, scene *scene)
{
    vector3 view_direction = normalize_v3(substract_v3(scene->camera.position, scene->hit.position));
	vector3 light_direction = normalize_v3(substract_v3(light_source->position, scene->hit.position));

    float light_distance = length_v3(substract_v3(light_source->position, scene->hit.position));

    ray shadow_ray;
    const float bias = 0.01f; // Ajusta este valor según el tamaño de la escena
	shadow_ray.origin = sum_v3(point, scale_v3(scene->hit.normal, bias));
    shadow_ray.direction = light_direction;

    hit original_hit = scene->hit;

    int in_shadow = 0;
	ray_intersection(shadow_ray, scene);
    if (scene->hit.intersect) {
        if (scene->hit.dist < light_distance) {
            in_shadow = 1;
        }
    }

    // Restaurar el hit original
    //scene->hit = original_hit;

    return in_shadow;
}*/
