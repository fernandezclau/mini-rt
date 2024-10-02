// include/minirt.h

#ifndef MINIRT_H
#define MINIRT_H

#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct s_vector {
    float x;
    float y;
    float z;
} t_vector;

typedef struct s_ambient {
    float ratio; // Ratio de luz ambiental
    int color[3]; // Color de la luz ambiental
} t_ambient;

typedef struct s_light {
    t_vector position; // Posición de la luz
    float brightness; // Brillo de la luz
    int color[3]; // Color de la luz
} t_light;

typedef struct s_camera {
    t_vector position; // Posición de la cámara
    t_vector direction; // Dirección de la cámara
    float fov; // Campo de visión
} t_camera;

typedef struct s_sphere {
    t_vector center; // Centro de la esfera
    float diameter; // Diámetro de la esfera
    int color[3]; // Color de la esfera
} t_sphere;

typedef struct s_data {
    void *mlx_ptr;         // Puntero a la estructura de miniLibX
    void *win_ptr;         // Puntero a la ventana de miniLibX
    void *image_ptr;       // Puntero a la imagen de miniLibX
    int *image_data;       // Puntero a los datos de la imagen
    int bpp;               // Bits por pixel
    int size_line;         // Tamaño de la línea
    int endian;            // Endian
    t_ambient ambient;     // Luz ambiental
    t_light light;         // Luz
    t_camera camera;       // Cámara
    t_sphere sphere;       // Esfera (puedes agregar más elementos según lo necesites)
} t_data;

// Prototipos de funciones
int parse_ambient(char **tokens, t_data *data);
int parse_camera(char **tokens, t_data *data);
int parse_light(char **tokens, t_data *data);
void parse_file(const char *filename, t_data *data);

#endif // MINIRT_H

