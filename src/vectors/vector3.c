#include "../../include/minirt.h"

/**
 * @brief Creates and returns a 3D vector initialized to (0, 0, 0).
 *
 * @return A vector3 structure with all components (x, y, z) set to 0.
 */
vector3 init_v3(void)
{
    vector3 v;

    v.x = 0;
    v.y = 0;
    v.z = 0;

    return v;
}

/**
 * @brief Initializes a 3D vector with the given x, y, and z components.
 *
 * @param x The x component of the vector.
 * @param y The y component of the vector.
 * @param z The z component of the vector.
 * @return A vector3 structure initialized with the given x, y, and z values.
 */
vector3 init_p_v3(float x, float y, float z)
{
    vector3 v;

    v.x = x;
    v.y = y;
    v.z = z;

    return v;
}

/**
 * @brief Initializes a vector3 structure to zero.
 *
 * @param v A pointer to the vector3 structure to be initialized.
 */
vector3 init_r_v3(vector3 *v)
{
    v->x = 0;
    v->y = 0;
    v->z = 0;
}

/**
 * @brief Sum two 3D vectors component-wise.
 *
 * @param a The first vector (minuend).
 * @param b The second vector (subtrahend).
 * @return A new vector3 representing the result of the sum.
 */
vector3 sum_v3(vector3 a, vector3 b)
{
    return init_p_v3(a.x + b.x, a.y + b.y, a.z + b.z);
}

/**
 * @brief Subtracts two 3D vectors component-wise.
 *
 * @param a The first vector (minuend).
 * @param b The second vector (subtrahend).
 * @return A new vector3 representing the result of the subtraction.
 */
vector3 substract_v3(vector3 a, vector3 b)
{
    return init_p_v3(a.x - b.x, a.y - b.y, a.z - b.z);
}

/**
 * @brief Multiplies two 3D vectors component-wise.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return A new vector3 representing the component-wise product of `a` and `b`.
 */
vector3 multiple_v3(vector3 a, vector3 b)
{
    return init_p_v3(a.x * b.x, a.y * b.y, a.z * b.z);
}

/**
 * @brief Scales a 3D vector by a scalar value.
 *
 * @param v The vector to scale.
 * @param scalar The scaling factor.
 * @return A new vector3 scaled by the given scalar.
 */
vector3 scale_v3(vector3 v, float scalar)
{
    return init_p_v3(v.x * scalar, v.y * scalar, v.z * scalar);
}

/**
 * @brief Computes the dot product of two 3D vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return A float representing the dot product of the two vectors.
 */
float dot_product_v3(vector3 a, vector3 b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

/**
 * @brief Computes the cross product of two 3D vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return A new vector3 that is the cross product of `a` and `b`.
 */
vector3 cross_product_v3(vector3 a, vector3 b)
{
    return init_p_v3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

/**
 * @brief Computes the squared length (magnitude) of a 3D vector.
 *
 * @param v The vector whose squared length is to be calculated.
 * @return A float representing the squared length of the vector.
 */
float pow_v3(vector3 v)
{
    return pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2);
}

/**
 * @brief Computes the length (magnitude) of a 3D vector.
 *
 * The length of a vector represents its magnitude or distance from the origin.
 *
 * @param v The vector whose length is to be calculated.
 * @return A float representing the length of the vector.
 */
float length_v3(vector3 v)
{
    return sqrt(pow_v3(v));
}

/**
 * @brief Normalizes a 3D vector to have a length of 1.
 *
 * @param v The vector to normalize.
 * @return A new vector3 that is the normalized version of the input vector.
 */
vector3 normalize_v3(vector3 v)
{
    float len = length_v3(v);

    if (len > 0) {
        return scale_v3(v, 1.0f / len);
    }

    return v;
}

/**
 * @brief Prints the components of a 3D vector on the console.
 * 
 * @param v The 3D vector to print.
 */
void    display_v3(vector3 v)
{
    printf("x:%s [%f] %s \t", PIN, v.x, RE);
    printf("y:%s [%f] %s \t", CY, v.y, RE);
    printf("z:%s [%f] %s \t", YE, v.z, RE);
    printf("\n");
}
