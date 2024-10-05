#include "../include/vector3.h"
#include "../include/minirt.h"

// vector3 create_vector3(float x, float y, float z)
// {
//     vector3 v;
    
//     v.x = x;
//     v.y = y;
//     v.z = z;
    
//     return v;
// }

// vector3 add(vector3 a, vector3 b)
// {
//     return create_vector3(a.x + b.x, a.y + b.y, a.z + b.z);    
// }

// vector3 substract(vector3 a, vector3 b)
// {
//     return create_vector3(a.x - b.x, a.y - b.y, a.z - b.z);    
// }

// vector3 multiple(vector3 a, vector3 b)
// {
//     return create_vector3(a.x * b.x, a.y * b.y, a.z * b.z);
// }

// vector3 divide(vector3 a, vector3 b)
// {
//     return create_vector3(a.x / b.x, a.y / b.y, a.z / b.z);    
// }

// vector3 scale(vector3 v, float scalar)
// {
//     return create_vector3(v.x * scalar, v.y * scalar, v.z * scalar);
// }

// float length2(vector3 v)
// {
//     return sqr(v.x) + sqr(v.y) + sqr(v.z);
// }

// float length(vector3 v)
// {
//     return sqrt(length2(v));
// }

// vector3 normalize(vector3 v)
//  {
//     float len = length(v);
//     if (len > 0) {
//         return scale(v, 1.0f / len);
//     }
//     return v;
// }