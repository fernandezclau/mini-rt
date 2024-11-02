// vector3 oc;
    // float   a;
    // float   b;
    // float   c;
    // float   discriminant;
    // float   t1;
    // float   t2;
    
    // oc = substract_v3(r->origin, sp->center);
    // a = dot_product_v3(r->direction, r->direction);
    // b = 2.0f * dot_product_v3(oc, r->direction);
    // c = dot_product_v3(oc, oc) - (sp->radius * sp->radius);
    // discriminant = b * b - 4 * a * c;
    // if (discriminant < 0)
    //     return 0;
    // t1 = (-b - sqrt(discriminant)) / (2 * a);
    // t2 = (-b + sqrt(discriminant)) / (2 * a);
    // if (t1 > 0 && t2 > 0)
    //     hit->dist = fmin(t1, t2);
    // else if (t1 > 0)
    //     hit->dist = t1;
    // else if (t2 > 0)
    //     hit->dist = t2;
    // else
    //     return (0);
    // hit->position = sum_v3(r->origin, scale_v3(r->direction, hit->dist));
    // return (1); 