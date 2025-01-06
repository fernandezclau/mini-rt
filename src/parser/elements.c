/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <claferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:07:41 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:07:42 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Inserts values into a vector3 structure from a string array.
 *
 * @param v Pointer to the vector3 structure to be filled.
 * @param tokens Array of string tokens containing the float values.
 * @param is_normalized Check if the vector is normalized.
 * @return 1 if successful, 0 if an error occurred (e.g., invalid tokens).
 */
int	insert_vector3(t_vector3 *v, char **tokens, int is_normalized)
{
	if (!three_floats(tokens))
		return (free_array(tokens), 0);
	v->x = ft_atof(tokens[0]);
	v->y = ft_atof(tokens[1]);
	v->z = ft_atof(tokens[2]);
	free_array(tokens);
	if (is_normalized && !is_normalized_f_v3(*v))
		return (0);
	return (1);
}

/**
 * @brief Inserts values into a color structure from a string array.
 *
 * @param c Pointer to the color structure to be filled.
 * @param tokens Array of string tokens containing the integer color values.
 * @return 1 if successful, 0 if an error occurred.
 */
int	insert_color(t_color *c, char **tokens)
{
	if (!three_ints(tokens))
		return (free_array(tokens), 0);
	c->r = ft_atoi(tokens[0]);
	c->g = ft_atoi(tokens[1]);
	c->b = ft_atoi(tokens[2]);
	free_array(tokens);
	if (!is_valid_color(*c))
		return (0);
	return (1);
}

/**
 * @brief Inserts a field of view angle into a float variable.
 *
 * @param fov Pointer to the float variable to be filled.
 * @param value String representing the field of view angle.
 * @return 1 if successful, 0 if an error occurred (e.g., invalid value).
 */
int	insert_angle(float *fov, char *value)
{
	if (!is_int(value))
		return (0);
	*fov = ft_atoi(value);
	if (!is_valid_angle(*fov))
		return (0);
	return (1);
}

/**
 * @brief Inserts a ratio value into a float variable.
 *
 * @param ratio Pointer to the float variable to be filled.
 * @param value String representing the ratio value.
 * @return 1 if successful, 0 if an error occurred (e.g., invalid value).
 */
int	insert_ratio(float *ratio, char *value)
{
	if (!is_float(value))
		return (0);
	*ratio = ft_atof(value);
	if (!is_valid_ratio(*ratio))
		return (0);
	return (1);
}

/**
 * @brief Inserts a magnitude value into a float variable.
 *s
 * @param magnitude Pointer to the float variable to be filled.
 * @param value String representing the magnitude value.
 * @return 1 if successful, 0 if an error occurred (e.g., invalid value).
 */
int	insert_magnitude(float *magnitude, char *value)
{
	if (!is_float(value))
		return (0);
	*magnitude = ft_atof(value);
	return (1);
}
