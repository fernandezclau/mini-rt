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

// ________________ VECTOR 2 ____________________
vector2 init_v2(void);
vector2 init_p_v2(float x, float y);
void    display_v2(vector2 v);

// ________________ VECTOR 3 ____________________
vector3 init_v3(void);
vector3 init_p_v3(float x, float y, float z);
vector3 init_r_v3(vector3 *v);
vector3 substract_v3(vector3 a, vector3 b);
vector3 cross_product_v3(vector3 a, vector3 b);
vector3 multiple_v3(vector3 a, vector3 b);
vector3 scale_v3(vector3 v, float scalar);
float   dot_product_v3(vector3 a, vector3 b);
float   pow_v3(vector3 v);
float   length_v3(vector3 v);
vector3 normalize_v3(vector3 v);
void    display_v3(vector3 v);

#endif  // VECTORS_H