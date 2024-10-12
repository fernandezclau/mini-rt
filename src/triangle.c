#include "../../include/minirt.h"

void swap_points(vector2 *p1, vector2 *p2)
{
    vector2 tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}


void draw_horizontal_line(t_data *data, int x_start, int x_end, int y, int color)
{
    if (x_start > x_end)
    {
        int tmp = x_start;
        x_start = x_end;
        x_end = tmp;
    }
    for (int x = x_start; x <= x_end; x++)
    {
        my_mlx_pixel_put(data, x, y, color);
    }
}

// Función para dibujar un triángulo relleno
void fill_triangle(t_data *data, vector2 *a, vector2 *b, vector2 *c, int color)
{
    // Ordenar los vértices por su coordenada Y (a->y <= b->y <= c->y)
    if (a->y > b->y) swap_points(a, b);
    if (b->y > c->y) swap_points(b, c);
    if (a->y > b->y) swap_points(a, b);

    // Dibujar desde la parte superior a la inferior del triángulo
    float invslope1 = (float)(b->x - a->x) / (b->y - a->y); // Pendiente inversa de la primera mitad
    float invslope2 = (float)(c->x - a->x) / (c->y - a->y); // Pendiente inversa de la segunda mitad
    float curx1 = a->x;
    float curx2 = a->x;

    // Dibujar la primera parte del triángulo (desde a->y hasta b->y)
    for (int y = a->y; y <= b->y; y++)
    {
        draw_horizontal_line(data, curx1, curx2, y, color);
        curx1 += invslope1;
        curx2 += invslope2;
    }

    // Dibujar la segunda parte del triángulo (desde b->y hasta c->y)
    invslope1 = (float)(c->x - b->x) / (c->y - b->y); // Recalcular pendiente inversa
    curx1 = b->x;
    for (int y = b->y; y <= c->y; y++)
    {
        draw_horizontal_line(data, curx1, curx2, y, color);
        curx1 += invslope1;
        curx2 += invslope2;
    }
}