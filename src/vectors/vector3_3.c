/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:07:02 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:07:03 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Computes the dot product of two 3D vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return A float representing the dot product of the two vectors.
 */
float	dot_product_v3(vector3 a, vector3 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

/**
 * @brief Computes the cross product of two 3D vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return A new vector3 that is the cross product of `a` and `b`.
 */
vector3	cross_product_v3(vector3 a, vector3 b)
{
	return (init_p_v3(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x));
}

/**
 * @brief Computes the squared length (magnitude) of a 3D vector.
 *
 * @param v The vector whose squared length is to be calculated.
 * @return A float representing the squared length of the vector.
 */
float	pow_v3(vector3 v)
{
	return (pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

/**
 * @brief Computes the length (magnitude) of a 3D vector.
 *
 * The length of a vector represents its magnitude or distance from the origin.
 *
 * @param v The vector whose length is to be calculated.
 * @return A float representing the length of the vector.
 */
float	length_v3(vector3 v)
{
	return (sqrtf(pow_v3(v)));
}

/**
 * @brief Normalizes a 3D vector to have a length of 1.
 *
 * @param v The vector to normalize.
 * @return A new vector3 that is the normalized version of the input vector.
 */
vector3	normalize_v3(vector3 v)
{
	float	len;

	len = length_v3(v);
	if (!len)
		return ((vector3){0, 0, 0});
	if (len > 0)
		return (scale_v3(v, 1.0f / len));
	return (v);
}
