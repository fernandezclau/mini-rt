/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:48:14 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/12/11 19:48:16 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Adds a cone to the end of the cone linked list.
 *
 * @param head A pointer to a pointer to the head of the cone linked list.
 * @param new_cone A pointer to the new cone to be added.
 */
void	add_cone(t_cone **head, t_cone *new_cone)
{
	t_cone	*last;

	if (*head == NULL)
		*head = new_cone;
	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_cone;
	}
}
