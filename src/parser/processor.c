/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:07:53 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:07:54 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Processes camera parameters from tokens and updates 
 * the camera structure.
 *
 * @param tokens An array of strings containing the camera parameters.
 * @param camera A pointer to the camera structure to be updated.
 * @return int Returns 1 on success, 0 on failure (e.g., incorrect token count).
 */
int	process_camera(char **tokens, t_camera *camera)
{
	char	**position;
	char	**direction;

	if (array_len(tokens) != 4)
		return (0);
	position = ft_split(tokens[1], ',');
	if (!insert_vector3(&camera->position, position, NOT_NORMALIZED))
		return (0);
	direction = ft_split(tokens[2], ',');
	if (!insert_vector3(&camera->direction, direction, NORMALIZED))
		return (0);
	camera->direction = normalize_v3(camera->direction);
	if (!insert_angle(&camera->fov, tokens[3]))
		return (0);
	return (1);
}

/**
 * @brief Processes ambient light parameters from tokens and updates
 * the ambient light structure.
 *
 * @param tokens An array of strings containing the ambient light parameters.
 * @param ambient_light A pointer to the ambient light structure to be updated.
 * @return int Returns 1 on success, 0 on failure (e.g., incorrect token count).
 */
int	process_ambient(char **tokens, t_ambient_light *ambient_light)
{
	char	**colors;

	if (array_len(tokens) != 3)
		return (0);
	insert_ratio(&ambient_light->ratio, tokens[1]);
	colors = ft_split(tokens[2], ',');
	if (!insert_color(&ambient_light->color, colors))
		return (0);
	return (1);
}

/**
 * @brief Processes light parameters from tokens and updates the light structure.
 *
 * @param tokens An array of strings containing the light parameters.
 * @param light A pointer to the light structure to be updated.
 * @return int Returns 1 on success, 0 on failure (e.g., incorrect token count).
 */
int	process_light(char **tokens, t_light **l)
{
	t_light	*new_light;
	char	**position;
	char	**colors;

	new_light = NULL;
	if (array_len(tokens) != 4)
		return (0);
	new_light = (t_light *)malloc(sizeof(t_light));
	if (!new_light)
		return (0);
	position = ft_split(tokens[1], ',');
	if (!insert_vector3(&new_light->position, position, NOT_NORMALIZED))
		return (free(new_light), (0));
	if (!insert_ratio(&new_light->brightness, tokens[2]))
		return (free(new_light), (0));
	colors = ft_split(tokens[3], ',');
	if (!insert_color(&new_light->color, colors))
		return (free(new_light), (0));
	new_light->next = NULL;
	add_light(l, new_light);
	return (1);
}
