#include "../../include/minirt.h"

void    intersection_cylinders(ray *r, cylinder **cylinders, hit *l_hit)
{
    cylinder   *iter_cylinders;
    
    iter_cylinders = *cylinders;
    while (iter_cylinders != NULL)
    {   
        if (intersect_ray_cylinder(r, iter_cylinders, &l_hit->dist))
        {
            if (l_hit->dist < l_hit->min_dist || l_hit->intersect == 0)
            {
                l_hit->min_dist = abs(l_hit->dist);
                l_hit->final_color = iter_cylinders->color;
            }
            l_hit->intersect = 1;
        }
        iter_cylinders = iter_cylinders->next;
    }
}

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
int intersect_ray_cylinder(ray *r, cylinder *cl, float *t) {
    // Definimos los puntos extremos del cilindro
    vector3 a = cl->center;
    vector3 b = sum_v3(cl->center, scale_v3(cl->direction, cl->height));
    vector3 ba = substract_v3(b, a);  // Asegúrate de que sea (b - a)
    double baba = dot_product_v3(ba, ba);

    // Definimos vectores auxiliares para los cálculos
    vector3 oc = substract_v3(r->origin, a);
    double bard = dot_product_v3(ba, r->direction);
    double baoc = dot_product_v3(ba, oc);
    double k2 = baba - bard * bard;
    double k1 = baba * dot_product_v3(oc, r->direction) - baoc * bard;
    double k0 = baba * dot_product_v3(oc, oc) - baoc * baoc - 
                (cl->diameter / 2) * (cl->diameter / 2) * baba;

    double discr = k1 * k1 - k2 * k0;

    *t = -1;
    if (discr < 0)
        return 0;

    discr = sqrt(discr);
    double t0 = (-k1 - discr) / k2;
    double t1 = (-k1 + discr) / k2;

    double y0 = baoc + t0 * bard;
    double y1 = baoc + t1 * bard;

    if ((y0 < 0 || y0 > baba) && (y1 < 0 || y1 > baba))
        return 0;

    if (y0 >= 0 && y0 <= baba)
        *t = t0;
    else
        *t = t1;

    return (fabs(*t) >= 0);
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
