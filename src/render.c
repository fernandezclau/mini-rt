#include "minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->image_data + (y * data->size_line + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}