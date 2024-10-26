#include "../../include/minirt.h"

/**
 * @brief Initializes a scene by setting all its geometric shapes to NULL.
 *
 * @param scene A pointer to the scene structure to be initialized.
 */
void init_scene(scene *scene)
{
    // CAMERA INIT
    init_camera(&scene->camera);

    // LIGHT INIT
    scene->lights = NULL;

    // AMBIENT LIGHT INIT
    init_ambient_light(&scene->ambient_light);

    // SPHERE INIT
    scene->spheres = NULL;
    
    // PLANE INIT
    scene->planes = NULL;

    // CYLINDER INIT
    scene->cylinders = NULL;
}

/**
 * @brief Initializes a hit structure by setting all its parameters to NULL.
 *
 * @param hit A pointer to the hit structure to be initialized.
 */
void    init_hit_point(hit *hit)
{
    hit->intersect = 0;
    hit->min_dist = INFINITY;
    hit->reflection = REFLECT_RATIO;
    init_r_color(&hit->final_color);
}

/**
 * @brief Frees all allocated resources in the scene.
 *
 * @param scene A pointer to the scene structure to be freed.
 */
void free_scene(scene *scene)
{
    free_lights(&scene->lights);
    free_spheres(&scene->spheres);
    free_plane(&scene->planes);
    free_cylinder(&scene->cylinders);
}

/**
 * @brief Prints the details of the scene to the standard output.
 *
 * @param scene The scene structure containing all the scene elements to be displayed.
 */
void print_scene(scene scene)
{
    display_camera(scene.camera);
    display_ambient_light(scene.ambient_light);
    display_light(scene.lights);
    display_spheres(scene.spheres);
    display_cylinders(scene.cylinders);
    display_planes(scene.planes);
}
