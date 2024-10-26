#include "../../include/minirt.h"

/**
 * @brief Calculates the effect of ambient light on a given color.
 *
 * @param color Pointer to the color structure that will be modified to 
 *              incorporate the ambient light effect.
 * @param light The ambient light structure containing the color and ratio 
 *              of the ambient light.
*/
color calculate_ambient_light(ambient_light light)
{
    color intensity;
    int     sum_color;

    sum_color = light.color.r + light.color.g + light.color.b;
    intensity.r = INTENSITY_RATIO * 3 * light.ratio * light.color.r / sum_color;
    intensity.g = INTENSITY_RATIO * 3 * light.ratio * light.color.g / sum_color;
    intensity.b = INTENSITY_RATIO * 3 * light.ratio * light.color.b / sum_color;

    return (intensity);
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