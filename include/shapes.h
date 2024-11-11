/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:56:38 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:02:11 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "./view.h"
# include "./minirt.h"

typedef struct s_plane
{
	vector3			point;
	vector3			normal;
	color			color;
	struct s_plane	*next;
}					plane;

typedef struct s_sphere
{
	vector3			center;
	float			diameter;
	float			radius;
	color			color;
	struct s_sphere	*next;
}					sphere;

typedef struct s_cylinder
{
	vector3			center;
	vector3			direction;
	float			diameter;
	float			height;
	color			color;
	struct s_cylinder	*next;
}					cylinder;

typedef struct s_ugh
{
	float	distance;
	vector3	position;
	vector3	center;
	vector3	direction;
}			ugh;

// LIST INTERSECTIONS
void	interesection_planes(ray *r, plane **planes, hit *l_hit);
void	intersection_spheres(ray *r, sphere **spheres, hit *l_hit);
void	intersection_cylinders(ray *r, cylinder **cylinders, hit *l_hit);

// SINGLE INTERSECTIONS
int		intersect_ray_plane(ray *r, plane *pl, hit *hit);
int		intersect_ray_sphere(ray *r, sphere *sphere, hit *hit);
int		intersect_ray_cylinder(ray *r, hit *hit, cylinder *cl);

// NORMAL
void	set_cylinder_normal(ray *r, cylinder *cy, hit *l_hit);
void	set_sphere_normal(ray *r, hit *l_hit, sphere *sp);
void	set_plane_normal(ray *r, hit *l_hit, plane *pl);

// INSERTION
int		insert_vector3(vector3 *v, char **tokens, int is_normalized);
int		insert_color(color *c, char **tokens);
int		insert_angle(float *fov, char *value);
int		insert_ratio(float *ratio, char *value);
int		insert_magnitude(float *magnitude, char *value);

// LIST HANDLING
void	add_sphere(sphere **head, sphere *new_sphere);
void	add_plane(plane **head, plane *new_plain);
void	add_cylinder(cylinder **head, cylinder *new_cylinder);

// MEMORY RELEASING
void	free_spheres(sphere **head);
void	free_plane(plane **head);
void	free_cylinder(cylinder **head);

// DISPLAY
void	display_spheres(sphere *sp);
void	display_planes(plane *pl);
void	display_cylinders(cylinder *cl);

// CYLINDER CALCS
int		intersect_circle(ray *r, ugh *ugh, float radius);
int		intersect_cylinder(ray *r, cylinder *cl, ugh *ugh);
int		calculate_intersection_times(float a, float b, float discriminant, \
		float *d);
int		select_dist_cylinder(ugh cylinder_body, ugh top_cap, ugh bottom_cap, \
		hit *hit);
int		select_dist_cylinder2(ugh top_cap, ugh bottom_cap, hit *hit);
int		cylinder_calculations(vector3 d_perp, vector3 w_perp, \
		cylinder *cl, float *d);
#endif  // SHAPES_H
