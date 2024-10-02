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

void draw_circle(t_data *data, int x0, int y0, int radius, int color) {
    void *img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    char *img_data = mlx_get_data_addr(img, &(int){0}, &(int){0}, &(int){0});
    
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            // Ecuación del círculo: x^2 + y^2 <= radius^2
            if (x * x + y * y <= radius * radius) {
                put_pixel(img, x0 + x, y0 + y, color);
            }
        }
    }

    mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
    mlx_destroy_image(data->mlx, img);
}

int main() {
    t_data data;
    int x0 = 0;            // Centro en X
    int y0 = 0;            // Centro en Y
    int radius = 8;        // Radio de la esfera
    int color = 0xD83888;  // Color en formato hexadecimal

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Sphere");

    draw_circle(&data, x0 + 400, y0 + 300, radius, color);

    mlx_loop(data.mlx);
    return 0;
}