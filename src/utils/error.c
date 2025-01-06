/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <claferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:04:34 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:04:36 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Prints an error message to the console.
 * 
 * @param error The error message to print.
 */
void	ft_error(char *error)
{
	printf("%sError: %s%s%s\n", RED, WH, error, RE);
}
