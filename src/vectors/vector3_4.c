/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:07:06 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:07:07 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Multiplies two 3D vectors component-wise.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return A new vector3 representing the component-wise product of `a` and `b`.
 */
vector3	multiple_v3(vector3 a, vector3 b)
{
	return (init_p_v3(a.x * b.x, a.y * b.y, a.z * b.z));
}

/**
 * @brief Scales a 3D vector by a scalar value.
 *
 * @param v The vector to scale.
 * @param scalar The scaling factor.
 * @return A new vector3 scaled by the given scalar.
 */
vector3	scale_v3(vector3 v, float scalar)
{
	return (init_p_v3(v.x * scalar, v.y * scalar, v.z * scalar));
}
