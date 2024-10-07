#include "../../include/minirt.h"

void init_scene(scene *scene)
{
    // SPHERE INIT
    scene->spheres = NULL;
    
    // PLANE INIT
    scene->planes = NULL;

    // CYLINDER INIT
    scene->cylinders = NULL;
}

int insert_vector3(vector3 *v, char **tokens, int is_normalized)
{
    if (!three_floats(tokens))
        return free_array(tokens), 0;

    v->x = atof(tokens[0]);
    v->y = atof(tokens[1]);
    v->z = atof(tokens[2]);
    
    free_array(tokens);

    if (is_normalized && !is_normalized_f_v3(*v))
        return 0;

    return 1;
}

int insert_color(color *c, char **tokens)
{
    if (!three_ints(tokens))
        return free_array(tokens), 0;
    
    c->r = atoi(tokens[0]);
    c->g = atoi(tokens[1]);
    c->b = atoi(tokens[2]);

    free_array(tokens);

    if (!is_valid_color(*c))
        return 0;
    
    return 1;
}

int insert_angle(float *fov, char *value)
{
    if (!is_int(value))
        return 0;
    
    *fov = atoi(value);
    
    if (!is_valid_angle(*fov))
        return 0;
    
    return 1;
}

int insert_ratio(float *ratio, char *value)
{
    if (!is_float(value))
        return 0;
    
    *ratio = atof(value);
    
    if (!is_valid_ratio(*ratio))
        return 0;
    
    return 1;
}

int insert_magnitude(float *magnitude, char *value)
{
    if (!is_float(value))
        return 0;
    
    *magnitude = atof(value);

    return 1;
}

void    add_sphere(sphere **head, sphere *new_sphere)
{
    if (*head == NULL)
        *head = new_sphere;
    else 
    {
        sphere *last = *head;
        while (last->next != NULL)
              last = last->next;
        last->next = new_sphere;
    }
}

void    add_plane(plane **head, plane *new_plain)
{
    if (*head == NULL)
        *head = new_plain;
    else 
    {
        plane *last = *head;
        while (last->next != NULL)
              last = last->next;
        last->next = new_plain;
    }
}

void    add_cylinder(cylinder **head, cylinder *new_cylinder)
{
    if (*head == NULL)
        *head = new_cylinder;
    else 
    {
        cylinder *last = *head;
        while (last->next != NULL)
              last = last->next;
        last->next = new_cylinder;
    }
}

void    free_scene(scene *scene)
{
    free_spheres(&scene->spheres);
    free_plane(&scene->planes);
    free_cylinder(&scene->cylinders);
}

void    free_spheres(sphere **head)
{
    sphere *current = *head;
    sphere *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

void    free_plane(plane **head)
{
    plane *current = *head;
    plane *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

void    free_cylinder(cylinder **head)
{
    cylinder *current = *head;
    cylinder *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

// PRINTING
void    print_color(color c)
{
    printf("r:%s [%d] %s \t\t", RED, c.r, RE);
    printf("g:%s [%d] %s \t\t", GR, c.g, RE);
    printf("b:%s [%d] %s \t\t", CY, c.b, RE);
    printf("\n");
}

void    print_vector3(vector3 v)
{
    printf("x:%s [%f] %s \t", PIN, v.x, RE);
    printf("y:%s [%f] %s \t", CY, v.y, RE);
    printf("z:%s [%f] %s \t", YE, v.z, RE);
    printf("\n");
}

void    print_camera(camera c)
{
    printf(" %s____ CAMARA ____ %s\n", WH, RE);
    printf("\n");
    printf("%s > Position %s", WH, RE);
    print_vector3(c.position);
    printf("\n");
    printf("%s > Direction %s", WH, RE);
    print_vector3(c.direction);
    printf("\n");
    printf("%s > Fov %s", WH, RE);
    printf("%s[%f]%s\n", CY, c.fov, RE);
    printf("\n");
}

void    print_ambient_light(ambient_light al)
{
    printf(" %s____ AMBIENT LIGHT ____ %s\n", WH, RE);
    printf("\n");
    printf("%s > Ratio %s", WH, RE);
    printf("%s[%f]%s\n", CY, al.ratio, RE);
    printf("\n");
    printf("%s > Color %s", WH, RE);
    print_color(al.color);
    printf("\n");
}

void    print_light(light l)
{
    printf(" %s____ LIGHT ____ %s\n", WH, RE);
    printf("\n");
    printf("%s > Position %s", WH, RE);
    print_vector3(l.position);
    printf("\n");
    printf("%s > Brightness %s", WH, RE);
    printf("%s[%f]%s\n", CY, l.brightness, RE);
    printf("\n");
    printf("%s > Color %s", WH, RE);
    print_color(l.color);
    printf("\n");
}

void    print_spheres(sphere *sp)
{
    sphere  *current = sp;
    int i = 1;
    printf(" %s____ SPHERES ____ %s\n", WH, RE);
    printf("\n");    
    while (current)
    {
        printf("%s %d. %s\n", WH, i, RE);
        printf("\n");
        printf("%s > Center %s", WH, RE);
        print_vector3(sp->center);
        printf("\n");
        printf("%s > Diameter %s", WH, RE);
        printf("%s[%f]%s\n", CY, sp->diameter, RE);
        printf("\n");
        printf("%s > Color %s", WH, RE);
        print_color(sp->color);
        printf("\n");
        current = current->next;
        i++;
    }
}

void    print_planes(plane *pl)
{
    plane  *current = pl;
    int i = 1;
    printf(" %s____ PLANES ____ %s\n", WH, RE);
    printf("\n");    
    while (current)
    {
        printf("%s %d. %s\n", WH, i, RE);
        printf("\n");
        printf("%s > Point %s", WH, RE);
        print_vector3(pl->point);
        printf("\n");
        printf("%s > Normal %s", WH, RE);
        print_vector3(pl->normal);
        printf("\n");
        printf("%s > Color %s", WH, RE);
        print_color(pl->color);
        printf("\n");
        current = current->next;
        i++;
    }
}

void    print_cylinders(cylinder *cy)
{
    cylinder  *current = cy;
    int i = 1;
    printf(" %s____ CYLINDERS ____ %s\n", WH, RE);
    printf("\n");    
    while (current)
    {
        printf("%s %d. %s\n", WH, i, RE);
        printf("\n");
        printf("%s > Center %s", WH, RE);
        print_vector3(cy->center);
        printf("\n");
        printf("%s > Direction %s", WH, RE);
        print_vector3(cy->direction);
        printf("\n");
        printf("%s > Diameter %s", WH, RE);
        printf("%s[%f]%s\n", CY, cy->diameter, RE);
        printf("\n");
        printf("%s > Height %s", WH, RE);
        printf("%s[%f]%s\n", CY, cy->height, RE);
        printf("\n");
        printf("%s > Color %s", WH, RE);
        print_color(cy->color);
        printf("\n");
        current = current->next;
        i++;
    }
}

void    print_scene(scene scene)
{
    print_camera(scene.camera);
    print_ambient_light(scene.ambient);
    print_light(scene.light);
    print_spheres(scene.spheres);
    print_cylinders(scene.cylinders);
}

