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
 * @brief Scales a color by a scalar value.
 *
 * @param c The color to scale.
 * @param scalar The scaling factor.
 * @return A new color scaled by the given scalar.
 */
color   scale_color(color c, float scale)
{
    color new;

    new.r = c.r * scale;
    new.g = c.g * scale;
    new.b = c.b * scale;

    return new;
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