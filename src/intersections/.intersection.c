// vector3 oc;
    // float   a;
    // float   b;
    // float   c;
    // float   discriminant;
    // float   t1;
    // float   t2;
    
    // oc = substract_v3(r->origin, sp->center);
    // a = dot_product_v3(r->direction, r->direction);
    // b = 2.0f * dot_product_v3(oc, r->direction);
    // c = dot_product_v3(oc, oc) - (sp->radius * sp->radius);
    // discriminant = b * b - 4 * a * c;
    // if (discriminant < 0)
    //     return 0;
    // t1 = (-b - sqrt(discriminant)) / (2 * a);
    // t2 = (-b + sqrt(discriminant)) / (2 * a);
    // if (t1 > 0 && t2 > 0)
    //     hit->dist = fmin(t1, t2);
    // else if (t1 > 0)
    //     hit->dist = t1;
    // else if (t2 > 0)
    //     hit->dist = t2;
    // else
    //     return (0);
    // hit->position = sum_v3(r->origin, scale_v3(r->direction, hit->dist));
    // return (1); 
//     void set_plane_normal(ray *r, hit *l_hit, plane *pl)
// {
//     l_hit->normal = normalize_v3(pl->normal);
//     if (dot_product_v3(r->direction, l_hit->normal) > 0)
//         l_hit->normal = scale_v3(l_hit->normal, -1);
// }
    // int intersect_ray_plane(ray *r, plane *pl, hit *hit)
    // {
    //     float		denom;
    //     vector3	point_origin;
    //     vector3	scaled_direction;

    //     pl->normal = normalize_v3(pl->normal);
    //     denom = dot_product_v3(r->direction, pl->normal);
    //     if (fabs(denom) < EPSILON)
    //         return (0);
    //     point_origin = substract_v3(pl->point, r->origin);
    //     hit->dist = dot_product_v3(pl->normal, point_origin) / denom;
    //     scaled_direction = scale_v3(r->direction, hit->dist);
    //     hit->position = sum_v3(r->origin, scaled_direction);
    //     return (1);
    // }
    // vector3	oc;
	// float	a;
	// float	b;
	// float	c;
	// float	discriminant;

	// oc = substract_v3(r->origin, sp->center);
	// a = dot_product_v3(r->direction, r->direction);
	// b = 2.0f * dot_product_v3(oc, r->direction);
	// c = dot_product_v3(oc, oc) - (sp->radius * sp->radius);
	// discriminant = b * b - 4 * a * c;
	// if (discriminant >= 0)
	// {
	// 	hit->dist = (-b - sqrt(discriminant)) / (2 * a);
	// 	if (hit->dist >= 0)
	// 		return (1);
	// }
	// hit->position = sum_v3(r->origin, scale_v3(r->direction, hit->dist));
	// return (0);
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