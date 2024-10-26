#include "../../include/minirt.h"

void   calculate_light(scene *scene)
{
    color intensity;
    light   *iter_light;
    hit     hit;
    ambient_light al;
    vector3 point_to_l;

    al = scene->ambient_light;
    hit = scene->hit;
    iter_light = scene->lights;

    intensity = calculate_ambient_light(al);
    while (iter_light != NULL)
    {
        // TODO   
        iter_light = iter_light->next;
    }
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

