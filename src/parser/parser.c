#include "../../include/minirt.h"

/**
 * @brief Parses a single line of input and updates the scene accordingly.
 *
 * @param line Pointer to the line of text to parse.
 * @param scene Pointer to the scene structure to update.
 * @return 1 if successful, 0 if an error occurred during parsing.
 */
int	parse_line(char *line, scene *scene)
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
	else if (!strcmp(tokens[0], SPHERE) && \
			!process_sphere(tokens, &scene->spheres))
		return (free_array(tokens), ft_error(E_SPHERE), 0);
	else if (!strcmp(tokens[0], PLANE) && \
			!process_plane(tokens, &scene->planes))
		return (free_array(tokens), ft_error(E_PLANE), 0);
	else if (!strcmp(tokens[0], CYLINDER) && \
			!process_cylinder(tokens, &scene->cylinders))
		return (free_array(tokens), ft_error(E_CYLINDER), 0);
	return (free_array(tokens), 1);
}

/**
 * @brief Parses a .rt file and updates the scene structure with its content.
 *
 * @param filename Pointer to the name of the file to parse.
 * @param scene Pointer to the scene structure to update.
 * @return 1 if successful, 0 if an error occurred during parsing.
 */
int	parse_file(const char *filename, scene *scene)
{
	FILE	*file;
	char	*line;
	size_t	len;

	line = NULL;
	len = 0;
	if (!is_rt_file(filename))
		return (ft_error(E_EXTENSION), 0);
	file = fopen(filename, "r");
	if (!file)
		return (perror("\033[1;31mError\033[1;37m"), 0);
	while (getline(&line, &len, file) != -1)
		if (!parse_line(line, scene))
			return (free(line), fclose(file), 0);
	free(line);
	fclose(file);
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
int	get_scene(int argc, char *filename, scene *scene)
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
	}
	else
		ft_error(E_USAGE);
	return (0);
}
