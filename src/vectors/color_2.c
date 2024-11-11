/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:06:44 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:06:46 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

color	scale_c(color c, float factor)
{
	color	result;

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
void	display_color(color c)
{
	printf("r:%s [%d] %s \t\t", RED, c.r, RE);
	printf("g:%s [%d] %s \t\t", GR, c.g, RE);
	printf("b:%s [%d] %s \t\t", CY, c.b, RE);
	printf("\n");
}
