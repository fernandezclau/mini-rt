#include "../../include/minirt.h"
#include <ctype.h>

int is_float(const char *str)
{
    int dot = 0;
    if (*str == '-' || *str == '+') str++;
    while (*str)
    {
        if (*str == '.')
        {
            if (dot) return 0;
            dot = 1;
        }
        else if (!isdigit(*str) && !isspace(*str))
            return 0;
        str++;
    }
    return 1;
}

int is_int(const char *str)
{
    if (!str || *str == '\0')
        return 0;

    while (*str)
    {
        if (!isdigit(*str) && !isspace(*str))
            return 0;
        str++;
    }

    return 1;
}

int three_floats(char **tokens)
{
    int i = 0;
    
    while (tokens[i])
    {
        if (i > 2)
            return 0;
        if (!is_float(tokens[i]))
            return 0;
        i++;
    }
    return 1;
}

int three_ints(char **tokens)
{
    int i = 0;

    while (tokens[i])
    {
        if (i > 2)
            return 0;
        if (!is_int(tokens[i]))
            return 0;
        i++;
    }
    return 1;
}

int is_valid_color(color rgb)
{
    if (rgb.r < 0 || rgb.r > 255)
        return 0;
    else if(rgb.g < 0 || rgb.g > 255)
        return 0;
    else if (rgb.b < 0 || rgb.b > 255)
        return 0;
    return 1;
}

int is_valid_ratio(float ratio)
{
    return (ratio >= 0 && ratio <= 1);
}
int is_normalized_f_v3(vector3 v)
{
    if (v.x < -1 || v.x > 1)
        return 0;
    else if (v.y < -1 || v.y > 1)
        return 0;
    else if (v.z < -1 || v.z > 1)
        return 0;
    return 1;
}

int is_valid_angle(int angle)
{
    return (angle >= 0 && angle <= 180);
}

// #include "../../include/minirt.h"
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>


// int main(int argc, char **argv)
// {
//     if (argc < 2)
//     {
//         printf("Uso: %s <opciones> <valores>\n", argv[0]);
//         printf("Opciones:\n");
//         printf("  -f <float>            Verifica si el valor es un float válido\n");
//         printf("  -i <int>              Verifica si el valor es un int válido\n");
//         printf("  -3f <float1> <float2> <float3> Verifica si los tres valores son floats válidos\n");
//         printf("  -3i <int1> <int2> <int3> Verifica si los tres valores son ints válidos\n");
//         return 1;
//     }

//     // Opción para verificar si un valor es un float
//     if (strcmp(argv[1], "-f") == 0 && argc == 3)
//     {
//         if (is_float(argv[2]))
//             printf("'%s' es un float válido\n", argv[2]);
//         else
//             printf("'%s' NO es un float válido\n", argv[2]);
//     }
//     // Opción para verificar si un valor es un int
//     else if (strcmp(argv[1], "-i") == 0 && argc == 3)
//     {
//         if (is_int(argv[2]))
//             printf("'%s' es un int válido\n", argv[2]);
//         else
//             printf("'%s' NO es un int válido\n", argv[2]);
//     }
//     // Opción para verificar si tres valores son floats válidos
//     else if (strcmp(argv[1], "-3f") == 0 && argc == 5)
//     {
//         if (three_floats(&argv[2]))
//             printf("Los valores '%s', '%s', '%s' son floats válidos\n", argv[2], argv[3], argv[4]);
//         else
//             printf("Uno o más de los valores no son floats válidos\n");
//     }
//     // Opción para verificar si tres valores son ints válidos
//     else if (strcmp(argv[1], "-3i") == 0 && argc == 5)
//     {
//         if (three_ints(&argv[2]))
//             printf("Los valores '%s', '%s', '%s' son ints válidos\n", argv[2], argv[3], argv[4]);
//         else
//             printf("Uno o más de los valores no son ints válidos\n");
//     }
//     else
//     {
//         printf("Argumentos no válidos. Usa -f, -i, -3f, o -3i con los valores correctos.\n");
//     }

//     return 0;
// }
