/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <claferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:52:33 by claferna          #+#    #+#             */
/*   Updated: 2024/03/27 22:48:45 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

/* DESC: The 'ft_find_line' finds the '\n' character in BUFFER_SIZE range.*/
int	ft_find_line(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->content[i] && i < BUFFER_SIZE)
		{
			if (list->content[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

/* DESC: The 'ft_lstlast' function finds the last element of a list.*/
t_list	*ft_lstlast(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/* DESC: The 'ft_lstadd_line' adds a new element to a list.*/
void	ft_lstadd_line(t_list **list, char *buffer)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return ;
	last_node = ft_lstlast(*list);
	if (!new_node)
		return ;
	if (!last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->content = buffer;
	new_node->next = NULL;
}

/* DESC: The 'ft_get_len_line' gets the length of the current line.*/
int	ft_get_len_line(t_list *list)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->content[i] != '\0')
		{
			if (list->content[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		list = list->next;
	}
	return (len);
}

/* DESC: The 'ft_extract_line_lst' extracts all the elements of the list 
corresponding to the current line.*/
void	ft_extract_line_lst(t_list *list, char *line)
{
	int	i;
	int	k;

	if (!list)
		return ;
	k = 0;
	while (list)
	{
		i = 0;
		while (list->content[i] != '\0')
		{
			if (list->content[i] == '\n')
			{
				line[k++] = '\n';
				line[k] = '\0';
				return ;
			}
			line[k++] = list->content[i++];
		}
		list = list->next;
	}
	line[k] = '\0';
}
