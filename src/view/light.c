#include "../../include/minirt.h"

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
 * @brief Initializes an ambient light structure to default values.
 *
 * @param al A pointer to the ambient light structure to be initialized.
 */
void init_ambient_light(ambient_light *al)
{
    init_r_color(&al->color);
    al->ratio = 0;
}

/**
 * @brief Calculates the effect of ambient light on a given color.
 *
 * @param color Pointer to the color structure that will be modified to 
 *              incorporate the ambient light effect.
 * @param light The ambient light structure containing the color and ratio 
 *              of the ambient light.
*/
void    calculate_ambient_light(color *color, ambient_light light)
{
    color->r *= light.color.r * light.ratio;
    color->g *= light.color.g * light.ratio;
    color->b *= light.color.b * light.ratio;
}

// void	calculate_diffuse_light(color *color, color base_color, light *light, double exposure)
// {
// 	color->r += base_color.r * (light->color.r * light->brightness * exposure);
// 	color->g += base_color.g * (light->color.g * light->brightness * exposure);
// 	color->b += base_color.b * (light->color.b * light->brightness * exposure);
// }

// void    calculate_light(scene *scene, light *light, vector3 *hit, vector3 *normal, color color)
// {
//     color col;

//     calculate_ambient_light(&col);
//     vector3 light_dir = substract_v3(light->position, *hit);
// 	float   light_dist = length_v3(light_dir);
// 	light_dir = scale_v3(light_dir,  1 / light_dist);
// 	float  expo = fmax(dot_product_v3(*normal, light_dir), 0.0);
//     if (is_in_shadow(hit, light_dir, light_dist, scene) || !expo)
//         continue;
// 	col = apply_diffuse(color, light, expo);
// 	protect_colors(&col);
//     return col;
// }
// void calculate_light(scene *scene, float dist, color *color) {
//     // Calculamos el punto donde el rayo de la cámara intersecta con la escena.
//     vector3 point = sum_v3(scene->camera.position, scale_v3(scene->camera.direction, dist));
    
//     // Preparamos un rayo desde el punto hacia la luz.
//     ray r;
//     r.origin = point;
//     r.direction = normalize_v3(substract_v3(scene->light.position, point));

//     float light_dist = length_v3(substract_v3(scene->light.position, point)); // Distancia a la luz.
//     int intersect = 0; // Bandera para saber si hay intersección con un objeto antes de la luz.

//     // Recorremos todas las esferas.
//     sphere *iter_spheres = scene->spheres;
//     while (iter_spheres != NULL) {
//         float temp_dist;
//         if (intersect_ray_sphere(&r, &iter_spheres->center, iter_spheres->diameter / 2, &temp_dist)) {
//             if (temp_dist < light_dist) { // Solo consideramos intersecciones antes de la luz.
//                 intersect = 1;
//                 break;
//             }
//         }
//         iter_spheres = iter_spheres->next;
//     }

//     // Recorremos todos los planos.
//     plane *iter_planes = scene->planes;
//     while (iter_planes != NULL) {
//         float temp_dist;
//         if (intersect_ray_plane(&r, &iter_planes->point, &iter_planes->normal, &temp_dist)) {
//             if (temp_dist < light_dist) { // Solo consideramos intersecciones antes de la luz.
//                 intersect = 1;
//                 break;
//             }
//         }
//         iter_planes = iter_planes->next;
//     }

//     // Recorremos todos los cilindros.
//     cylinder *iter_cylinder = scene->cylinders;
//     while (iter_cylinder != NULL) {
//         float temp_dist;
//         if (intersect_ray_cylinder(&r, &iter_cylinder->center, iter_cylinder->diameter / 2, 
//                                    iter_cylinder->height, &temp_dist)) {
//             if (temp_dist < light_dist) { // Solo consideramos intersecciones antes de la luz.
//                 intersect = 1;
//                 break;
//             }
//         }
//         iter_cylinder = iter_cylinder->next;
//     }

