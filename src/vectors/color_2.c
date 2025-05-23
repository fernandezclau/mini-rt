/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <claferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:06:44 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:06:46 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Scales the RGB values of a color by a given factor.
 * 
 * @param c The original color structure with RGB values to be scaled.
 * @param factor The scaling factor to adjust the color intensity.
 * 
 * @return The scaled color structure with modified RGB values.
 */
t_color	scale_c(t_color c, float factor)
{
	t_color	result;

	result.r = fminf(fmaxf(c.r * factor, 0), 255);
	result.g = fminf(fmaxf(c.g * factor, 0), 255);
	result.b = fminf(fmaxf(c.b * factor, 0), 255);
	return (result);
}

/**
 * @brief Displays the RGB components of a color.
 *
 * @param c The color structure containing the RGB components to be displayed.
 */
void	display_color(t_color c)
{
	printf("r:%s [%d] %s \t\t", RED, c.r, RE);
	printf("g:%s [%d] %s \t\t", GR, c.g, RE);
	printf("b:%s [%d] %s \t\t", CY, c.b, RE);
	printf("\n");
}
