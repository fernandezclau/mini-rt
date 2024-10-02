#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600
#define PI 3.14159265358979323846

typedef struct s_data {
    void *mlx;
    void *win;
} t_data;

void put_pixel(void *img, int x, int y, int color) {
    char *img_data = mlx_get_data_addr(img, &(int){0}, &(int){0}, &(int){0});
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        *(unsigned int *)(img_data + (y * WIDTH * 4 + x * 4)) = color; // 32 bits por píxel
    }
}

void draw_sphere(t_data *data, int x0, int y0, int radius) {
    void *img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    char *img_data = mlx_get_data_addr(img, &(int){0}, &(int){0}, &(int){0});
    
    // Itera sobre el ángulo theta (latitud)
    for (double theta = 0; theta < PI; theta += 0.05) {  // 0.05 radianes
        // Itera sobre el ángulo phi (longitud)
        for (double phi = 0; phi < 2 * PI; phi += 0.05) {  // 0.05 radianes
            int x = x0 + radius * sin(theta) * cos(phi);  // Proyección en X
            int y = y0 + radius * sin(theta) * sin(phi);  // Proyección en Y

            // Proyecta a 2D
            put_pixel(img, x, y, 0xFF0000);  // Color rojo
        }
    }

    // Coloca la imagen en la ventana
    mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
    mlx_destroy_image(data->mlx, img);
}

void draw_scene(t_data *data) {
    // Fondo blanco
    void *img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    char *img_data = mlx_get_data_addr(img, &(int){0}, &(int){0}, &(int){0});

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            put_pixel(img, x, y, 0xFFFFFF);
        }
    }
    
    mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
    mlx_destroy_image(data->mlx, img);

    // Dibuja una esfera en el centro
    draw_sphere(data, 400, 300, 100); // Esfera roja en el centro
}

int main() {
    t_data data;
    // Inicialización de MiniLibX
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Renderizando Esfera 3D");

    draw_scene(&data);

    mlx_loop(data.mlx);
    return 0;
}

