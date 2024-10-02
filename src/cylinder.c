#include <mlx.h>
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

// Función para dibujar un círculo
void draw_circle(void *img, int x0, int y0, int radius, int color) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                put_pixel(img, x0 + x, y0 + y, color);
            }
        }
    }
}

// Función para rellenar el centro del cilindro (superficie lateral)
void fill_lateral(void *img, int x0, int y0, int radius, int height, int color) {
    for (int x = -radius; x <= radius; x++) {
        for (int y = 0; y <= height; y++) {
            // Pintamos las líneas dentro del rectángulo lateral
            put_pixel(img, x0 + x, y0 + y, color);
        }
    }
}

// Función para dibujar un cilindro en 2D
void draw_cylinder(t_data *data, int x0, int y0, int radius, int height, int color) {
    void *img = mlx_new_image(data->mlx, WIDTH, HEIGHT);

    // Dibujar la tapa inferior (círculo)
     draw_circle(img, x0, y0 + height, radius, color);

    // Dibujar la tapa superior (círculo)
    draw_circle(img, x0, y0, radius, color);

    // // Dibujar el lateral (rectángulo) conectando las dos tapas
    // for (int x = -radius; x <= radius; x++) {
    //     put_pixel(img, x0 + x, y0, color);             // Línea superior
    //     put_pixel(img, x0 + x, y0 + height, color);    // Línea inferior
    // }

    // // Rellenar el centro del cilindro (superficie lateral)
    // fill_lateral(img, x0, y0, radius, height, color);

    // mlx_put_image_to_window(data->mlx, data->win, img, 0, 0);
    // mlx_destroy_image(data->mlx, img);
}

int main() {
    t_data data;
    int x0 = WIDTH / 2;     // Coordenada X del centro del cilindro
    int y0 = HEIGHT / 4;    // Coordenada Y de la tapa superior del cilindro
    int radius = 50;        // Radio del cilindro
    int height = 200;       // Altura del cilindro
    int color = 0x00FFFF;   // Color del cilindro (cyan)

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "2D Cylinder");

    // Dibujar el cilindro en 2D
    draw_cylinder(&data, x0, y0, radius, height, color);

    mlx_loop(data.mlx);
    return 0;
}
