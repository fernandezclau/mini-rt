/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:56:28 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 18:00:50 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// ......... LIBS ........
# include "mlx.h"
# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include "../lib/libft/libft.h"
# include "./macros.h"
# include "./vectors.h"
# include "./view.h"
# include "./shapes.h"

// ......... STRUCTS .......

typedef struct s_scene
{
	t_camera		camera;
	t_ambient_light	ambient_light;
	t_light			*lights;
	t_sphere		*spheres;
	t_plane			*planes;
	t_cylinder		*cylinders;
	t_cone			*cones;
	int				num_spheres;
	int				num_planes;
	int				num_cylinders;
}			t_scene;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*image_ptr;
	char	*image_data;
	int		bpp;
	int		size_line;
	int		endian;
	t_scene	*scene;
}	t_data;

// RENDER (MAIN FUNCTION)

void		render(t_data *data, t_scene *scene);

// RAY

void		ray_intersection(t_ray r, t_scene *scene, t_hit *hit);
t_vector3	calculate_ray_direction(t_scene *scene, unsigned x, unsigned y);
void		set_intersection_position(t_ray *r, t_hit *hit);

// LIGHT

void		calculate_light(t_scene *scene, t_hit *initial_hit);

// SCENE

void		init_scene(t_scene *scene);
int			get_scene(int argc, char *filename, t_scene *scene);
void		free_scene(t_scene *scene);
void		print_scene(t_scene scene);

// PIXEL MANAGEMENT

void		pixel_put(t_data *data, int x, int y, int color);

// WINDOWS MANAGEMENT

int			key_hook(int keycode, t_data *data);
int			close_window(t_data *data);
int			mouse_hook(int button);

// WINDOWS MEMORY RELEASE

void		free_resources(t_data *data);

// PARSING

int			process_camera(char **tokens, t_camera *camera);
int			process_ambient(char **tokens, t_ambient_light *ambient_light);
int			process_light(char **tokens, t_light **l);
int			process_sphere(char **tokens, t_sphere **sp);
int			process_plane(char **tokens, t_plane **pl);
int			process_cylinder(char **tokens, t_cylinder **cy);
int			process_cone(char **tokens, t_cone **cn);

// PARSING VALIDATIONS

int			is_float(const char *str);
int			is_int(const char *str);
int			three_floats(char **tokens);
int			three_ints(char **tokens);
int			is_valid_ratio(float ratio);
int			is_valid_color(t_color rgb);
int			is_normalized_f_v3(t_vector3 v);
int			is_valid_angle(int angle);
int			is_rt_file(const char *filename);

// UTILS

// char		**ft_split(char const *s, char c);
char		**split_spaces(char const *s);
int			array_len(char **array);
void		free_array(char **array);
void		ft_error(char *error);
void		init_ugh_cylinder(t_ugh *top_cap, t_ugh *cylinder_cap, \
			t_ugh *bottom_cap, t_cylinder *cl);

#endif
