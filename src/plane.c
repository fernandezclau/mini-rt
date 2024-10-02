#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct s_data {
    void *mlx;
    void *win;
} t_data;

void put_pixel(void *img, int x, int y, int color) {
    char *img_data = mlx_get_data_addr(img, &(int){0}, &(int){0}, &(int){0});
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        *(unsigned int *)(img_data + (y * WIDTH * 4 + x * 4)) = color; // Asumiendo 32 bits por píxel
    }
}
void draw_plane(t_data *data, int z0, int width, int height, int color, int d) {
    void *img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    char *img_data = mlx_get_data_addr(img, &(int){0}, &(int){0}, &(int){0});
    
    for (int y = -height; y <= height; y++) {
        for (int x = -width; x <= width; x++) {            
            put_pixel(img, x + WIDTH / 2, y + HEIGHT / 2, color);
        }
    }

    mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
    mlx_destroy_image(data->mlx, img);
}

int main() {
    t_data data;
    int z0 = 10;           // Altura del plano en Z
    int width = 100;       // Ancho del plano (en unidades 3D)
    int height = 100;      // Altura del plano (en unidades 3D)
    int color = 0x00FF00;  // Color del plano (verde)
    int d = 100;           // Distancia focal

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "3D Plane");

    // Dibujar el plano en 3D proyectado a 2D
    draw_plane(&data, z0, width, height, color, d);

    mlx_loop(data.mlx);
    return 0;
}
