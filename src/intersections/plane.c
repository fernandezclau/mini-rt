#include "../../include/minirt.h"

/**
 * @brief Checks for intersections between a ray and a list of planes.
 * If an intersection is found, updates the hit record with the distance to the 
 * closest intersection point and the color of the intersecting plane.
 * 
 * @param r The ray being tested for intersections.
 * @param planes A pointer to a linked list of planes to test against.
 * @param l_hit A pointer to the hit record to update with intersection details.
 */
void	interesection_planes(ray *r, plane **planes, hit *l_hit)
{
	plane	*iter_planes;

	iter_planes = *planes;
	while (iter_planes != NULL)
	{
		if (intersect_ray_plane(r, iter_planes, l_hit))
		{
			if (l_hit->dist < l_hit->min_dist || l_hit->intersect == 0)
			{
				l_hit->min_dist = l_hit->dist;
				l_hit->final_color = iter_planes->color;
				set_plane_normal(r, l_hit, iter_planes);
			}
			l_hit->intersect = 1;
		}
		iter_planes = iter_planes->next;
	}
}

/**
 * @brief Intersects a ray with a plane.
 *
 * @param r Ray structure containing the origin and direction of the ray.
 * @param point_on_plane Vector3 structure representing a point on the plane.
 * @param normal Vector3 structure representing the normal of the plane.
 * @param hit Hit structure with intersection information.
 * @return Returns 1 if the ray intersects.
 *         Returns 0 if there is no intersection.
 */
int	intersect_ray_plane(ray *r, plane *pl, hit *hit)
{
	float	denom;
	vector3	point_origin;
	vector3	scaled_direction;

	pl->normal = normalize_v3(pl->normal);
	denom = dot_product_v3(r->direction, pl->normal);
	if (fabs(denom) < EPSILON_4)
		return (0);
	point_origin = substract_v3(pl->point, r->origin);
	hit->dist = dot_product_v3(pl->normal, point_origin) / denom;
	scaled_direction = scale_v3(r->direction, hit->dist);
	hit->position = sum_v3(r->origin, scaled_direction);
	return (1);
}

/**
 * @brief Adds a plane to the end of the plane linked list.
 *
 * @param head A pointer to a pointer to the head of the plane linked list.
 * @param new_plain A pointer to the new plane to be added.
 */
void	add_plane(plane **head, plane *new_plain)
{
	plane	*last;

	if (*head == NULL)
		*head = new_plain;
	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_plain;
	}
}

/**
 * @brief Frees the memory allocated for the plane linked list.
 *
 * @param head A pointer to a pointer to the head of the plane linked list.
 */
void	free_plane(plane **head)
{
	plane	*current;
	plane	*next;

	current = *head;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}
