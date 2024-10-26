#include "../../include/minirt.h"

/**
 * @brief Renders the entire scene by casting rays from the camera through each pixel,
 * calculating intersections with scene objects, and coloring pixels based on the hit results.
 * 
 * @param data The rendering data structure for pixel output.
 * @param scene The scene data containing camera, objects, and light sources.
 */
void render(t_data *data, scene *scene)
{
    ray r;
    for (int y = 0; y < W_HEIGHT; y++)
    {
        for (int x = 0; x < W_WIDTH; x++)
        {
            r.origin = scene->camera.position;
            r.direction = compute_ray_direction(x, y, scene->camera.fov, &scene->camera);
            ray_intersection(r, scene);
            if (scene->hit.intersect)
            {
                pixel_put(data, x, y, rgb_to_hex(&scene->hit.final_color));
            }
        }
    }
}

/**
 * @brief Puts a pixel in the image at the specified position with the given color.
 *
 * @param data Pointer to the image data structure.
 * @param x X-coordinate of the pixel to draw.
 * @param y Y-coordinate of the pixel to draw.
 * @param color Color of the pixel in hexadecimal format.
 */
void pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->image_data + (y * data->size_line + x * (data->bpp / 8));
    *(unsigned int *)dst = color;
}

