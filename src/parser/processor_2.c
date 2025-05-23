/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <claferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:07:56 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:07:57 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Processes sphere parameters from tokens and adds 
 * a new sphere to the list.
 *
 * @param tokens An array of strings containing the sphere parameters.
 * @param sp A double pointer to the head of the sphere linked list.
 * @return int Returns 1 on success, 0 on failure.
 */
int	process_sphere(char **tokens, t_sphere **sp)
{
	t_sphere	*new_sphere;
	char		**position;
	char		**colors;

	new_sphere = NULL;
	if (array_len(tokens) != 4)
		return (0);
	new_sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!new_sphere)
		return (0);
	position = ft_split(tokens[1], ',');
	if (!insert_vector3(&new_sphere->center, position, NOT_NORMALIZED))
		return (free(new_sphere), (0));
	if (!insert_magnitude(&new_sphere->diameter, tokens[2]))
		return (free(new_sphere), (0));
	new_sphere->radius = new_sphere->diameter / 2.0f;
	colors = ft_split(tokens[3], ',');
	if (!insert_color(&new_sphere->color, colors))
		return (free(new_sphere), (0));
	new_sphere->next = NULL;
	add_sphere(sp, new_sphere);
	return (1);
}

/**
 * @brief Processes plane parameters from tokens and adds a new plane 
 * to the list.
 *
 * @param tokens An array of strings containing the plane parameters.
 * @param pl A double pointer to the head of the plane linked list.
 * @return int Returns 1 on success, 0 on failure.
 */
int	process_plane(char **tokens, t_plane **pl)
{
	t_plane	*new_plane;
	char	**point;
	char	**normal;
	char	**colors;

	new_plane = NULL;
	if (array_len(tokens) != 4)
		return (0);
	new_plane = (t_plane *)malloc(sizeof(t_plane));
	if (!new_plane)
		return (0);
	point = ft_split(tokens[1], ',');
	if (!insert_vector3(&new_plane->point, point, NOT_NORMALIZED))
		return (free(new_plane), 0);
	normal = ft_split(tokens[2], ',');
	if (!insert_vector3(&new_plane->normal, normal, NORMALIZED))
		return (free(new_plane), 0);
	colors = ft_split(tokens[3], ',');
	if (!insert_color(&new_plane->color, colors))
		return (free(new_plane), 0);
	new_plane->next = NULL;
	add_plane(pl, new_plane);
	return (1);
}

/**
 * @brief Processes cylinder parameters from tokens and adds a new cylinder
 * to the list.
 *
 * @param tokens An array of strings containing the cylinder parameters.
 * @param cy A double pointer to the head of the cylinder linked list.
 * @return int Returns 1 on success, 0 on failure.
 */
int	process_cylinder(char **tokens, t_cylinder **cy)
{
	t_cylinder	*new_cylinder;
	char		**center;
	char		**direction;
	char		**colors;

	new_cylinder = NULL;
	new_cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (array_len(tokens) != 6 || !new_cylinder)
		return (0);
	center = ft_split(tokens[1], ',');
	if (!insert_vector3(&new_cylinder->center, center, NOT_NORMALIZED))
		return (free(new_cylinder), 0);
	direction = ft_split(tokens[2], ',');
	if (!insert_vector3(&new_cylinder->direction, direction, NORMALIZED))
		return (free(new_cylinder), 0);
	if (!insert_magnitude(&new_cylinder->diameter, tokens[3]))
		return (free(new_cylinder), 0);
	if (!insert_magnitude(&new_cylinder->height, tokens[4]))
		return (free(new_cylinder), 0);
	colors = ft_split(tokens[5], ',');
	if (!insert_color(&new_cylinder->color, colors))
		return (free(new_cylinder), 0);
	new_cylinder->next = NULL;
	add_cylinder(cy, new_cylinder);
	return (1);
}

/**
 * @brief Processes cone parameters from tokens and adds a new cone
 * to the list.
 *
 * @param tokens An array of strings containing the cone parameters.
 * @param cn A double pointer to the head of the cone linked list.
 * @return int Returns 1 on success, 0 on failure.
 */
int	process_cone(char **tokens, t_cone **cn)
{
	t_cone		*new_cone;
	char		**center;
	char		**direction;
	char		**colors;

	new_cone = NULL;
	new_cone = (t_cone *)malloc(sizeof(t_cone));
	if (array_len(tokens) != 6 || !new_cone)
		return (0);
	center = ft_split(tokens[1], ',');
	if (!insert_vector3(&new_cone->center, center, NOT_NORMALIZED))
		return (free(new_cone), 0);
	direction = ft_split(tokens[2], ',');
	if (!insert_vector3(&new_cone->direction, direction, NORMALIZED))
		return (free(new_cone), 0);
	if (!insert_magnitude(&new_cone->diameter, tokens[3]))
		return (free(new_cone), 0);
	if (!insert_magnitude(&new_cone->height, tokens[4]))
		return (free(new_cone), 0);
	colors = ft_split(tokens[5], ',');
	if (!insert_color(&new_cone->color, colors))
		return (free(new_cone), 0);
	new_cone->next = NULL;
	add_cone(cn, new_cone);
	return (1);
}
