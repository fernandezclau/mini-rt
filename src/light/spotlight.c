#include "../../include/minirt.h"

vector3	diffuse_intensity(vector3 normal, vector3 p_to_l, vector3 light)
{
    vector3 diffuse;
    float   ratio;

    ratio = fmax(dot_product_v3(p_to_l, normal), 0);
    diffuse = scale_v3(light, ratio);
    return (diffuse);
}

vector3 specular_intensity(vector3 normal, vector3 p_to_l, vector3 light)
{
    float   ratio;
    vector3 specular;
    
    ratio = fmax(dot_product_v3(p_to_l, normal), 0);
    specular = scale_v3(light, pow(ratio, 70) * 3);
    return (specular);
}