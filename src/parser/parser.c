#include "../../include/minirt.h"

int parse_line(char *line, scene *scene)
{
    int error = 1;

    char **tokens = split_spaces(line);
    if (!tokens[0])
        return free_array(tokens), 1;

    if (tokens[0][0] == CAMERA && !process_camera(tokens, &scene->camera))
        ft_error(E_CAMERA), error = 0;
    else if (tokens[0][0] == AMBIENT_LIGHT && !process_ambient(tokens, &scene->ambient))
        ft_error(E_AMBIENT_LIGHT), error = 0;
    else if (tokens[0][0] == LIGHT && !process_light(tokens, &scene->light))
        ft_error(E_LIGHT), error = 0;
    else if (!strcmp(tokens[0], SPHERE) && !process_sphere(tokens, &scene->spheres))
        ft_error(E_SPHERE), error = 0;
    else if (!strcmp(tokens[0], PLANE) && !process_plane(tokens, &scene->planes))
        ft_error(E_PLANE), error = 0;
    else if (!strcmp(tokens[0], CYLINDER) && !process_cylinder(tokens, &scene->cylinders))
        ft_error(E_CYLINDER), error = 0;

    return free_array(tokens), error;
}

int parse_file(const char *filename, scene *scene)
{
    if (!is_rt_file(filename))
        ft_error(E_EXTENSION), exit(EXIT_FAILURE);

    FILE *file = fopen(filename, "r");
    if (!file)
        perror("\033[1;31mError\033[1;37m"), exit(EXIT_FAILURE);

    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1)
        if (!parse_line(line, scene))
            return free(line), fclose(file), 0;
    free(line);
    fclose(file);
    return 1;
}

int get_scene(int argc, char *filename, scene *scene)
{
    if (argc == 2)
    {
        init_scene(scene);
        if (parse_file(filename, scene))
        {
            print_scene(*scene);
            printf("%s%s%s", GR, LOADED_SCENE, RE);
            return 1;
        }
    }
    else
        ft_error(E_USAGE);
    
    return 0;
}

