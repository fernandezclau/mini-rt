/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:56:38 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 18:05:03 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "./view.h"
# include "./minirt.h"

typedef struct s_plane
{
	t_vector3		point;
	t_vector3		normal;
	t_color			color;
	struct s_plane	*next;
}					t_plane;

typedef struct s_sphere
{
	t_vector3		center;
	float			diameter;
	float			radius;
	t_color			color;
	struct s_sphere	*next;
}					t_sphere;

typedef struct s_cylinder
{
	t_vector3			center;
	t_vector3			direction;
	float				diameter;
	float				height;
	t_color				color;
	struct s_cylinder	*next;
}						t_cylinder;

typedef struct s_ugh
{
	float		distance;
	t_vector3	position;
	t_vector3	center;
	t_vector3	direction;
}				t_ugh;

// LIST INTERSECTIONS

void	interesection_planes(t_ray *r, t_plane **planes, t_hit *l_hit);
void	intersection_spheres(t_ray *r, t_sphere **spheres, t_hit *l_hit);
void	intersection_cylinders(t_ray *r, t_cylinder **cylinders, t_hit *l_hit);

// SINGLE INTERSECTIONS

int		intersect_ray_plane(t_ray *r, t_plane *pl, t_hit *hit);
int		intersect_ray_sphere(t_ray *r, t_sphere *sphere, t_hit *hit);
int		intersect_ray_cylinder(t_ray *r, t_hit *hit, t_cylinder *cl);

// NORMAL

void	set_cylinder_normal(t_cylinder *cy, t_hit *l_hit);
void	set_sphere_normal(t_hit *l_hit, t_sphere *sp);
void	set_plane_normal(t_ray *r, t_hit *l_hit, t_plane *pl);

// INSERTION

int		insert_vector3(t_vector3 *v, char **tokens, int is_normalized);
int		insert_color(t_color *c, char **tokens);
int		insert_angle(float *fov, char *value);
int		insert_ratio(float *ratio, char *value);
int		insert_magnitude(float *magnitude, char *value);

// LIST HANDLING

void	add_sphere(t_sphere **head, t_sphere *new_sphere);
void	add_plane(t_plane **head, t_plane *new_plain);
void	add_cylinder(t_cylinder **head, t_cylinder *new_cylinder);

// MEMORY RELEASING

void	free_spheres(t_sphere **head);
void	free_plane(t_plane **head);
void	free_cylinder(t_cylinder **head);

// DISPLAY

void	display_spheres(t_sphere *sp);
void	display_planes(t_plane *pl);
void	display_cylinders(t_cylinder *cl);

// CYLINDER CALCS

int		intersect_circle(t_ray *r, t_ugh *ugh, float radius);
int		intersect_cylinder(t_ray *r, t_cylinder *cl, t_ugh *ugh);
int		calculate_intersection_times(float a, float b, float discriminant, \
		float *d);
int		select_dist_cylinder(t_ugh cylinder_body, t_ugh top_cap, \
		t_ugh bottom_cap, t_hit *hit);
int		select_dist_cylinder2(t_ugh top_cap, t_ugh bottom_cap, t_hit *hit);
int		cylinder_calculations(t_vector3 d_perp, t_vector3 w_perp, \
		t_cylinder *cl, float *d);
#endif  // SHAPES_H
