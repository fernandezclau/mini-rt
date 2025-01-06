/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spotlight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <claferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:09:47 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:33:34 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vector3	calculate_spotlight(t_light light, t_vector3 normal, \
		t_vector3 position)
{
	t_vector3	light_intensity;
	t_vector3	diffuse;
	t_vector3	specular;

	light_intensity = calculate_intensity(light.color, light.brightness);
	specular = calculate_specular(normal, position, light_intensity);
	diffuse = calculate_diffuse(normal, position, light_intensity);
	return (sum_v3(specular, diffuse));
}

/**
 * @brief Calculates the effect of ambient light on a given color.
 *
 * @param color Pointer to the color structure that will be modified to 
 *              incorporate the ambient light effect.
 * @param ration The ration of the light.
*/
t_vector3	calculate_intensity(t_color colour, float ratio)
{
	t_vector3	intensity;

	intensity.x = ratio * colour.r / 255;
	intensity.y = ratio * colour.r / 255;
	intensity.z = ratio * colour.r / 255;
	return (intensity);
}

/**
 * @brief Calculates the diffuse intensity of light at a point.
 * 
 * @param normal Vector representing the surface normal at the point.
 * @param p_to_l Vector pointing from the point to the light source.
 * @param light Vector representing the light intensity.
 * @return t_vector3 The diffuse intensity vector at the point.
 */
t_vector3	calculate_diffuse(t_vector3 normal, t_vector3 p_to_l, \
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
t_vector3	calculate_specular(t_vector3 normal, t_vector3 p_to_l, \
		t_vector3 light)
{
	float		ratio;
	t_vector3	specular;

	ratio = fmax(dot_product_v3(p_to_l, normal), 0);
	specular = scale_v3(light, pow(ratio, 70) * 3);
	return (specular);
}
