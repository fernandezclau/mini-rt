#include <mlx.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct s_data {
    void    *mlx;
    void    *win;
}               t_data;

// Función para dibujar un píxel en la ventana
void put_pixel(void *img, int x, int y, int color) {
    char *img_data = mlx_get_data_addr(img, &(int){0}, &(int){0}, &(int){0});
    int bpp = 32 / 8;  // 4 bytes por píxel
    int line_size = WIDTH * bpp;
    int pixel_position = (y * line_size) + (x * bpp);

    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
        *(unsigned int *)(img_data + pixel_position) = color;
}

// Función para dibujar una línea entre dos puntos (usamos la ecuación de Bresenham para la línea)
void draw_line(void *img, int x0, int y0, int x1, int y1, int color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (1) {
        put_pixel(img, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        int e2 = err * 2;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}

// Función para dibujar la circunferencia de forma continua
void draw_circle(t_data *data, int x0, int y0, int radius, int color) {
    void *img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    
    // Variables para calcular los puntos en el círculo
    int prev_x = x0 + radius;
    int prev_y = y0;

    // Recorrer el círculo y dibujar líneas entre puntos consecutivos
    for (int angle = 1; angle <= 360; angle++) {
        // Convertimos el ángulo a radianes
        float rad = angle * (M_PI / 180.0);
        
        // Calcular el punto correspondiente en la circunferencia
        int x = x0 + radius * cos(rad);
        int y = y0 + radius * sin(rad);

        // Dibujar una línea entre el punto anterior y el actual
        draw_line(img, prev_x, prev_y, x, y, color);

        // Actualizar el punto anterior
        prev_x = x;
        prev_y = y;
    }

    mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
    mlx_destroy_image(data->mlx, img);
}

int main() {
    t_data data;
    int x0 = WIDTH / 2;     // Coordenada X del centro del círculo
    int y0 = HEIGHT / 2;    // Coordenada Y del centro del círculo
    int radius = 100;       // Radio del círculo
    int color = 0xFF0000;   // Color del círculo (rojo)

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "2D Circle");

    // Dibujar la circunferencia
    draw_circle(&data, x0, y0, radius, color);

    mlx_loop(data.mlx);
    return 0;
}
