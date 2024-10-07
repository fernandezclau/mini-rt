#ifndef VECTORS_H
    #define VECTORS_H

typedef struct vector2
{
    float   x;
    float   y;
}           vector2;

typedef struct vector3
{
    float   x;
    float   y;
    float   z;
}           vector3;

typedef struct vector4
{
    float   x;
    float   y;
    float   z;
    float   k;
}           vector4;

typedef struct mat4
{
    vector4 a;
    vector4 b;
    vector4 c;
    vector4 d;
}           mat4;

vector2 init_v2();
vector2 init_p_v2(float x, float y);

vector3 init_v3();
vector3 init_p_v3(float x, float y, float z);
vector3 v3_substract(vector3 a, vector3 b);
vector3 v3_cross_product(vector3 a, vector3 b);
vector3 v3_multiple(vector3 a, vector3 b);
vector3 v3_scale(vector3 v, float scalar);
float v3_dot_product(vector3 a, vector3 b);
float v3_length2(vector3 v);
float v3_length(vector3 v);
vector3 v3_normalize(vector3 v);
void print_v3(vector3 v);

vector4 init_v4();
vector4 init_p_v4(float x, float y, float z, float k);
vector4 multiple_v4_mat4(mat4 m, vector4 v);
void print_v4(vector4 v);

mat4 init_mac4();
mat4 init_p_mac4(vector4 a, vector4 b, vector4 c, vector4 d);
mat4 mac4_multiple(mat4 a, mat4 b);
void    print_m4(mat4 m);


#endif  // VECTORS_H