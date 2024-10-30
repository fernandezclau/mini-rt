#include "../../include/minirt.h"

/**
 * @brief Checks for intersections between a ray and a list of spheres.
 * If an intersection is found, updates the hit record with the distance to the 
 * closest intersection point and the color of the intersecting sphere.
 * 
 * @param r The ray being tested for intersections.
 * @param spheres A pointer to a linked list of spheres to test against.
 * @param l_hit A pointer to the hit record to update with intersection details.
 */
void    intersection_spheres(ray *r, sphere **spheres, hit *l_hit)
{
    sphere   *iter_spheres;
    
    iter_spheres = *spheres;
    while (iter_spheres != NULL)
    {   
        if (intersect_ray_sphere(r, iter_spheres, &l_hit->dist))
        {
            if (l_hit->dist < l_hit->min_dist || l_hit->intersect == 0)
            {
                l_hit->min_dist = l_hit->dist;
                l_hit->final_color = iter_spheres->color;
                l_hit->position = sum_v3(r->origin, scale_v3(r->direction, l_hit->min_dist));
                l_hit->on_object = is_on_sphere(*iter_spheres, l_hit->position);
                l_hit->normal = normalize_v3(substract_v3(l_hit->position, iter_spheres->center));
            }
            l_hit->intersect = 1;
        }
        iter_spheres = iter_spheres->next;
    }
} 

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
int intersect_ray_sphere(ray *r, sphere *sphere, float *t)
{
    vector3 oc;
    float   a;
    float   b;
    float   c;
    float   discriminant;
    
    oc = substract_v3(r->origin, sphere->center);
    a = dot_product_v3(r->direction, r->direction);
    b = 2.0f * dot_product_v3(oc, r->direction);
    c = dot_product_v3(oc, oc) - (sphere->radius * sphere->radius);
    discriminant = b * b - 4 * a * c;
    if (discriminant >= 0)
    {
        *t = (-b - sqrt(discriminant)) / (2 * a);
        if(t >= 0)
            return 1;
    }
    return (0);
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
