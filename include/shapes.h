/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <claferna@student.42madrid.com>   +#+  +:+       +#+        */
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

typedef struct s_cone
{
	t_vector3		center;
	t_vector3		direction;
	float			diameter;
	float			height;
	t_vector3		apex;
	t_color			color;
	struct s_cone	*next;
}					t_cone;

typedef struct s_ugh
{
	float		distance;
	t_vector3	position;
	t_vector3	direction;
}				t_ugh;

// LIST INTERSECTIONS

void	intersection_planes(t_ray *r, t_plane **planes, t_hit *l_hit);
void	intersection_spheres(t_ray *r, t_sphere **spheres, t_hit *l_hit);
void	intersection_cylinders(t_ray *r, t_cylinder **cylinders, t_hit *l_hit);
void	intersection_cones(t_ray *r, t_cone **cones, t_hit *l_hit);

// NORMAL

void	set_cylinder_normal(t_cylinder *cy, t_hit *l_hit);
void	set_sphere_normal(t_hit *l_hit, t_sphere *sp);
void	set_plane_normal(t_ray *r, t_hit *l_hit, t_plane *pl);
void	set_cone_normal(t_cone *cn, t_hit *l_hit);

// INSERTION

int		insert_vector3(t_vector3 *v, char **tokens, int is_normalized);
int		insert_color(t_color *c, char **tokens);
int		insert_angle(float *fov, char *value);
int		insert_ratio(float *ratio, char *value);
int		insert_magnitude(float *magnitude, char *value);

// LIST HANDLING

void	add_sphere(t_sphere **head, t_sphere *new_sphere);
void	add_plane(t_plane **head, t_plane *new_plane);
void	add_cylinder(t_cylinder **head, t_cylinder *new_cylinder);
void	add_cone(t_cone **head, t_cone *new_cone);

// MEMORY RELEASING

void	free_spheres(t_sphere **head);
void	free_plane(t_plane **head);
void	free_cylinder(t_cylinder **head);
void	free_cone(t_cone **head);

// DISPLAY

void	display_spheres(t_sphere *sp);
void	display_planes(t_plane *pl);
void	display_cylinders(t_cylinder *cy);
void	display_cones(t_cone *cn);

// CYLINDER CALCS

int		intersect_circle(t_ray *r, t_ugh *ugh, float radius);
int		calculate_intersection_times(float a, float b, float discriminant, \
		float *d);
int		select_dist_cylinder(t_ugh cylinder_body, t_ugh top_cap, \
		t_ugh bottom_cap, t_hit *hit);
int		select_dist_cylinder2(t_ugh top_cap, t_ugh bottom_cap, t_hit *hit);
int		cylinder_calculations(t_vector3 d_perp, t_vector3 w_perp, \
		t_cylinder *cy, float *d);

// CONE CALCS

int		select_dist_cone(t_ugh base, t_ugh body, t_hit *hit);
int		cone_calculations(t_ray *r, float tantheta2, t_cone *cn, float *d);

#endif  // SHAPES_H
