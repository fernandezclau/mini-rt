#include "../include/minirt.h"

// VECTOR 2
vector2 init_v2()
{
    vector2 v;

    v.x = 0;
    v.y = 0;

    return v;
}

vector2 init_p_v2(float x, float y)
{
    vector2 v;

    v.x = x;
    v.y = y;

    return v;
}

// VECTOR 3
vector3 init_v3()
{
    vector3 v;

    v.x = 0;
    v.y = 0;
    v.y = 0;

    return v;
}

vector3 init_p_v3(float x, float y, float z)
{
    vector3 v;

    v.x = x;
    v.y = y;
    v.z = z;

    return v;
}

vector3 v3_substract(vector3 a, vector3 b)
{
    return init_p_v3(a.x - b.x, a.y - b.y, a.z - b.z);    
}

vector3 v3_multiple(vector3 a, vector3 b)
{
    return init_p_v3(a.x * b.x, a.y * b.y, a.z * b.z);
}

vector3 v3_scale(vector3 v, float scalar)
{
    return init_p_v3(v.x * scalar, v.y * scalar, v.z * scalar);
}

float v3_dot_product(vector3 a, vector3 b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

vector3 v3_cross_product(vector3 a, vector3 b)
{
    return init_p_v3(a.y * b.z - a.z * b.y,
                    a.z * b.x - a.x * b.z,
                    a.x * b.y + a.y * b.x);
}

float v3_length2(vector3 v)
{
    return pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2);
}

float v3_length(vector3 v)
{
    return sqrt(v3_length2(v));
}

vector3 v3_normalize(vector3 v)
 {
    float len = v3_length(v);
    
    if (len > 0) {
        return v3_scale(v, 1.0f / len);
    }

    return v;
}

void print_v3(vector3 v)
{
    printf("A x: %f\t", v.x);
    printf("y: %f\t", v.y);
    printf("z: %f\t", v.z);
    printf("\n");
}

// VECTOR 4
vector4 init_v4()
{
    vector4 v;

    v.x = 0;
    v.y = 0;
    v.z = 0;
    v.k = 0;

    return v;
}

vector4 init_p_v4(float x, float y, float z, float k)
{
    vector4 v;

    v.x = x;
    v.y = y;
    v.z = z;
    v.k = k;

    return v;
}

void    init_r_mat(mat4 *m)
{
    m->a = init_v4();
    m->b = init_v4();
    m->c = init_v4();
    m->d = init_v4();
}

vector4 multiple_v4_mat4(mat4 m, vector4 v)
{
    vector4 result;

    result.x = m.a.x * v.x + m.a.y * v.y + m.a.z * v.z + m.a.k * v.k;
    result.y = m.b.x * v.x + m.b.y * v.y + m.b.z * v.z + m.b.k * v.k;
    result.z = m.c.x * v.x + m.c.y * v.y + m.c.z * v.z + m.c.k * v.k;
    result.k = m.d.x * v.x + m.d.y * v.y + m.d.z * v.z + m.d.k * v.k;

    return result;
}

void print_v4(vector4 v)
{
    printf("A x: %f\t", v.x);
    printf("z: %f\t", v.y);
    printf("y: %f\t", v.z);
    printf("k: %f\t", v.k);
    printf("\n");
}

void    print_m4(mat4 m)
{
    printf("A x: %f\t", m.a.x);
    printf("z: %f\t", m.a.y);
    printf("y: %f\t", m.a.z);
    printf("k: %f\t", m.a.k);
    printf("\n");

    printf("B x: %f\t", m.b.x);
    printf("z: %f\t", m.b.y);
    printf("y: %f\t", m.b.z);
    printf("k: %f\t", m.b.k);
    printf("\n");

    printf("C x: %f\t", m.c.x);
    printf("z: %f\t", m.c.y);
    printf("y: %f\t", m.c.z);
    printf("k: %f\t", m.c.k);
    printf("\n");

    printf("D x: %f\t", m.d.x);
    printf("z: %f\t", m.d.y);
    printf("y: %f\t", m.d.z);
    printf("k: %f\t", m.d.k);
    printf("\n");
}

// MATRIX 4
mat4 init_mac4()
{
    mat4 mat;

    mat.a = init_p_v4(1, 0, 0, 0);
    mat.b = init_p_v4(0, 1, 0, 0);
    mat.c = init_p_v4(0, 0, 1, 0);
    mat.d = init_p_v4(0, 0, 0, 1);

    return mat;
}

mat4 init_p_mac4(vector4 a, vector4 b, vector4 c, vector4 d)
{
    mat4 mat;

    mat.a = a;
    mat.b = b;
    mat.c = c;
    mat.d = d;

    return mat;
}

mat4 mac4_multiple(mat4 m1, mat4 m2)
{
    mat4 res;

    // First line
    res.a.x = m1.a.x * m2.a.x + m1.a.y * m2.b.x + m1.a.z * m2.c.x + m1.a.k * m2.d.x;
    res.a.y = m1.a.x * m2.a.y + m1.a.y * m2.b.y + m1.a.z * m2.c.y + m1.a.k * m2.d.y;
    res.a.z = m1.a.x * m2.a.z + m1.a.y * m2.b.z + m1.a.z * m2.c.z + m1.a.k * m2.d.z;
    res.a.k = m1.a.x * m2.a.k + m1.a.y * m2.b.k + m1.a.z * m2.c.k + m1.a.k * m2.d.k;

    // Second line
    res.b.x = m1.b.x * m2.a.x + m1.b.y * m2.b.x + m1.b.z * m2.c.x + m1.b.k * m2.d.x;
    res.b.y = m1.b.x * m2.a.y + m1.b.y * m2.b.y + m1.b.z * m2.c.y + m1.b.k * m2.d.y;
    res.b.z = m1.b.x * m2.a.z + m1.b.y * m2.b.z + m1.b.z * m2.c.z + m1.b.k * m2.d.z;
    res.b.k = m1.b.x * m2.a.k + m1.b.y * m2.b.k + m1.b.z * m2.c.k + m1.b.k * m2.d.k;

    // Third line
    res.c.x = m1.c.x * m2.a.x + m1.c.y * m2.b.x + m1.c.z * m2.c.x + m1.c.k * m2.d.x;
    res.c.y = m1.c.x * m2.a.y + m1.c.y * m2.b.y + m1.c.z * m2.c.y + m1.c.k * m2.d.y;
    res.c.z = m1.c.x * m2.a.z + m1.c.y * m2.b.z + m1.c.z * m2.c.z + m1.c.k * m2.d.z;
    res.c.k = m1.c.x * m2.a.k + m1.c.y * m2.b.k + m1.c.z * m2.c.k + m1.c.k * m2.d.k;

    // Fourth line
    res.d.x = m1.d.x * m2.a.x + m1.d.y * m2.b.x + m1.d.z * m2.c.x + m1.d.k * m2.d.x;
    res.d.y = m1.d.x * m2.a.y + m1.d.y * m2.b.y + m1.d.z * m2.c.y + m1.d.k * m2.d.y;
    res.d.z = m1.d.x * m2.a.z + m1.d.y * m2.b.z + m1.d.z * m2.c.z + m1.d.k * m2.d.z;
    res.d.k = m1.d.x * m2.a.k + m1.d.y * m2.b.k + m1.d.z * m2.c.k + m1.d.k * m2.d.k;

    return res;
}



