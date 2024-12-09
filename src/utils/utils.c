/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:04:44 by claferna          #+#    #+#             */
/*   Updated: 2024/11/11 17:04:45 by claferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/**
 * @brief Calculates the length of a string array.
 * 
 * @param array The string array to measure.
 * @return int The number of elements in the array.
 */
int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

/**
 * @brief Splits a string into an array of substrings based 
 * on a specified delimiter.
 * 
 * @param s The string to split.
 * @param c The delimiter character to split the string by.
 * @return char** An array of substrings, NULL-terminated. 
 *                NULL is returned in case of an allocation error.
 */
char	**ft_split(char const *s, char c) //TODO get rid of strndup or function
{
	char	**array;
	int		i;
	int		j;
	int		start;
	int		end;

	i = 0;
	j = 0;
	array = malloc(sizeof(char *) * (ft_strlen(s) + 1));
	if (!s || !(array))
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		end = i;
		if (end > start)
			array[j++] = strndup(&s[start], end - start);
	}
	array[j] = NULL;
	return (array);
}

/**
 * @brief Splits a string into an array of substrings based 
 * on whitespace characters.
 * 
 * @param s The string to split.
 * @return char** An array of substrings, NULL-terminated.
 *                NULL is returned in case of an allocation error.
 */
char	**split_spaces(char const *s) //TODO get rid of strndup
{
	char	**array;
	int		i;
	int		j;
	int		start;
	int		end;

	i = 0;
	j = 0;
	array = malloc(sizeof(char *) * (ft_strlen(s) + 1));
	if (!s || !(array))
		return (NULL);
	while (s[i])
	{
		while (((s[i] >= 9 && s[i] <= 13) || s[i] == 32))
			i++;
		start = i;
		while (s[i] && !((s[i] >= 9 && s[i] <= 13) || s[i] == 32))
			i++;
		end = i;
		if (end > start)
			array[j++] = strndup(&s[start], end - start);
	}
	array[j] = NULL;
	return (array);
}

/**
 * @brief Frees the memory allocated for an array of strings.
 * 
 * @param array The array of strings to free.
 */
void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	array = NULL;
}

/**
 * @brief Checks if a filename has a .rt extension.
 * 
 * @param filename The filename to check.
 * @return int Returns 1 if the filename ends with .rt, 0 otherwise.
 */
int	is_rt_file(const char *filename)
{
	const char	*dot;

	dot = ft_strrchr(filename, '.');
	if (!dot || dot == filename)
		return (0);
	return (ft_strncmp(dot, ".rt", 4) == 0);
}
