#ifndef MINIRT_H
    #define MINIRT_H

// ......... LIBS ........
# include <mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <math.h>
# include "./macros.h"
# include "./structs.h"
# include "./vectors.h"
#  include "./camera.h"

// ......... STRUCTS .......

typedef struct s_data {
    void    *mlx_ptr;         // Puntero a la estructura de miniLibX
    void    *win_ptr;         // Puntero a la ventana de miniLibX
    void    *image_ptr;       // Puntero a la imagen de miniLibX
    char    *image_data;       // Puntero a los datos de la imagen
    int     bpp;               // Bits por pixel
    int     size_line;         // Tamaño de la línea
    int     endian;            // Endian
}           t_data;

// WINDOWS MANAGEMENT
int key_hook(int keycode, t_data *data);
int close_window(t_data *data);
int mouse_hook(int button);
void free_mlx_resources(t_data *data);

int get_scene(int argc, char *filename, scene *scene);
// PIXEL MANAGEMENT
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int is_float(const char *str);
int is_int(const char *str);
int three_floats(char **tokens);
int three_ints(char **tokens);
int is_valid_color(color rgb);
int is_normalized_f_v3(vector3 v);
int is_valid_angle(int  angle);
char **ft_split(char const *s, char c);
char **split_spaces(char const *s);
void    ft_error(char *error);
int is_rt_file(const char *filename);

//CAMARA
int process_view(char   **tokens, view *view);
int process_camera(char **tokens, camera *camera);
int process_ambient(char **tokens, ambient_light *ambient_light);
int process_light(char **tokens, light *light);
int process_sphere(char **tokens, sphere **sp);
int process_plane(char **tokens, plane **pl);
int process_cylinder(char **tokens, cylinder **cy);
int array_len(char **array);
void    free_array(char **array);

int is_valid_ratio(float ratio);
#endif