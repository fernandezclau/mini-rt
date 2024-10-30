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
void    interesection_planes(ray *r, plane **planes, hit *l_hit)
{
    plane   *iter_planes;
    
    iter_planes = *planes;
    while (iter_planes != NULL)
    {   
        if (intersect_ray_plane(r, iter_planes, &l_hit->dist))
        {
            if (l_hit->dist < l_hit->min_dist || l_hit->intersect == 0)
            {
                l_hit->min_dist = l_hit->dist;
                l_hit->final_color = iter_planes->color;
                l_hit->position = sum_v3(r->origin, scale_v3(r->direction, l_hit->min_dist));
                set_plane_normal(r, l_hit, iter_planes);
                l_hit->is_plane = 1;
	            l_hit->on_object = is_on_plane(*iter_planes, l_hit->position);
            }
            l_hit->intersect = 1;
        }
        iter_planes = iter_planes->next;
    }
}

/**
 * @brief Intersects a ray with a plane.
 *
 * @param r A pointer to a ray structure containing the origin and direction of the ray.
 * @param point_on_plane A pointer to a vector3 structure representing a point on the plane.
 * @param normal A pointer to a vector3 structure representing the normal of the plane.
 * @param t A pointer to a float where the distance to the intersection point will be stored.
 * @return Returns 1 if the ray intersects the plane and sets t to the distance to the intersection.
 *         Returns 0 if there is no intersection or if the ray is parallel to the plane.
 */
int intersect_ray_plane(ray *r, plane *pl, float *t)
{
    double  denom;
    vector3 p0l0;

    denom = dot_product_v3(r->direction, pl->normal);
    if (fabs(denom) > 1e-6)
    {
        p0l0 = substract_v3(pl->point, r->origin);
        *t = dot_product_v3(pl->normal, p0l0) / denom;
        return (*t >= 0);
    }
    return 0;
}

/**
 * @brief Adjusts the normal of a plane at the intersection point to ensure
 * it faces against the ray direction for correct shading.
 * 
 * @param r The ray intersecting with the plane.
 * @param l_hit The hit record containing intersection details, including the plane's normal.
 */
void    set_plane_normal(ray *r, hit *l_hit, plane *pl)
{
    l_hit->normal = pl->normal;
	if (dot_product_v3(r->direction, pl->normal) > 0)
		l_hit->normal = substract_v3((vector3){0, 0, 0}, pl->normal);
}

/**
 * @brief Adds a plane to the end of the plane linked list.
 *
 * @param head A pointer to a pointer to the head of the plane linked list.
 * @param new_plain A pointer to the new plane to be added.
 */
void add_plane(plane **head, plane *new_plain)
{
    if (*head == NULL)
        *head = new_plain;
    else 
    {
        plane *last = *head;
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
void free_plane(plane **head)
{
    plane *current = *head;
    plane *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

/**
 * @brief Prints the information of all planes in the linked list.
 *
 * @param pl A pointer to the head of the plane linked list.
 */
void display_planes(plane *pl)
{
    plane *current = pl;
    int i = 1;
    printf(" %s____ PLANES ____ %s\n", WH, RE);
    printf("\n");
    
    while (current)
    {
        printf("%s %d. %s\n", WH, i, RE);
        printf("\n");
        printf("%s > Point %s", WH, RE);
        display_v3(current->point);
        printf("\n");
        printf("%s > Normal %s", WH, RE);
        display_v3(current->normal);
        printf("\n");
        printf("%s > Color %s", WH, RE);
        display_color(current->color);
        printf("\n");
        current = current->next;
        i++;
    }
}
