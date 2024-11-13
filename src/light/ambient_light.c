/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:09:42 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:09:43 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Calculates the effect of ambient light on a given color.
 *
 * @param color Pointer to the color structure that will be modified to 
 *              incorporate the ambient light effect.
 * @param light The ambient light structure containing the color and ratio 
 *              of the ambient light.
*/
t_vector3	calculate_ambient_light(t_ambient_light light)
{
	t_vector3	intensity;

	intensity.x = light.ratio * light.color.r / 255;
	intensity.y = light.ratio * light.color.g / 255;
	intensity.z = light.ratio * light.color.b / 255;
	return (intensity);
}

/**
 * @brief Initializes an ambient light structure to default values.
 *
 * @param al A pointer to the ambient light structure to be initialized.
 */
void	init_ambient_light(t_ambient_light *al)
{
	init_r_color(&al->color);
	al->ratio = 0;
}

/**
 * @brief Displays the details of an ambient light structure.
 *
 * @param al The ambient light structure to be displayed.
 */
void	display_ambient_light(t_ambient_light al)
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
