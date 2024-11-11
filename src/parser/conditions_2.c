/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:07:37 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:07:38 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Checks if a given ratio is within the valid range [0, 1].
 *
 * @param ratio The ratio to check.
 * @return 1 if the ratio is valid, 0 otherwise.
 */
int	is_valid_ratio(float ratio)
{
	return (ratio >= 0 && ratio <= 1);
}

/**
 * @brief Checks if a 3D vector is normalized.
 *
 * @param v The 3D vector to check.
 * @return 1 if the vector is normalized, 0 otherwise.
 */
int	is_normalized_f_v3(vector3 v)
{
	if (v.x < -1 || v.x > 1)
		return (0);
	else if (v.y < -1 || v.y > 1)
		return (0);
	else if (v.z < -1 || v.z > 1)
		return (0);
	return (1);
}

/**
 * @brief Checks if an angle is within the valid range [0, 180] degrees.
 *
 * @param angle The angle to check.
 * @return 1 if the angle is valid, 0 otherwise.
 */
int	is_valid_angle(int angle)
{
	return (angle >= 0 && angle <= 180);
}
