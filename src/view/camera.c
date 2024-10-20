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
