/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:06:53 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:06:55 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Creates and returns a 3D vector initialized to (0, 0, 0).
 *
 * @return A vector3 structure with all components (x, y, z) set to 0.
 */
t_vector3	init_v3(void)
{
	t_vector3	v;

	v.x = 0;
	v.y = 0;
	v.z = 0;
	return (v);
}

/**
 * @brief Initializes a 3D vector with the given x, y, and z components.
 *
 * @param x The x component of the vector.
 * @param y The y component of the vector.
 * @param z The z component of the vector.
 * @return A vector3 structure initialized with the given x, y, and z values.
 */
t_vector3	init_p_v3(float x, float y, float z)
{
	t_vector3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

/**
 * @brief Initializes a vector3 structure to zero.
 *
 * @param v A pointer to the vector3 structure to be initialized.
 */
t_vector3	init_r_v3(t_vector3 *v)
{
	v->x = 0;
	v->y = 0;
	v->z = 0;
}

/**
 * @brief Sum two 3D vectors component-wise.
 *
 * @param a The first vector (minuend).
 * @param b The second vector (subtrahend).
 * @return A new vector3 representing the result of the sum.
 */
t_vector3	sum_v3(t_vector3 a, t_vector3 b)
{
	return (init_p_v3(a.x + b.x, a.y + b.y, a.z + b.z));
}

/**
 * @brief Subtracts two 3D vectors component-wise.
 *
 * @param a The first vector (minuend).
 * @param b The second vector (subtrahend).
 * @return A new vector3 representing the result of the subtraction.
 */
t_vector3	substract_v3(t_vector3 a, t_vector3 b)
{
	return (init_p_v3(a.x - b.x, a.y - b.y, a.z - b.z));
}
