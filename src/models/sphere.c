#include "../../include/minirt.h"

/**
 * @brief Intersects a ray with a sphere.
 *
 * @param r A pointer to a ray structure containing the origin and direction of the ray.
 * @param center A pointer to a vector3 structure representing the center of the sphere.
 * @param radius The radius of the sphere.
 * @param t A pointer to a float where the distance to the intersection point will be stored.
 *          If there is no intersection, the value pointed to by t is not modified.
 * @return Returns 1 if the ray intersects the sphere and sets t to the distance to the intersection.
 *         Returns 0 if there is no intersection.
 */
int intersect_ray_sphere(ray *r, vector3 *center, float radius, float *t)
{
    vector3 oc = {r->origin.x - center->x, r->origin.y - center->y, r->origin.z - center->z};
    
    float a = (r->direction.x * r->direction.x) +
              (r->direction.y * r->direction.y) +
              (r->direction.z * r->direction.z);
    
    float b = 2.0f * (oc.x * r->direction.x + oc.y * r->direction.y + oc.z * r->direction.z);
    
    float c = (oc.x * oc.x + oc.y * oc.y + oc.z * oc.z) - (radius * radius);
    
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return 0;
    } else {
        *t = (-b - sqrt(discriminant)) / (2.0f * a);
        return 1;
    }
}

/**
 * @brief Adds a sphere to the end of the sphere linked list.
 *
 * @param head A pointer to a pointer to the head of the sphere linked list.
 * @param new_sphere A pointer to the new sphere to be added.
 */
void add_sphere(sphere **head, sphere *new_sphere)
{
    if (*head == NULL)
        *head = new_sphere;
    else 
    {
        sphere *last = *head;
        while (last->next != NULL)
              last = last->next;
        last->next = new_sphere;
    }
}

/**
 * @brief Frees the memory allocated for the sphere linked list.
 *
 * @param head A pointer to a pointer to the head of the sphere linked list.
 */
void free_spheres(sphere **head)
{
    sphere *current = *head;
    sphere *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

/**
 * @brief Prints the information of all spheres in the linked list.
 *
 * @param sp A pointer to the head of the sphere linked list.
 */
void display_spheres(sphere *sp)
{
    sphere *current = sp;
    int i = 1;
    printf(" %s____ SPHERES ____ %s\n", WH, RE);
    printf("\n");
    
    while (current)
    {
        printf("%s %d. %s\n", WH, i, RE);
        printf("\n");
        printf("%s > Center %s", WH, RE);
        display_v3(current->center);
        printf("\n");
        printf("%s > Diameter %s", WH, RE);
        printf("%s[%f]%s\n", CY, current->diameter, RE);
        printf("\n");
        printf("%s > Color %s", WH, RE);
        display_color(current->color);
        printf("\n");
        current = current->next;
        i++;
    }
}
