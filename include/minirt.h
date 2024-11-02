#ifndef MINIRT_H
    #define MINIRT_H

// ......... STRUCTS .......
typedef struct s_data
{
    void    *mlx_ptr;
    void    *win_ptr;
    void    *image_ptr;
    char    *image_data;
    int     bpp;
    int     size_line;
    int     endian;
}           t_data;

// ......... LIBS ........
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <math.h>
# include <float.h>
# include "./macros.h"
# include "./vectors.h"
# include "./view.h"
# include "./shapes.h"

typedef struct scene
{
    camera          camera;
    ambient_light   ambient_light;
    light           *lights;
    sphere          *spheres;
    plane           *planes;
    cylinder        *cylinders;
    int             num_spheres;
    int             num_planes;
    int             num_cylinders;
    hit             hit;
}               scene;

// RENDER (MAIN FUNCTION)
void    render(t_data *data, scene *scene);

// RAY INTERSECTION
void    ray_intersection(ray r, scene *scene);
int is_in_shadow(vector3 point, light *light_source, scene *scene);
color   calculate_light(ray r, scene *scene);
vector3	intersection_point(ray ray, double distance);

// SCENE
void    init_scene(scene *scene);
int     get_scene(int argc, char *filename, scene *scene);
void    free_scene(scene *scene);
void    print_scene(scene scene);

// PIXEL MANAGEMENT
void	pixel_put(t_data *data, int x, int y, int color);

// WINDOWS MANAGEMENT
int     key_hook(int keycode, t_data *data);
int     close_window(t_data *data);
int     mouse_hook(int button);

// WINDOWS MEMORY RELEASE
void    free_mlx_resources(t_data *data);

// PARSING
int     process_camera(char **tokens, camera *camera);
int     process_ambient(char **tokens, ambient_light *ambient_light);
int     process_light(char **tokens, light **l);
int     process_sphere(char **tokens, sphere **sp);
int     process_plane(char **tokens, plane **pl);
int     process_cylinder(char **tokens, cylinder **cy);

// PARSING VALIDATIONS
int     is_float(const char *str);
int     is_int(const char *str);
int     three_floats(char **tokens);
int     three_ints(char **tokens);
int     is_valid_ratio(float ratio);
int     is_valid_color(color rgb);
int     is_normalized_f_v3(vector3 v);
int     is_valid_angle(int  angle);
int     is_rt_file(const char *filename);

// UTILS
char    **ft_split(char const *s, char c);
char    **split_spaces(char const *s);
int     array_len(char **array);
void    free_array(char **array);
void    ft_error(char *error);

#endif