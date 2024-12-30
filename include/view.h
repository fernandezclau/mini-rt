/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:56:48 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 18:04:09 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEW_H
# define VIEW_H

# include "./minirt.h"

typedef struct s_camera
{
	t_vector3	position;
	t_vector3	direction;
	t_vector3	right; //TODO calculate this in process_camera instead of calculate_ray_direction
	t_vector3	true_up;
	float		fov;
}				t_camera;

typedef struct s_ray
{
	t_vector3	origin;
	t_vector3	direction;
}				t_ray;

typedef struct s_ambient_light
{
	float	ratio;
	t_color	color;
}			t_ambient_light;

typedef struct s_light
{
	t_vector3		position;
	float			brightness;
	t_color			color;
	struct s_light	*next;
}					t_light;

typedef struct s_hit
{
	float		dist;
	float		min_dist;
	int			intersect;
	t_color		final_color;
	t_vector3	position;
	t_vector3	normal;
	int			reflection;
}				t_hit;

// LIGHT

t_vector3	calculate_intensity(t_color colour, float ratio);
t_vector3	calculate_ambient_light(t_ambient_light light);
t_vector3	calculate_spotlight(t_light light, t_vector3 normal, \
		t_vector3 p_to_l);
t_vector3	calculate_diffuse(t_vector3 normal, t_vector3 p_to_l, \
		t_vector3 light);
t_vector3	calculate_specular(t_vector3 normal, t_vector3 p_to_l, \
		t_vector3 light);

// INITIALIZATION

void		init_camera(t_camera *c);
void		init_light(t_light *l);
void		init_ambient_light(t_ambient_light *al);
void		init_hit_point(t_hit *hit);

// LIST

void		add_light(t_light **head, t_light *new_plane);

// MEMORY RELEASING

void		free_lights(t_light **head);

// DISPLAY

void		display_camera(t_camera c);
void		display_ambient_light(t_ambient_light al);
void		display_light(t_light *l);

#endif // VIEW_H
