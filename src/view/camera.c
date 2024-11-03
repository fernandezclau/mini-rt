#include "../../include/minirt.h"

/**
 * @brief Updates the camera's orthonormal basis based on its direction vector.
 * 
 * @param cam Pointer to the camera structure with direction and identity 
 * basis vectors.
 */
void	compute_camera_basis(camera *cam)
{
	vector3	axis;
	float	cos_theta;
	float	sin_theta;

	cam->identity[0] = (vector3){1, 0, 0};
	cam->identity[1] = (vector3){0, 1, 0};
	cam->identity[2] = (vector3){0, 0, 1};
	axis = normalize_v3(cross_product_v3(cam->identity[2], cam->direction));
	cos_theta = cos_v3(cam->identity[2], cam->direction);
	sin_theta = sin_v3(cam->identity[2], cam->direction);
	cam->identity[0] = rotate_vect(cam->identity[0], axis, \
			cos_theta, sin_theta);
	cam->identity[1] = rotate_vect(cam->identity[1], axis, \
			cos_theta, sin_theta);
	cam->identity[2] = rotate_vect(cam->identity[2], axis, \
			cos_theta, sin_theta);
}

/**
 * @brief Initializes a camera structure to default values.
 *
 * @param c A pointer to the camera structure to be initialized.
 */
void	init_camera(camera *c)
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
void	display_camera(camera c)
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
