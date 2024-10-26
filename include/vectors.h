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

typedef struct color
{
    int r;
    int g;
    int b;
}       color;

// VECTOR 2
vector2 init_v2(void);
vector2 init_p_v2(float x, float y);
void    display_v2(vector2 v);

/* VECTOR 3 */
vector3 init_v3(void);
vector3 init_p_v3(float x, float y, float z);
vector3 init_r_v3(vector3 *v);

vector3 sum_v3(vector3 a, vector3 b);
vector3 substract_v3(vector3 a, vector3 b);
vector3 cross_product_v3(vector3 a, vector3 b);
vector3 multiple_v3(vector3 a, vector3 b);
vector3 negate_v3(vector3 v);
vector3 scale_v3(vector3 v, float scalar);
float   dot_product_v3(vector3 a, vector3 b);
float   pow_v3(vector3 v);
float   length_v3(vector3 v);
vector3 normalize_v3(vector3 v);
float	cos_v3(vector3 a, vector3 b);
float	sin_v3(vector3 a, vector3 b);
vector3	rotate_vect(vector3 vector, vector3 axis, float cos, float sin);

void    display_v3(vector3 v);

/* COLOR */
int     init_r_color(color *c);
int     rgb_to_hex(color *c);
color   scale_color(color c, float scale);
void    display_color(color c);

#endif  // VECTORS_H