/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cn_calculation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:07:10 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/12/16 19:07:12 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Initializes intersection data for the cone caps and body.
 * 
 * @param base Ugh structure representing the base of the cone.
 * @param body Ugh structure representing the cone body.
 * @param cl cone structure to initialize intersection data for.
 */
void	init_ugh_cone(t_ugh *base, t_ugh *body, t_cone *cn)
{
	cn->direction = normalize_v3(cn->direction);
	body->distance = FLT_MAX;
	base->distance = FLT_MAX;
	base->position = sum_v3(cn->center, scale_v3(cn->direction, cn->height));
	base->direction = cn->direction;
}
