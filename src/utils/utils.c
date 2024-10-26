#include "../../include/minirt.h"

/**
 * @brief Calculates the length of a string array.
 * 
 * @param array The string array to measure.
 * @return int The number of elements in the array (not including the NULL terminator).
 */
int array_len(char **array)
{
    int i = 0;
    while (array[i])
        i++;
    return i;
}

/**
 * @brief Splits a string into an array of substrings based on a specified delimiter.
 * 
 * @param s The string to split.
 * @param c The delimiter character to split the string by.
 * @return char** An array of substrings, NULL-terminated. 
 *                NULL is returned in case of an allocation error.
 */
char **ft_split(char const *s, char c)
{
    char **array;
    int i = 0, j = 0, start, end;

    if (!s || !(array = malloc(sizeof(char *) * (strlen(s) + 1))))
        return NULL;

    while (s[i])
    {
        while (s[i] == c)
            i++;
        start = i;
        while (s[i] && s[i] != c)
            i++;
        end = i;
        if (end > start)
        {
            array[j] = strndup(&s[start], end - start);
            j++;
        }
    }
    array[j] = NULL;
    return array;
}

/**
 * @brief Splits a string into an array of substrings based on whitespace characters.
 * 
 * @param s The string to split.
 * @return char** An array of substrings, NULL-terminated.
 *                NULL is returned in case of an allocation error.
 */
char **split_spaces(char const *s)
{
    char **array;
    int i = 0, j = 0, start, end;

    if (!s || !(array = malloc(sizeof(char *) * (strlen(s) + 1))))
        return NULL;

    while (s[i])
    {
        while (isspace(s[i]))
            i++;
        start = i;
        while (s[i] && !isspace(s[i]))
            i++;
        end = i;
        if (end > start)
        {
            array[j] = strndup(&s[start], end - start);
            j++;
        }
    }
    array[j] = NULL;
    return array;
}

/**
 * @brief Frees the memory allocated for an array of strings.
 * 
 * @param array The array of strings to free.
 */
void    free_array(char **array)
{
    int i = 0;
    while (array[i])
        free(array[i++]);
    free(array);
    array = NULL;
}

/**
 * @brief Prints an error message to the console.
 * 
 * @param error The error message to print.
 */
void    ft_error(char *error)
{
    printf("%sError: %s%s%s\n", RED, WH, error, RE);
}

/**
 * @brief Checks if a filename has a .rt extension.
 * 
 * @param filename The filename to check.
 * @return int Returns 1 if the filename ends with .rt, 0 otherwise.
 */
int is_rt_file(const char *filename)
{
    const char *dot = strrchr(filename, '.');

    if (!dot || dot == filename)
        return 0;

    return (strcmp(dot, ".rt") == 0);
}