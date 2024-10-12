#include "../../include/minirt.h"

/**
 * @brief Intersects a ray with a plane.
 *
 * @param r A pointer to a ray structure containing the origin and direction of the ray.
 * @param point_on_plane A pointer to a vector3 structure representing a point on the plane.
 * @param normal A pointer to a vector3 structure representing the normal of the plane.
 * @param t A pointer to a float where the distance to the intersection point will be stored.
 *          If there is no intersection, the value pointed to by t is not modified.
 * @return Returns 1 if the ray intersects the plane and sets t to the distance to the intersection.
 *         Returns 0 if there is no intersection or if the ray is parallel to the plane.
 */
int intersect_ray_plane(ray *r, vector3 *point_on_plane, vector3 *normal, float *t)
{
    float denom = normal->x * r->direction.x + normal->y * r->direction.y + normal->z * r->direction.z;

    if (fabs(denom) > 1e-6) {
        vector3 p0l0 = {point_on_plane->x - r->origin.x,
                         point_on_plane->y - r->origin.y,
                         point_on_plane->z - r->origin.z};

        *t = (normal->x * p0l0.x + normal->y * p0l0.y + normal->z * p0l0.z) / denom;

        return (*t >= 0);
    }
    return 0;
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
