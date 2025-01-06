/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <claferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:06:49 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:06:50 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Creates and returns a 2D vector initialized to (0, 0).
 *
 * @return A vector2 structure with x and y components set to 0.
 */
t_vector2	init_v2(void)
{
	t_vector2	v;

	v.x = 0;
	v.y = 0;
	return (v);
}

/**
 * @brief Initializes a 2D vector with the given x and y components.
 *
 * @param x The x component of the vector.
 * @param y The y component of the vector.
 * @return A vector2 structure initialized with the given x and y values.
 */
t_vector2	init_p_v2(float x, float y)
{
	t_vector2	v;

	v.x = x;
	v.y = y;
	return (v);
}

/**
 * @brief Displays a 2D vector in console.
 * 
 * @param x The 2D vector to display.
 */
void	display_v2(t_vector2 v)
{
	printf("x: %f\t", v.x);
	printf("y: %f\t", v.y);
	printf("\n");
}
