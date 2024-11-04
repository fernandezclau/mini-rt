#include "../../include/minirt.h"

void    set_cylinder_normal(ray *r, cylinder *cy, hit *l_hit);
int intersect_cylinder(const ray* r, const cylinder* cl, vector3* p, float* dist);
int intersect_circle( ray* r, vector3* p, float* dist, const vector3 c_center, const vector3 c_normal, float radius);

void    intersection_cylinders(ray *r, cylinder **cylinders, hit *l_hit)
{
    cylinder   *iter_cylinders;
    
    iter_cylinders = *cylinders;
    while (iter_cylinders != NULL)
    {   
        if (intersect_ray_cylinder(r, &l_hit->position, &l_hit->dist, iter_cylinders))
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
int intersect_ray_cylinder(ray *r, vector3 *p, float *dist, cylinder *cl)
{
    // Medir intersecciones con cada parte
    float dist_top = FLT_MAX, dist_cylinder = FLT_MAX, dist_bottom = FLT_MAX;
    vector3 p_top, p_cylinder, p_bottom;
    cl->direction = normalize_v3(cl->direction);
    intersect_circle(r, &p_top, &dist_top, sum_v3(cl->center, scale_v3(cl->direction, cl->height)), cl->direction, cl->diameter/2);
    intersect_cylinder(r, cl, &p_cylinder, &dist_cylinder);
    intersect_circle(r, &p_bottom, &dist_bottom, cl->center, scale_v3(cl->direction, -1), cl->diameter/2);

    // Quedarse con la más cercana si la hubiese
    if (dist_cylinder <= dist_top) {
        if (dist_cylinder <= dist_bottom) {
            if (dist_cylinder != FLT_MAX) {
                *dist = dist_cylinder;
                *p = p_cylinder;
                return 1;
            }
        } else {
            if (dist_bottom != FLT_MAX) {
                *dist = dist_bottom;
                *p = p_bottom;
                return 1;
            }
        }
    } else {
        if (dist_top <= dist_bottom) {
            if (dist_top != FLT_MAX) {
                *dist = dist_top;
                *p = p_top;
                return 1;
            }
        } else {
            if (dist_bottom != FLT_MAX) {
                *dist = dist_bottom;
                *p = p_bottom;
                return 1;
            }
        }
    }

    // Si no, no hay intersección
    return 0;
}

// Intersección de un rayo con el cuerpo de un cilindro
int intersect_cylinder(const ray* r, const cylinder* cl, vector3* p, float* dist) {
    vector3 w = substract_v3(r->origin, cl->center);
    vector3 D_perp = substract_v3(r->direction, scale_v3(cl->direction, dot_product_v3(r->direction, cl->direction))); // Componente de D perpendicular a A
    vector3 w_perp = substract_v3(w, scale_v3(cl->direction, dot_product_v3(w, cl->direction))); // Componente de w perpendicular a A

    float a = dot_product_v3(D_perp, D_perp);
    float b = 2 * dot_product_v3(w_perp, D_perp);
    float c = dot_product_v3(w_perp, w_perp) - cl->diameter/2 * cl->diameter/2;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return 0; // No hay intersección
    }

    float sqrtDisc = sqrt(discriminant);
    float t1 = (-b + sqrtDisc) / (2 * a);
    float t2 = (-b - sqrtDisc) / (2 * a);

    // Selección manual del menor valor positivo de t (si ambos son positivos)
    float d;
    if (t1 > 0 && t2 > 0) {
        d = (t1 < t2) ? t1 : t2; // Selecciona el menor de los dos si ambos son positivos
    } else if (t1 > 0) {
        d = t1;
    } else if (t2 > 0) {
        d = t2;
    } else {
        return 0; // Ambos valores son negativos, intersección detrás del rayo
    }

    // Calcula el punto de intersección
    vector3 potentialIntersection = sum_v3(r->origin, scale_v3(r->direction, d));

    // Proyecta el vector desde el centro al punto en el eje del cilindro para verificar la altura
    float projectionOnAxis = dot_product_v3(substract_v3(potentialIntersection, cl->center), cl->direction);
    if (projectionOnAxis < 0 || projectionOnAxis > cl->height) {
        return 0; // La intersección está fuera de los límites de la altura del cilindro
    }

    // Si pasa todas las verificaciones, asigna el punto de intersección y la distancia
    *p = potentialIntersection;
    *dist = d;
    return 1;
}

// Intersección de un rayo con un círculo
int intersect_circle( ray* r, vector3* p, float* dist, const vector3 c_center, const vector3 c_normal, float radius)
{
    // Vector desde el origen del rayo al centro del círculo
    vector3 OC = substract_v3(c_center, r->origin);

    // Proyecta OC sobre la normal del plano para encontrar la distancia al plano
    float denom = dot_product_v3(r->direction, c_normal);

    // Verifica si el rayo es paralelo al plano
    if (fabs(denom) < 1e-6) {
        return 0; // El rayo es paralelo al plano del círculo, no intersecta
    }

    // Calcula el valor de t para la intersección con el plano
    float t = dot_product_v3(OC, c_normal) / denom;

    // Verifica si la intersección está detrás del origen del rayo
    if (t < 0) {
        return 0; // La intersección está detrás del rayo
    }

    // Calcula el punto de intersección en el plano
    vector3 intersectionPoint = sum_v3(r->origin, scale_v3(r->direction, t));

    // Verifica si el punto de intersección está dentro del radio del círculo
    float distanceToCenter = length_v3(substract_v3(intersectionPoint, c_center));
    if (distanceToCenter > radius) {
        return 0; // El punto está fuera del círculo
    }

    // Si pasa las verificaciones, asigna el punto y la distancia
    *p = intersectionPoint;
    *dist = t;
    return 1;
}

// Función para configurar la normal en el punto de intersección con el cilindro
void set_cylinder_normal(ray *r, cylinder *cy, hit *l_hit)
{
    vector3 base_to_point;
    float   distance;
    vector3 projected_point;
    
    base_to_point = substract_v3(l_hit->position, cy->center);
    distance = dot_product_v3(base_to_point, cy->direction);
    if (distance <= EPSILON_4)
        l_hit->normal = scale_v3(normalize_v3(cy->direction), -1);
    else if (distance < cy->height - EPSILON_4)
    {
        projected_point = sum_v3(cy->center, scale_v3(cy->direction, distance));
        l_hit->normal = normalize_v3(substract_v3(l_hit->position, projected_point));
    } else if (distance >= cy->height - EPSILON_4)
        l_hit->normal = normalize_v3(cy->direction);
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
