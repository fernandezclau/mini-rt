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
    // Calcular el �ngulo del campo de visi�n
    float tanFOV = tan(scene->camera.fov * M_PI / 360.0f);
    float aspectRatio = (float)(W_WIDTH) / (float)(W_HEIGHT);
    
    // Precalcular vectores
    vector3 up = init_p_v3(0.0f, 1.0f, 0.0f);
    vector3 right = normalize_v3(cross_product_v3(scene->camera.direction, up));
    vector3 trueUp = normalize_v3(cross_product_v3(right, scene->camera.direction));

    // Comprobar pixel a pixel
    for (unsigned x = 0; x < W_WIDTH; ++x) {

        float normalizedX = (x + 0.5f) / W_WIDTH;
        float screenX = (1.0f - 2.0f * normalizedX) * aspectRatio * tanFOV;

        for (unsigned y = 0; y < W_HEIGHT; ++y) {

            float normalizedY = (y + 0.5f) / W_HEIGHT;
            float screenY = (1.0f - 2.0f * normalizedY) * tanFOV;

            // Calcular la direcci�n del rayo en el espacio de la c�mara
            vector3 rayDirection;

            // Multiplicar screenX por el vector right
            vector3 rightScaled = scale_v3(right, screenX);

            // Multiplicar screenY por el vector trueUp
            vector3 trueUpScaled = scale_v3(trueUp, screenY);

            // Sumar los vectores: rightScaled + trueUpScaled + camera.direction
            vector3 temp = sum_v3(rightScaled, trueUpScaled);
            rayDirection = sum_v3(temp, scene->camera.direction);

            // Normalizar el vector resultante
            rayDirection = normalize_v3(rayDirection);

            // Crear el rayo
            ray r;
            r.direction = rayDirection;// compute_ray_direction(x, y, scene->camera.fov, &scene->camera);//rayDirection;
            r.origin = scene->camera.position;

            ray_intersection(r, scene);
            // Si hubo una intersecci�n con alguna figura
            if (scene->hit.intersect)
            {
                scene->hit.final_color = calculate_light(r, scene);
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

