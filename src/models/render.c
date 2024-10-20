#include "../../include/minirt.h"

/**
 * @brief Puts a pixel in the image at the specified position with the given color.
 *
 * @param data Pointer to the image data structure.
 * @param x X-coordinate of the pixel to draw.
 * @param y Y-coordinate of the pixel to draw.
 * @param color Color of the pixel in hexadecimal format.
 */
void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->image_data + (y * data->size_line + x * (data->bpp / 8));
    *(unsigned int *)dst = color;
}

/**
 * @brief Computes the direction of a ray based on pixel coordinates.
 *
 * @param x X-coordinate of the pixel.
 * @param y Y-coordinate of the pixel.
 * @param fov Camera's field of view in degrees.
 * @return vector3 Normalized ray direction.
 */
vector3 compute_direction(int x, int y, float fov)
{
    float aspect_ratio = (float)W_WIDTH / (float)W_HEIGHT;

    float fov_rad = 1.0f / tanf(fov * 0.5f * (M_PI / 180.0f));

    float x_nds = (2.0f * (float)x / (float)W_WIDTH - 1.0f) * aspect_ratio;
    float y_nds = 1.0f - 2.0f * (float)y / (float)W_HEIGHT;

    vector3 direction = {
        x_nds * fov_rad,
        y_nds * fov_rad,
        -1.0f
    };

    float length = sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
    direction.x /= length;
    direction.y /= length;
    direction.z /= length;

    return direction;
}

/**
 * @brief Renders the scene into the image using ray tracing.
 *
 * @param data Pointer to the image data structure.
 * @param scene Pointer to the scene structure containing the objects to render.
 */
void render(t_data *data, scene *scene)
{
    ray r;
    hit hit;
    for (int x = 0; x < W_WIDTH; x++) {
        for (int y = 0; y < W_HEIGHT; y++) {
            ray r;
            r.origin = scene->camera.position;
            r.direction = compute_direction(x, y, scene->camera.fov);
            
            float   min_dist;
            float dist;
            color final_color = {0, 0, 0};
            int     intersect = 0;
            
            init_hit_point(&hit);
            sphere *iter_spheres = scene->spheres;
            plane  *iter_planes= scene->planes;
            cylinder *iter_cylinder = scene->cylinders;
            
            // Spheres intersection
            intersection_spheres(&r, &scene->spheres, &hit);
            // while (iter_spheres != NULL)
            // {   
            //     if (intersect_ray_sphere(&r, iter_spheres, &hit.dist))
            //     {
            //         if (hit.dist < hit.min_dist || hit.intersect == 0)
            //         {
            //             hit.min_dist = abs(hit.dist);
            //             hit.final_color = iter_spheres->color;
            //         }
            //         hit.intersect = 1;
            //     }
            //     iter_spheres = iter_spheres->next;
            // }
            // Planes intersection
           interesection_planes(&r, &scene->planes, &hit);
            // while (iter_planes != NULL)
            // {   
            //     if (intersect_ray_plane(&r, iter_planes, &dist))
            //     {
            //         if (dist < min_dist || intersect == 0)
            //         {
            //             min_dist = abs(dist);
            //             final_color = iter_planes->color;
            //         }
            //         intersect = 1;
            //     }
            //     iter_planes = iter_planes->next;
            // }
            // Cylinders intersection
            intersection_cylinders(&r, &scene->cylinders, &hit);
            // cylinder *iter_cylinders = scene->cylinders;
            // while (iter_cylinders != NULL) {
            //     if (intersect_ray_cylinder(&r, iter_cylinders, &hit.dist)) {
            //         if (hit.dist < hit.min_dist || hit.intersect == 0) {
            //             hit.min_dist = dist;
            //             hit.final_color = iter_cylinders->color;
            //         }
            //         hit.intersect = 1;
            //     }
            //     iter_cylinders = iter_cylinders->next;
            // }
            if (hit.intersect)
            {
                //calculate_ambient_light(&final_color, scene->ambient);
                my_mlx_pixel_put(data, x, y, rgb_to_hex(&hit.final_color));
            }
        }
    }
}
