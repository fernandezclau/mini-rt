#include "../../include/minirt.h"

int array_len(char **array)
{
    int i = 0;
    while (array[i])
        i++;
    return i;
}

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

void    free_array(char **array)
{
    int i = 0;
    while (array[i])
        free(array[i++]);
    free(array);
    array = NULL;
}

void    ft_error(char *error)
{
    printf("%sError: %s%s%s\n", RED, WH, error, RE);
}

int is_rt_file(const char *filename)
{
    const char *dot = strrchr(filename, '.');

    if (!dot || dot == filename)
        return 0;

    return (strcmp(dot, ".rt") == 0);
}