/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:56:44 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 18:01:33 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct s_vector2
{
	float	x;
	float	y;
}		t_vector2;

typedef struct s_vector3
{
	float	x;
	float	y;
	float	z;
}		t_vector3;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}		t_color;

// VECTOR 2
t_vector2	init_v2(void);
t_vector2	init_p_v2(float x, float y);
void		display_v2(t_vector2 v);

// VECTOR 3
t_vector3	init_v3(void);
t_vector3	init_p_v3(float x, float y, float z);
t_vector3	init_r_v3(t_vector3 *v);

t_vector3	sum_v3(t_vector3 a, t_vector3 b);
t_vector3	substract_v3(t_vector3 a, t_vector3 b);
t_vector3	cross_product_v3(t_vector3 a, t_vector3 b);
t_vector3	multiple_v3(t_vector3 a, t_vector3 b);
t_vector3	scale_v3(t_vector3 v, float scalar);
float		dot_product_v3(t_vector3 a, t_vector3 b);
float		pow_v3(t_vector3 v);
float		length_v3(t_vector3 v);
t_vector3	normalize_v3(t_vector3 v);
float		cos_v3(t_vector3 a, t_vector3 b);
float		sin_v3(t_vector3 a, t_vector3 b);
t_vector3	reflect_v3(t_vector3 light_direction, t_vector3 normal);
void		display_v3(t_vector3 v);

/* COLOR */
int			init_r_color(t_color *c);
int			rgb_to_hex(t_color *c);
t_color		multiply_color(t_color c, t_vector3 v);
t_color		scale_c(t_color c, float factor);
t_color		add_color(t_color a, t_color b);
void		display_color(t_color c);
t_color		vector3_to_color(t_vector3 v);

#endif  // VECTORS_H
