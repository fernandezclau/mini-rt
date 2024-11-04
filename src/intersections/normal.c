#include "../../include/minirt.h"

/**
 * @brief Adjusts the normal of a plane at the intersection point to ensure
 * it faces against the ray direction for correct shading.
 * 
 * @param r The ray intersecting with the plane.
 * @param l_hit The hit record.
 * @param pl The plane structure.
 */
void	set_plane_normal(ray *r, hit *l_hit, plane *pl)
{
	l_hit->normal = normalize_v3(pl->normal);
	if (dot_product_v3(r->direction, pl->normal) > 0)
		l_hit->normal = scale_v3(l_hit->normal, -1);
}

/**
 * @brief Adjusts the normal of a sphere at the intersection point to ensure
 * it faces against the ray direction for correct shading.
 * 
 * @param r The ray intersecting with the sphere.
 * @param l_hit The hit record.
 * @param pl The sphere structure.
 */
void	set_sphere_normal(ray *r, hit *l_hit, sphere *sp)
{
	l_hit->normal = normalize_v3(substract_v3(l_hit->position, sp->center));
}