//     // Composición del color basado en la intersección.
//     float base_ratio = 1.0f - scene->ambient.ratio;
//     if (!intersect) {
//         // No hay sombra: aplicamos la luz directa junto con la ambiental.
//         color->r = color->r * base_ratio + scene->ambient.color.r * scene->ambient.ratio + scene->light.color.r;
//         color->g = color->g * base_ratio + scene->ambient.color.g * scene->ambient.ratio + scene->light.color.g;
//         color->b = color->b * base_ratio + scene->ambient.color.b * scene->ambient.ratio + scene->light.color.b;
//     } else {
//         // Hay sombra: solo aplicamos la luz ambiental.
//         color->r = color->r * base_ratio + scene->ambient.color.r * scene->ambient.ratio;
//         color->g = color->g * base_ratio + scene->ambient.color.g * scene->ambient.ratio;
//         color->b = color->b * base_ratio + scene->ambient.color.b * scene->ambient.ratio;
//     }
// }


// void    calculate_light(scene *scene, float dist, color *color, void *void_ptr)
// {
//     vector3 point = sum_v3(scene->camera.position, scale_v3(scene->camera.direction, dist));
//     ray r;

//     r.origin = point;
//     r.direction = normalize_v3(substract_v3(scene->light.position, point));

//     float   light_dist;
//     int     intersect = 0;

//     sphere *iter_spheres = scene->spheres;
//     plane  *iter_planes= scene->planes;
//     cylinder *iter_cylinder = scene->cylinders;
//     while (iter_spheres != NULL && !intersect)
//     {
//         if ((void *)iter_spheres != void_ptr)
//         {
//             intersect = intersect_ray_sphere(&r, &iter_spheres->center, iter_spheres->diameter /2, &light_dist);
//             iter_spheres = iter_spheres->next;
//         }
//     }
//     while (iter_planes != NULL && !intersect)
//     {
//         intersect = intersect_ray_plane(&r, &iter_planes->point, &iter_planes->normal, &light_dist);
//         iter_planes = iter_planes->next;
//     }
//     while (iter_cylinder != NULL && !intersect)
//     {
//         intersect = intersect_ray_cylinder(&r, &iter_cylinder->center, iter_cylinder->diameter /2, iter_cylinder->height, &light_dist);
//         iter_cylinder = iter_cylinder->next;
//     }
//     if (!intersect)
//     {
//         float   base_ratio = 1 - scene->ambient.ratio;
//         color->r = color->r * base_ratio + scene->ambient.color.r * scene->ambient.ratio;
//         color->g = color->g * base_ratio + scene->ambient.color.g * scene->ambient.ratio;
//         color->b = color->b * base_ratio + scene->ambient.color.b * scene->ambient.ratio;
//     }
//     else
//     {
//          float   base_ratio = 1 - scene->ambient.ratio;
//         color->r = (color->r * base_ratio + scene->ambient.color.r * scene->ambient.ratio) * 0.5f;
//         color->g = (color->g * base_ratio + scene->ambient.color.g * scene->ambient.ratio) * 0.5f;
//         color->b = (color->b * base_ratio + scene->ambient.color.b * scene->ambient.ratio) * 0.5f;
//     }
//     // float   base_ratio = 1 - scene->ambient.ratio - 0.3f;
//     // color->r = color->r * base_ratio + scene->ambient.color.r * scene->ambient.ratio + scene->light.color.r * 0.3f * !intersect;
//     // color->g = color->g * base_ratio + scene->ambient.color.g * scene->ambient.ratio + scene->light.color.g * 0.3f * !intersect;
//     // color->b = color->b * base_ratio + scene->ambient.color.b * scene->ambient.ratio + scene->light.color.b * 0.3f * !intersect;
// }

/**
 * @brief Displays the details of an ambient light structure.
 *
 * @param al The ambient light structure to be displayed.
 */
void display_ambient_light(ambient_light al)
{
    printf(" %s____ AMBIENT LIGHT ____ %s\n", WH, RE);
    printf("\n");
    printf("%s > Ratio %s", WH, RE);
    printf("%s[%f]%s\n", CY, al.ratio, RE);
    printf("\n");
    printf("%s > Color %s", WH, RE);
    display_color(al.color);
    printf("\n");
}

/**
 * @brief Displays the details of a light structure.
 *
 * @param l The light structure to be displayed.
 */
void display_light(light l)
{
    printf(" %s____ LIGHT ____ %s\n", WH, RE);
    printf("\n");
    printf("%s > Position %s", WH, RE);
    display_v3(l.position);
    printf("\n");
    printf("%s > Brightness %s", WH, RE);
    printf("%s[%f]%s\n", CY, l.brightness, RE);
    printf("\n");
    printf("%s > Color %s", WH, RE);
    display_color(l.color);
    printf("\n");
}

