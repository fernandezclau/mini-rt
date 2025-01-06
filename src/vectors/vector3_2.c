/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <claferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:06:58 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:07:00 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Calculates the cosine of the angle between two 3D vectors.
 * 
 * @param a The first vector.
 * @param b The second vector.
 * @return float The cosine of the angle between `a` and `b`.
 */
float	cos_v3(t_vector3 a, t_vector3 b)
{
	return (dot_product_v3(a, b) / (length_v3(a) * length_v3(b)));
}

/**
 * @brief Calculates the sine of the angle between two 3D vectors.
 * 
 * @param a The first vector.
 * @param b The second vector.
 * @return float The sine of the angle between `a` and `b`.
 */
float	sin_v3(t_vector3 a, t_vector3 b)
{
	return (length_v3(cross_product_v3(a, b)) * (length_v3(a) * length_v3(b)));
}

/**
 * @brief Computes the reflection vector of a light direction relative
 * to a normal.
 * 
 * @param light_direction Vector representing the incident light direction.
 * @param normal Normal vector at the point of reflection.
 * @return vector3 Reflected vector based on the given light direction and
 * normal.
 */
t_vector3	reflect_v3(t_vector3 light_direction, t_vector3 normal)
{
	float		dot_ln;
	t_vector3	reflected;

	dot_ln = dot_product_v3(light_direction, normal);
	reflected.x = light_direction.x - 2.0f * dot_ln * normal.x;
	reflected.y = light_direction.y - 2.0f * dot_ln * normal.y;
	reflected.z = light_direction.z - 2.0f * dot_ln * normal.z;
	return (reflected);
}

/**
 * @brief Prints the components of a 3D vector on the console.
 * 
 * @param v The 3D vector to print.
 */
void	display_v3(t_vector3 v)
{
	printf("x:%s [%f] %s \t", PIN, v.x, RE);
	printf("y:%s [%f] %s \t", CY, v.y, RE);
	printf("z:%s [%f] %s \t", YE, v.z, RE);
	printf("\n");
}
