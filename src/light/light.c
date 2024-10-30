#include "../../include/minirt.h"

vector3 final_intensity(light light, vector3 normal, vector3 p_to_l);

vector3	intersection_point(ray ray, double distance)
{
	vector3	intersection;

	intersection = sum_v3(ray.origin, \
		scale_v3(ray.direction, distance));
	return (intersection);
}

color   calculate_light(ray r, scene *scene)
{
    vector3 intensity;
    light   *iter_light;
    hit     hit;
    ambient_light al;
    vector3 point_to_l;
    vector3 p_intensity;
    color c = {0, 0, 0};

    al = scene->ambient_light;
    hit = scene->hit;
    iter_light = scene->lights;
    vector3 point = intersection_point(r, hit.min_dist);
    intensity = calculate_ambient_light(al);
    while (iter_light != NULL)
    {
        point_to_l = normalize_v3(substract_v3(iter_light->position, point));
        p_intensity = final_intensity(*iter_light, hit.normal, point_to_l);
        if (is_in_shadow(point, scene->lights, scene))
            p_intensity = scale_v3(p_intensity, 0);
        intensity = sum_v3(intensity, p_intensity);
        iter_light = iter_light->next;
    }
    c.r = hit.final_color.r * intensity.x;
    c.g = hit.final_color.g * intensity.y;
    c.b = hit.final_color.b * intensity.z;
    return (c);
}

vector3 final_intensity(light light, vector3 normal, vector3 p_to_l)
{
    vector3 light_intensity;
    vector3 diffuse;
    vector3 specular;
    vector3 intensity;

    light_intensity = calculate_intensity(light.color, light.brightness);
    specular = specular_intensity(normal, p_to_l, light_intensity);
    diffuse = diffuse_intensity(normal, p_to_l, light_intensity);
    
    return (sum_v3(specular, diffuse));
}
/**
 * @brief Calculates the effect of ambient light on a given color.
 *
 * @param color Pointer to the color structure that will be modified to 
 *              incorporate the ambient light effect.
 * @param light The ambient light structure containing the color and ratio 
 *              of the ambient light.
*/
vector3 calculate_intensity(color colour, float ratio)
{
    vector3 intensity;
    int     sum_color;

    sum_color = colour.r + colour.g + colour.b;
    intensity.x = INTENSITY_RATIO * 3 * ratio * colour.r / sum_color;
    intensity.y = INTENSITY_RATIO * 3 * ratio * colour.g / sum_color;
    intensity.z = INTENSITY_RATIO * 3 * ratio * colour.b / sum_color;

    return (intensity);
}
/**
 * @brief Initializes a light structure to default values.
 *
 * @param l A pointer to the light structure to be initialized.
 */
void init_light(light *l)
{
    init_r_v3(&l->position);
    init_r_color(&l->color);
    l->brightness = 0;
}

/**
 * @brief Adds a plane to the end of the plane linked list.
 *
 * @param head A pointer to a pointer to the head of the plane linked list.
 * @param new_light A pointer to the new plane to be added.
 */
void add_light(light **head, light *new_light)
{
    if (*head == NULL)
        *head = new_light;
    else 
    {
        light *last = *head;
        while (last->next != NULL)
              last = last->next;
        last->next = new_light;
    }
}

/**
 * @brief Frees the memory allocated for the light linked list.
 *
 * @param head A pointer to a pointer to the head of the light linked list.
 */
void free_lights(light **head)
{
    light *current = *head;
    light *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

/**
 * @brief Displays the details of a light structure.
 *
 * @param l The light structure to be displayed.
 */
void display_light(light *l)
{
    int     i;
    light   *current; 
    
    current = l;
    i = 1;
    printf(" %s____ LIGHT ____ %s\n", WH, RE);
    printf("\n");
    while (current)
    {
        printf("%s %d. %s\n", WH, i, RE);
        printf("\n");
        printf("%s > Position %s", WH, RE);
        display_v3(current->position);
        printf("\n");
        printf("%s > Brightness %s", WH, RE);
        printf("%s[%f]%s\n", CY, current->brightness, RE);
        printf("\n");
        printf("%s > Color %s", WH, RE);
        display_color(current->color);
        printf("\n");
        current = current->next;
        i++;
    }
}

