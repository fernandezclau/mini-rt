/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:04:40 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:04:41 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Prints the information of all planes in the linked list.
 *
 * @param pl A pointer to the head of the plane linked list.
 */
void	display_planes(t_plane *pl)
{
	t_plane	*current;
	int		i;

	current = pl;
	i = 1;
	printf(" %s____ PLANES ____ %s\n\n", WH, RE);
	while (current)
	{
		printf("%s %d. %s\n\n", WH, i, RE);
		printf("%s > Point %s", WH, RE);
		display_v3(current->point);
		printf("\n");
		printf("%s > Normal %s", WH, RE);
		display_v3(current->normal);
		printf("\n");
		printf("%s > Color %s", WH, RE);
		display_color(current->color);
		printf("\n");
		current = current->next;
		i++;
	}
}

/**
 * @brief Prints the information of all spheres in the linked list.
 *
 * @param sp A pointer to the head of the sphere linked list.
 */
void	display_spheres(t_sphere *sp)
{
	t_sphere	*current;
	int			i;

	current = sp;
	i = 1;
	printf(" %s____ SPHERES ____ %s\n\n", WH, RE);
	while (current)
	{
		printf("%s %d. %s\n\n", WH, i, RE);
		printf("%s > Center %s", WH, RE);
		display_v3(current->center);
		printf("\n");
		printf("%s > Diameter %s", WH, RE);
		printf("%s[%f]%s\n\n", CY, current->diameter, RE);
		printf("%s > Color %s", WH, RE);
		display_color(current->color);
		printf("\n");
		current = current->next;
		i++;
	}
}

/**
 * @brief Prints the information of all cylinders in the linked list.
 *
 * @param cy A pointer to the head of the cylinder linked list.
 */
void	display_cylinders(t_cylinder *cy)
{
	t_cylinder	*current;
	int			i;

	current = cy;
	i = 1;
	printf(" %s____ CYLINDERS ____ %s\n\n", WH, RE);
	while (current)
	{
		printf("%s %d. %s\n\n", WH, i, RE);
		printf("%s > Center %s", WH, RE);
		display_v3(current->center);
		printf("\n%s > Direction %s", WH, RE);
		display_v3(current->direction);
		printf("\n%s > Diameter %s", WH, RE);
		printf("%s[%f]%s\n\n", CY, current->diameter, RE);
		printf("%s > Height %s", WH, RE);
		printf("%s[%f]%s\n\n", CY, current->height, RE);
		printf("%s > Color %s", WH, RE);
		display_color(current->color);
		printf("\n");
		current = current->next;
		i++;
	}
}
