#include "../../include/minirt.h"

/**
 * @brief Intersects a ray with a cylinder.
 *
 * @param r A pointer to a ray structure containing the origin and direction of the ray.
 * @param center A pointer to a vector3 structure representing the center of the cylinder.
 * @param radius The radius of the cylinder.
 * @param height The height of the cylinder.
 * @param t A pointer to a float where the distance to the intersection point will be stored.
 *          If there is no intersection, the value pointed to by t is not modified.
 * @return Returns 1 if the ray intersects the cylinder and sets t to the distance to the intersection.
 *         Returns 0 if there is no intersection or if the intersections are not valid.
 */
int intersect_ray_cylinder(ray *r, vector3 *center, float radius, float height, float *t) {
    vector3 oc = {r->origin.x - center->x, r->origin.y - center->y, r->origin.z - center->z};

    float a = r->direction.x * r->direction.x + r->direction.y * r->direction.y;
    float b = 2.0 * (oc.x * r->direction.x + oc.y * r->direction.y);
    float c = oc.x * oc.x + oc.y * oc.y - radius * radius;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return 0;
    } else {
        float t0 = (-b - sqrt(discriminant)) / (2.0 * a);
        float t1 = (-b + sqrt(discriminant)) / (2.0 * a);

        float z0 = r->origin.z + t0 * r->direction.z;
        float z1 = r->origin.z + t1 * r->direction.z;

        if (z0 >= center->z && z0 <= center->z + height) {
            *t = t0;
            return 1;
        }
        if (z1 >= center->z && z1 <= center->z + height) {
            *t = t1;
            return 1;
        }
        return 0;
    }
}

/**
 * @brief Adds a cylinder to the end of the cylinder linked list.
 *
 * @param head A pointer to a pointer to the head of the cylinder linked list.
 * @param new_cylinder A pointer to the new cylinder to be added.
 */
void add_cylinder(cylinder **head, cylinder *new_cylinder)
{
    if (*head == NULL)
        *head = new_cylinder;
    else 
    {
        cylinder *last = *head;
        while (last->next != NULL)
              last = last->next;
        last->next = new_cylinder;
    }
}

/**
 * @brief Frees the memory allocated for the cylinder linked list.
 *
 * @param head A pointer to a pointer to the head of the cylinder linked list.
 */
void free_cylinder(cylinder **head)
{
    cylinder *current = *head;
    cylinder *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

/**
 * @brief Prints the information of all cylinders in the linked list.
 *
 * @param cy A pointer to the head of the cylinder linked list.
 */
void display_cylinders(cylinder *cy)
{
    cylinder *current = cy;
    int i = 1;
    printf(" %s____ CYLINDERS ____ %s\n", WH, RE);
    printf("\n");
    
    while (current)
    {
        printf("%s %d. %s\n", WH, i, RE);
        printf("\n");
        printf("%s > Center %s", WH, RE);
        display_v3(current->center);
        printf("\n");
        printf("%s > Direction %s", WH, RE);
        display_v3(current->direction);
        printf("\n");
        printf("%s > Diameter %s", WH, RE);
        printf("%s[%f]%s\n", CY, current->diameter, RE);
        printf("\n");
        printf("%s > Height %s", WH, RE);
        printf("%s[%f]%s\n", CY, current->height, RE);
        printf("\n");
        printf("%s > Color %s", WH, RE);
        display_color(current->color);
        printf("\n");
        current = current->next;
        i++;
    }
}
