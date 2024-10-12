#include "../../include/minirt.h"

/**
 * @brief Checks if a given string represents a valid floating-point number.
 * 
 * @param str The string to be checked.
 * @return 1 if the string is a valid float, 0 otherwise.
 */
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

/**
 * @brief Checks if a given string represents a valid integer.
 *
 * @param str The string to be checked.
 * @return 1 if the string is a valid integer, 0 otherwise.
 */
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

/**
 * @brief Checks if an array of strings contains exactly three valid floats.
 *
 * @param tokens An array of strings representing float values.
 * @return 1 if the array contains three valid floats, 0 otherwise.
 */
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

/**
 * @brief Checks if an array of strings contains exactly three valid integers.
 *
 * @param tokens An array of strings representing integer values.
 * @return 1 if the array contains three valid integers, 0 otherwise.
 */
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

/**
 * @brief Validates if a color has RGB components within the valid range (0-255).
 *
 * @param rgb A color structure with r, g, and b components.
 * @return 1 if all components are within the range, 0 otherwise.
 */
int is_valid_color(color rgb)
{
    if (rgb.r < 0 || rgb.r > 255)
        return 0;
    else if (rgb.g < 0 || rgb.g > 255)
        return 0;
    else if (rgb.b < 0 || rgb.b > 255)
        return 0;
    return 1;
}

/**
 * @brief Checks if a given ratio is within the valid range [0, 1].
 *
 * @param ratio The ratio to check.
 * @return 1 if the ratio is valid, 0 otherwise.
 */
int is_valid_ratio(float ratio)
{
    return (ratio >= 0 && ratio <= 1);
}

/**
 * @brief Checks if a 3D vector is normalized (i.e., each component is between -1 and 1).
 *
 * @param v The 3D vector to check.
 * @return 1 if the vector is normalized, 0 otherwise.
 */
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

/**
 * @brief Checks if an angle is within the valid range [0, 180] degrees.
 *
 * @param angle The angle to check.
 * @return 1 if the angle is valid, 0 otherwise.
 */
int is_valid_angle(int angle)
{
    return (angle >= 0 && angle <= 180);
}