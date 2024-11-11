/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:05:47 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:06:32 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Initializes a color structure to zero.
 *
 * @param c A pointer to the color structure to be initialized.
 * @return An integer value indicating success (1) or failure (0).
 */
int	init_r_color(t_color *c)
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
int	rgb_to_hex(t_color *c)
{
	int	r;
	int	g;
	int	b;

	if (c->r < 0)
		r = 0;
	else if (c->r > 255)
		r = 255;
	else
		r = c->r;
	if (c->g < 0)
		g = 0;
	else if (c->g > 255)
		g = 255;
	else
		g = c->g;
	if (c->b < 0)
		b = 0;
	else if (c->b > 255)
		b = 255;
	else
		b = c->b;
	return ((r << 16) | (g << 8) | b);
}

/**
 * @brief   Converts a vector3 to a color.
 *
 * @param v Vector3 struct.
 * @return  Corresponding color struct.
 */
t_color	vector3_to_color(t_vector3 v)
{
	t_color	c;

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
t_color	multiply_color(t_color c, t_vector3 v)
{
	t_color	new;

	new.r = c.r * v.x;
	new.g = c.g * v.y;
	new.b = c.b * v.z;
	return (new);
}

/**
 * @brief Adds two colors component-wise and clamps the result 
 * within the 0-255 range.
 * 
 * @param a The first color to be added.
 * @param b The second color to be added.
 * @return color Resulting color from the addition.
 */
t_color	add_color(t_color a, t_color b)
{
	t_color	result;

	result.r = fminf(fmaxf(a.r + b.r, 0), 255);
	result.g = fminf(fmaxf(a.g + b.g, 0), 255);
	result.b = fminf(fmaxf(a.b + b.b, 0), 255);
	return (result);
}
