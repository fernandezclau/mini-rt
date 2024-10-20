#include "../../include/minirt.h"

/**
 * @brief Processes camera parameters from tokens and updates the camera structure.
 *
 * @param tokens An array of strings containing the camera parameters.
 * @param camera A pointer to the camera structure to be updated.
 * @return int Returns 1 on success, 0 on failure (e.g., incorrect token count).
 */
int process_camera(char **tokens, camera *camera)
{
    if (array_len(tokens) != 4)
        return 0;

    // POSITION
    char    **position = ft_split(tokens[1], ',');
    if (!insert_vector3(&camera->position, position, NOT_NORMALIZED))
        return 0;
    
    // DIRECTION
    char    **direction = ft_split(tokens[2], ',');
    if (!insert_vector3(&camera->direction, direction, NORMALIZED))
        return 0; 

    // FOV
    if (!insert_angle(&camera->fov, tokens[3]))
        return 0;

    return 1;
}

/**
 * @brief Processes ambient light parameters from tokens and updates the ambient light structure.
 *
 * @param tokens An array of strings containing the ambient light parameters.
 * @param ambient_light A pointer to the ambient light structure to be updated.
 * @return int Returns 1 on success, 0 on failure (e.g., incorrect token count).
 */
int process_ambient(char **tokens, ambient_light *ambient_light)
{
    if (array_len(tokens) != 3)
        return 0;
    
    //LIGHTNING RATIO
    insert_ratio(&ambient_light->ratio, tokens[1]);
    
    //COLOR
    char **colors = ft_split(tokens[2], ',');
    if (!insert_color(&ambient_light->color, colors))
         return 0;

    return 1;
}

/**
 * @brief Processes light parameters from tokens and updates the light structure.
 *
 * @param tokens An array of strings containing the light parameters.
 * @param light A pointer to the light structure to be updated.
 * @return int Returns 1 on success, 0 on failure (e.g., incorrect token count).
 */
int process_light(char **tokens, light *light)
{
    if (array_len(tokens) != 4)
        return 0;

    // POSITION
    char    **position = ft_split(tokens[1], ',');
    if (!insert_vector3(&light->position, position, NOT_NORMALIZED))
        return 0;

    // BRIGTHNESS RATIO 
    insert_ratio(&light->brightness, tokens[2]);

    // COLOR
    char **colors = ft_split(tokens[3], ',');
    if (!insert_color(&light->color, colors))
         return 0;

    return 1;
}

/**
 * @brief Processes sphere parameters from tokens and adds a new sphere to the list.
 *
 * @param tokens An array of strings containing the sphere parameters.
 * @param sp A double pointer to the head of the sphere linked list.
 * @return int Returns 1 on success, 0 on failure (e.g., incorrect token count or memory allocation failure).
 */
int process_sphere(char **tokens, sphere **sp)
{
    sphere *new_sphere = NULL;

    if (array_len(tokens) != 4)
        return 0;

    new_sphere = (sphere *)malloc(sizeof(sphere));
    if (!new_sphere)
        return 0;

    // CENTER
    char **position = ft_split(tokens[1], ',');
    if (!insert_vector3(&new_sphere->center, position, NOT_NORMALIZED))
        return free(new_sphere), 0;

    // DIAMETER
    if (!insert_magnitude(&new_sphere->diameter, tokens[2]))
        return free(new_sphere), 0;
    
    // RADIOUS
    new_sphere->radius = new_sphere->diameter / 2.0f;

    // // COLOR
    char **colors = ft_split(tokens[3], ',');
    if (!insert_color(&new_sphere->color, colors))
        return free(new_sphere), 0;

    // // NEXT
    new_sphere->next = NULL;

    add_sphere(sp, new_sphere);

    return 1;
}

/**
 * @brief Processes plane parameters from tokens and adds a new plane to the list.
 *
 * @param tokens An array of strings containing the plane parameters.
 * @param pl A double pointer to the head of the plane linked list.
 * @return int Returns 1 on success, 0 on failure (e.g., incorrect token count or memory allocation failure).
 */
int process_plane(char **tokens, plane **pl)
{
    plane *new_plane = NULL;

    if (array_len(tokens) != 4)
        return 0;

    new_plane = (plane *)malloc(sizeof(plane));
    if (!new_plane)
        return 0;

    // POINT
    char **point = ft_split(tokens[1], ',');
    if (!insert_vector3(&new_plane->point, point, NOT_NORMALIZED))
        return free(new_plane), 0;

    // NORMAL
    char    **normal = ft_split(tokens[2], ',');
    if (!insert_vector3(&new_plane->normal, normal, NORMALIZED))
        return free(new_plane), 0;

    // COLOR
    char **colors = ft_split(tokens[3], ',');
    if (!insert_color(&new_plane->color, colors))
        return free(new_plane), 0;

    // NEXT
    new_plane->next = NULL;

    add_plane(pl, new_plane);

    return 1;
}

/**
 * @brief Processes cylinder parameters from tokens and adds a new cylinder to the list.
 *
 * @param tokens An array of strings containing the cylinder parameters.
 * @param cy A double pointer to the head of the cylinder linked list.
 * @return int Returns 1 on success, 0 on failure (e.g., incorrect token count or memory allocation failure).
 */
int process_cylinder(char **tokens, cylinder **cy)
{
    cylinder *new_cylinder = NULL;

    if (array_len(tokens) != 6)
        return 0;

    new_cylinder = (cylinder *)malloc(sizeof(cylinder));
    if (!new_cylinder)
        return 0;

    // CENTER
    char **center = ft_split(tokens[1], ',');
    if (!insert_vector3(&new_cylinder->center, center, NOT_NORMALIZED))
        return free(new_cylinder), 0;

    // DIRECCION
    char    **direction = ft_split(tokens[2], ',');
    if (!insert_vector3(&new_cylinder->direction, direction, NORMALIZED))
        return free(new_cylinder), 0;

    // DIAMETER
    if (!insert_magnitude(&new_cylinder->diameter, tokens[3]))
        return free(new_cylinder), 0;

    // HEIGHT
    if (!insert_magnitude(&new_cylinder->height, tokens[4]))
        return free(new_cylinder), 0;

    // COLOR
    char **colors = ft_split(tokens[5], ',');
    if (!insert_color(&new_cylinder->color, colors))
        return free(new_cylinder), 0;

    // NEXT
    new_cylinder->next = NULL;

    add_cylinder(cy, new_cylinder);

    return 1;
}