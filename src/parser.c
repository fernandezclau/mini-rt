// src/parser.c
#include "minirt.h"
#include <stdio.h>

int parse_ambient(char **tokens, t_data *data) {
    if (tokens[1] && tokens[2]) {
        data->ambient.ratio = atof(tokens[1]);
        sscanf(tokens[2], "%d,%d,%d", &data->ambient.color[0], &data->ambient.color[1], &data->ambient.color[2]);
        return 0; // Éxito
    }
    return -1; // Error
}

int parse_camera(char **tokens, t_data *data) {
    if (tokens[1] && tokens[2] && tokens[3]) {
        sscanf(tokens[1], "%f,%f,%f", &data->camera.position.x, &data->camera.position.y, &data->camera.position.z);
        sscanf(tokens[2], "%f,%f,%f", &data->camera.direction.x, &data->camera.direction.y, &data->camera.direction.z);
        data->camera.fov = atof(tokens[3]);
        return 0; // Éxito
    }
    return -1; // Error
}

int parse_light(char **tokens, t_data *data) {
    if (tokens[1] && tokens[2] && tokens[3]) {
        sscanf(tokens[1], "%f,%f,%f", &data->light.position.x, &data->light.position.y, &data->light.position.z);
        data->light.brightness = atof(tokens[2]);
        sscanf(tokens[3], "%d,%d,%d", &data->light.color[0], &data->light.color[1], &data->light.color[2]);
        return 0; // Éxito
    }
    return -1; // Error
}

// Función principal para procesar el archivo
void parse_file(const char *filename, t_data *data) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error abriendo el archivo");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *tokens[10]; // Para almacenar las palabras de la línea
        int token_count = 0;

        // Dividir la línea en tokens
        char *token = strtok(line, " \t\n");
        while (token) {
            tokens[token_count++] = token;
            token = strtok(NULL, " \t\n");
        }

        // Analizar los diferentes tipos de elementos
        if (tokens[0][0] == 'A') {
            parse_ambient(tokens, data);
        } else if (tokens[0][0] == 'c') {
            parse_camera(tokens, data);
        } else if (tokens[0][0] == 'l') {
            parse_light(tokens, data);
        } else if (tokens[0][0] == 's') { // Esfera
            // Aquí puedes implementar la función para parsear una esfera
        } // Agrega más condiciones para otros elementos como planos, cilindros, etc.
    }

    fclose(file);
}

