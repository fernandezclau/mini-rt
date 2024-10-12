#include "../../include/minirt.h"

/**
 * @brief Initializes a camera structure to default values.
 *
 * @param c A pointer to the camera structure to be initialized.
 */
void init_camera(camera *c)
{
    init_r_v3(&c->position);
    init_r_v3(&c->direction);
    c->fov = 0;
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
 * @brief Displays the details of a camera structure.
 *
 * @param c The camera structure to be displayed.
 */
void display_camera(camera c)
{
    printf(" %s____ CAMARA ____ %s\n", WH, RE);
    printf("\n");
    printf("%s > Position %s", WH, RE);
    display_v3(c.position);
    printf("\n");
    printf("%s > Direction %s", WH, RE);
    display_v3(c.direction);
    printf("\n");
    printf("%s > Fov %s", WH, RE);
    printf("%s[%f]%s\n", CY, c.fov, RE);
    printf("\n");
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
