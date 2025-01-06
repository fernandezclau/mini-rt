/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <claferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:04:24 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:31:48 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vector3	get_up(t_vector3 direction)
{
	t_vector3	up;

	up = init_p_v3(0.0f, 1.0f, 0.0f);
	if (fabs(direction.y) > 0.9999f)
		up = init_p_v3(1.0f, 0.0f, 0.0f);
	return (up);
}
