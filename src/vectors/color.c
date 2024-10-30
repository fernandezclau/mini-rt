#include "../../include/minirt.h"

/**
 * @brief Initializes a color structure to zero.
 *
 * @param c A pointer to the color structure to be initialized.
 * @return An integer value indicating success (1) or failure (0).
 */
int init_r_color(color *c)
{
    c->r = 0;
    c->g = 0;
    c->b = 0;
}

/**
 * @brief   Converts a RGB color to a hex value.
 *
 * @param c Color struct with the RGB elements.
 * @return  Corresponding hex value.
 */
int rgb_to_hex(color *c)
{
    int r = c->r < 0 ? 0 : (c->r > 255 ? 255 : c->r);
    int g = c->g < 0 ? 0 : (c->g > 255 ? 255 : c->g);
    int b = c->b < 0 ? 0 : (c->b > 255 ? 255 : c->b);

    return (r << 16) | (g << 8) | b;
}

/**
 * @brief   Converts a vector3 to a color.
 *
 * @param v Vector3 struct.
 * @return  Corresponding color struct.
 */
color   vector3_to_color(vector3 v)
{
    color   c;

    c.r = v.x;
    c.g = v.y;
    c.b = v.z;

    return (c);
}

/**
 * @brief Scales a color by a scalar value.
 *
 * @param c The color to scale.
 * @param scalar The scaling factor.
 * @return A new color scaled by the given scalar.
 */
color   multiply_color(color c, vector3 v)
{
    color new;

    new.r = c.r * v.x;
    new.g = c.g * v.y;
    new.b = c.b * v.z;

    return new;
}

color add_color(color a, color b)
{
    color result;
    result.r = fminf(fmaxf(a.r + b.r, 0), 255); // Asegúrate de que esté en el rango 0-255
    result.g = fminf(fmaxf(a.g + b.g, 0), 255);
    result.b = fminf(fmaxf(a.b + b.b, 0), 255);
    return result;
}

color scale_c(color c, float factor)
{
    color result;
    result.r = fminf(fmaxf(c.r * factor, 0), 255); // Asegúrate de que esté en el rango 0-255
    result.g = fminf(fmaxf(c.g * factor, 0), 255);
    result.b = fminf(fmaxf(c.b * factor, 0), 255);
    return result;
}


/**
 * @brief Displays the RGB components of a color.
 *
 * @param c The color structure containing the RGB components to be displayed.
 */
void display_color(color c)
{
    printf("r:%s [%d] %s \t\t", RED, c.r, RE);
    printf("g:%s [%d] %s \t\t", GR, c.g, RE);
    printf("b:%s [%d] %s \t\t", CY, c.b, RE);
    printf("\n");
}