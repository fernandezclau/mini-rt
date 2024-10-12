#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "./minirt.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->image_data + (y * data->size_line + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

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

int main(void)
{
    t_data  data;

    // Inicializar MiniLibX
    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, W_TITLE);
    data.image_ptr = mlx_new_image(data.mlx_ptr, W_WIDTH, W_HEIGHT);
    data.image_data = mlx_get_data_addr(data.image_ptr, &data.bpp, &data.size_line, &data.endian);

    // Triángulo 1: cubrirá la mitad izquierda
    vector2 a = {0.0f, 0.0f};       // Esquina superior izquierda
    vector2 b = {W_WIDTH, 0.0f};    // Esquina superior derecha
    vector2 c = {0.0f, W_HEIGHT};   // Esquina inferior izquierda
    fill_triangle(&data, &a, &b, &c, 0x00FF00); // Verde

    // Triángulo 2: cubrirá la mitad derecha
    // vector2 d = {W_WIDTH, 0.0f};     // Esquina superior derecha
    // vector2 e = {W_WIDTH, W_HEIGHT}; // Esquina inferior derecha
    // vector2 f = {0.0f, W_HEIGHT};    // Esquina inferior izquierda
    //fill_triangle(&data, &d, &e, &f, 0x00FF00);
    
    // Mostrar la imagen
    mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.image_ptr, 0, 0);
    mlx_loop(data.mlx_ptr);

    return 0;
}
