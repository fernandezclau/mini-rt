/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <claferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:07:45 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:07:46 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Parses a single line of input and updates the scene accordingly.
 *
 * @param line Pointer to the line of text to parse.
 * @param scene Pointer to the scene structure to update.
 * @return 1 if successful, 0 if an error occurred during parsing.
 */
int	parse_line(char *line, t_scene *scene)
{
	char	**tokens;

	tokens = split_spaces(line);
	if (!tokens[0])
		return (free_array(tokens), 1);
	if (tokens[0][0] == CAMERA && !process_camera(tokens, &scene->camera))
		return (free_array(tokens), ft_error(E_CAMERA), 0);
	else if (tokens[0][0] == AMBIENT_LIGHT && \
			!process_ambient(tokens, &scene->ambient_light))
		return (free_array(tokens), ft_error(E_AMBIENT_LIGHT), 0);
	else if (tokens[0][0] == LIGHT && !process_light(tokens, &scene->lights))
		return (free_array(tokens), ft_error(E_LIGHT), 0);
	else if (!ft_strncmp(tokens[0], SPHERE, ft_strlen(tokens[0])) && \
			!process_sphere(tokens, &scene->spheres))
		return (free_array(tokens), ft_error(E_SPHERE), 0);
	else if (!ft_strncmp(tokens[0], PLANE, ft_strlen(tokens[0])) && \
			!process_plane(tokens, &scene->planes))
		return (free_array(tokens), ft_error(E_PLANE), 0);
	else if (!ft_strncmp(tokens[0], CYLINDER, ft_strlen(tokens[0])) && \
			!process_cylinder(tokens, &scene->cylinders))
		return (free_array(tokens), ft_error(E_CYLINDER), 0);
	else if (!ft_strncmp(tokens[0], CONE, ft_strlen(tokens[0])) && \
			!process_cone(tokens, &scene->cones))
		return (free_array(tokens), ft_error(E_CONE), 0);
	return (free_array(tokens), 1);
}

/**
 * @brief Parses a .rt file and updates the scene structure with its content.
 *
 * @param filename Pointer to the name of the file to parse.
 * @param scene Pointer to the scene structure to update.
 * @return 1 if successful, 0 if an error occurred during parsing.
 */
int	parse_file(const char *filename, t_scene *scene)
{
	int		fd;
	char	*line;

	if (!is_rt_file(filename))
		return (ft_error(E_EXTENSION), 0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("\033[1;31mError\033[1;37m"), 0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!parse_line(line, scene))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

/**
 * @brief Initializes the scene and parses the specified file to populate it.
 *
 * @param argc The number of command-line arguments.
 * @param filename Pointer to the name of the file to parse.
 * @param scene Pointer to the scene structure to update.
 * @return 1 if successful, 0 if an error occurred or the usage is incorrect.
 */
int	get_scene(int argc, char *filename, t_scene *scene)
{
	if (argc == 2)
	{
		init_scene(scene);
		if (parse_file(filename, scene))
		{
			print_scene(*scene);
			printf("%s%s%s", GR, LOADED_SCENE, RE);
			return (1);
		}
		exit(-1);
	}
	else
		ft_error(E_USAGE);
	return (0);
}
