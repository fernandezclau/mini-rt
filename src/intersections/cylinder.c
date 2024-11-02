#include "../../include/minirt.h"
#define EPSILON 0.0001

void    set_cylinder_normal(ray *r, cylinder *cy, hit *l_hit);
int     intersect_circle(ray *r, vector3 center, vector3 normal, float radius, float *t);

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
                l_hit->min_dist = l_hit->dist;
                l_hit->final_color = iter_cylinders->color;
                set_cylinder_normal(r, iter_cylinders, l_hit);
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
int intersect_ray_cylinder(ray *r, cylinder *cl, float *t)
{
    // Variables temporales para almacenar los valores de intersección
    float t_top, t_bottom, t_body;
    int hit_top = 0, hit_bottom = 0, hit_body = 0;

    // Normalizar la dirección del cilindro
    vector3 normalized_direction = normalize_v3(cl->direction);

    // Definir los puntos extremos del cilindro usando la dirección normalizada
    vector3 a = cl->center;
    vector3 b = sum_v3(a, scale_v3(normalized_direction, cl->height));

    // Recalcular el vector ba y su magnitud cuadrada (baba)
    vector3 ba = substract_v3(b, a);
    float baba = dot_product_v3(ba, ba);  // Debería ser equivalente a cl->height * cl->height

    // Comprobar intersección con la tapa superior
    vector3 c_center = sum_v3(cl->center, scale_v3(normalized_direction, cl->height));
    if (intersect_circle(r, c_center, normalized_direction, cl->diameter / 2, &t_top) && t_top >= 0)
        hit_top = 1;

    // Comprobar intersección con la tapa inferior
    vector3 c2_center = cl->center;
    if (intersect_circle(r, c2_center, normalized_direction, cl->diameter / 2, &t_bottom) && t_bottom >= 0)
        hit_bottom = 1;

    // Definir vectores auxiliares para los cálculos
    vector3 oc = substract_v3(r->origin, a);
    float bard = dot_product_v3(ba, r->direction);
    float baoc = dot_product_v3(ba, oc);
    float k2 = baba - bard * bard;
    float k1 = baba * dot_product_v3(oc, r->direction) - baoc * bard;
    float k0 = baba * dot_product_v3(oc, oc) - baoc * baoc - 
               (cl->diameter / 2) * (cl->diameter / 2) * baba;

    float discr = k1 * k1 - k2 * k0;

    // Comprobar intersección con el cuerpo del cilindro
    if (discr >= 0) {
        discr = sqrt(discr);
        float t0 = (-k1 - discr) / k2;
        float t1 = (-k1 + discr) / k2;

        float y0 = baoc + t0 * bard;
        float y1 = baoc + t1 * bard;

        // Verificar si las intersecciones están dentro de los límites del cilindro
        if (y0 >= 0 && y0 <= baba) {
            t_body = t0;
            hit_body = 1;
        }
        if (y1 >= 0 && y1 <= baba) {
            if (!hit_body || t1 < t_body) {
                t_body = t1;
                hit_body = 1;
            }
        }
    }

    *t = -1;
    if (hit_top && (t_top < *t || *t < 0)) *t = t_top;
    if (hit_bottom && (t_bottom < *t || *t < 0)) *t = t_bottom;
    if (hit_body && (t_body < *t || *t < 0)) *t = t_body;

    return (*t >= 0);
}

// int intersect_ray_cylinder(ray *r, cylinder *cl, float *t)
// {
//     // Variables temporales para almacenar los valores de intersección
//     float t_top, t_bottom, t_body;
//     int hit_top = 0, hit_bottom = 0, hit_body = 0;

//     // Comprobar intersección con la tapa superior
//     vector3 c_center = sum_v3(cl->center, scale_v3(cl->direction, cl->height));
//     if (intersect_circle(r, c_center, cl->direction, cl->diameter / 2, &t_top) && t_top >= 0)
//         hit_top = 1;

//     // Comprobar intersección con la tapa inferior
//     vector3 c2_center = cl->center;
//     if (intersect_circle(r, c2_center, cl->direction, cl->diameter / 2, &t_bottom) && t_bottom >= 0)
//         hit_bottom = 1;
    
//     // Definir puntos extremos del cilindro
//     vector3 a = cl->center;
//     vector3 b = sum_v3(cl->center, scale_v3(cl->direction, cl->height));
//     vector3 ba = substract_v3(b, a);
//     float baba = dot_product_v3(ba, ba);

//     // Definir vectores auxiliares para los cálculos
//     vector3 oc = substract_v3(r->origin, a);
//     float bard = dot_product_v3(ba, r->direction);
//     float baoc = dot_product_v3(ba, oc);
//     float k2 = baba - bard * bard;
//     float k1 = baba * dot_product_v3(oc, r->direction) - baoc * bard;
//     float k0 = baba * dot_product_v3(oc, oc) - baoc * baoc - 
//                (cl->diameter / 2) * (cl->diameter / 2) * baba;

//     float discr = k1 * k1 - k2 * k0;

//     // Comprobar intersección con el cuerpo del cilindro
//     if (discr >= 0) {
//         discr = sqrt(discr);
//         float t0 = (-k1 - discr) / k2;
//         float t1 = (-k1 + discr) / k2;

//         float y0 = baoc + t0 * bard;
//         float y1 = baoc + t1 * bard;

//         // Verificar si las intersecciones están dentro de los límites del cilindro
//         if (y0 >= 0 && y0 <= baba) {
//             t_body = t0;
//             hit_body = 1;
//         }
//         if (y1 >= 0 && y1 <= baba) {
//             if (!hit_body || t1 < t_body) {
//                 t_body = t1;
//                 hit_body = 1;
//             }
//         }
//     }

//     *t = -1;
//     if (hit_top && (t_top < *t || *t < 0)) *t = t_top;
//     if (hit_bottom && (t_bottom < *t || *t < 0)) *t = t_bottom;
//     if (hit_body && (t_body < *t || *t < 0)) *t = t_body;

//     return (*t >= 0);
// }


int intersect_circle(ray *r, vector3 center, vector3 normal, float radius, float *t) {
    vector3 OC = substract_v3(center, r->origin);
    float denom = dot_product_v3(r->direction, normal);

    if (fabs(denom) < 1e-6) {
        return 0;  // El rayo es paralelo al plano del círculo
    }

    float t_intersect = dot_product_v3(OC, normal) / denom;
    if (t_intersect < 0) {
        return 0;  // Intersección detrás del origen del rayo
    }

    vector3 intersectionPoint = sum_v3(r->origin, scale_v3(r->direction, t_intersect));
    float distanceToCenter = length_v3(substract_v3(intersectionPoint, center));
    if (distanceToCenter > radius) {
        return 0;  // Punto fuera del círculo
    }

    *t = t_intersect;
    return 1;
}

// Función para configurar la normal en el punto de intersección con el cilindro
void set_cylinder_normal(ray *r, cylinder *cy, hit *l_hit) {
    vector3 baseToPoint = substract_v3(l_hit->position, cy->center);
    float distance = dot_product_v3(baseToPoint, cy->direction);
    float epsilon = 0.0001f;

    if (distance <= epsilon) {
        l_hit->normal = negate_v3(cy->direction);  // Tapa inferior
    } else if (distance < cy->height + epsilon) {
        vector3 projectedPoint = sum_v3(cy->center, scale_v3(cy->direction, distance));
        l_hit->normal = normalize_v3(substract_v3(l_hit->position, projectedPoint));  // Superficie lateral
    } else {
        l_hit->normal = cy->direction;  // Tapa superior
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
