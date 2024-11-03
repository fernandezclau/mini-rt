#include "../../include/minirt.h"

/**
 * @brief Checks if a given string represents a valid floating-point number.
 * 
 * @param str The string to be checked.
 * @return 1 if the string is a valid float, 0 otherwise.
 */
int	is_float(const char *str)
{
	int	dot;

	dot = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str == '.')
		{
			if (dot)
				return (0);
			dot = 1;
		}
		else if (!isdigit(*str) && !isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

/**
 * @brief Checks if a given string represents a valid integer.
 *
 * @param str The string to be checked.
 * @return 1 if the string is a valid integer, 0 otherwise.
 */
int	is_int(const char *str)
{
	if (!str || *str == '\0')
		return (0);
	while (*str)
	{
		if (!isdigit(*str) && !isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

/**
 * @brief Checks if an array of strings contains exactly three valid floats.
 *
 * @param tokens An array of strings representing float values.
 * @return 1 if the array contains three valid floats, 0 otherwise.
 */
int	three_floats(char **tokens)
{
	int		i;

	i = 0;
	while (tokens[i])
	{
		if (i > 2)
			return (0);
		if (!is_float(tokens[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Checks if an array of strings contains exactly three valid integers.
 *
 * @param tokens An array of strings representing integer values.
 * @return 1 if the array contains three valid integers, 0 otherwise.
 */
int	three_ints(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (i > 2)
			return (0);
		if (!is_int(tokens[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Validates if a color has RGB components within the valid range (0-255).
 *
 * @param rgb A color structure with r, g, and b components.
 * @return 1 if all components are within the range, 0 otherwise.
 */
int	is_valid_color(color rgb)
{
	if (rgb.r < 0 || rgb.r > 255)
		return (0);
	else if (rgb.g < 0 || rgb.g > 255)
		return (0);
	else if (rgb.b < 0 || rgb.b > 255)
		return (0);
	return (1);
}
