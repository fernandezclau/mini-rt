#ifndef VECTOR3_H
#define VECTOR3_H

#include <stdio.h>
#include <math.h>
#include "./structs.h"
// typedef struct vector3 {
//     float   x;
//     float   y;
//     float   z;
// }               vector3;

//vector3 create_vector3(float x, float y, float z);

vector3 add(vector3 a, vector3 b);
vector3 substract(vector3 a, vector3 b);
vector3 multiple(vector3 a, vector3 b);
vector3 divide(vector3 a, vector3 b);
 
vector3 scale(vector3 v, float scalar);
float   length(vector3 v);
vector3 normalize(vector3 v);
#endif
