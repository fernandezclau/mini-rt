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
