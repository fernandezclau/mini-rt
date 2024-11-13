/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spotlight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:09:47 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:33:34 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Calculates the diffuse intensity of light at a point.
 * 
 * @param normal Vector representing the surface normal at the point.
 * @param p_to_l Vector pointing from the point to the light source.
 * @param light Vector representing the light intensity.
 * @return t_vector3 The diffuse intensity vector at the point.
 */
t_vector3	diffuse_intensity(t_vector3 normal, t_vector3 p_to_l, \
		t_vector3 light)
{
	t_vector3	diffuse;
	float		ratio;

	ratio = fmax(dot_product_v3(p_to_l, normal), 0);
	diffuse = scale_v3(light, ratio);
	return (diffuse);
}

/**
 * @brief Calculates the specular intensity of light at a point.
 * 
 * @param normal Vector representing the surface normal at the point.
 * @param p_to_l Vector pointing from the point to the light source.
 * @param light Vector representing the light intensity.
 * @return t_vector3 The specular intensity vector at the point.
 */
t_vector3	specular_intensity(t_vector3 normal, t_vector3 p_to_l, \
		t_vector3 light)
{
	float		ratio;
	t_vector3	specular;

	ratio = fmax(dot_product_v3(p_to_l, normal), 0);
	specular = scale_v3(light, pow(ratio, 70) * 3);
	return (specular);
}
