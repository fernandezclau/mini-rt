#ifndef MACROS_H
# define MACROS_H

// windows sizing
# define W_WIDTH    800
# define W_HEIGHT   600
# define REFLECT_RATIO  0.0
# define INTENSITY_RATIO   0.8

// PROJECT TITLE
# define W_TITLE    "mini-rt .-."

// KEYS
#ifdef __APPLE__
# define ESC_KEY	53
#define A_KEY	0
#define W_KEY	13
#define S_KEY	1
#define D_KEY	2
#elif __linux__
#define ESC_KEY	65307
#define A_KEY	97
#define W_KEY	119
#define S_KEY	115
#define D_KEY	100
#endif

// FILE FIELDS
# define AMBIENT_LIGHT   'A'
# define CAMERA          'C'
# define LIGHT           'L'
# define SPHERE          "sp"
# define PLANE           "pl"
# define CYLINDER        "cy"

// VECTOR 3
# define NORMALIZED     1
# define NOT_NORMALIZED 0

// MATH 
# define M_PI 3.14159265358979323846
# define EPSILON 0.0001
# define FLT_MAX 340282346638528859811704183484516925440.000000

// COLORS
# define RE      "\033[0m"
# define YE      "\033[1;33m"
# define WH      "\033[1;37m"
# define CY      "\033[1;36m"
# define MA      "\033[1;35m"
# define PIN     "\033[1;38;2;255;209;220m"
# define RED     "\033[1;31m"
# define GR      "\033[1;32m"
# define BL      "\033[1;29m"

// SUCCESS
# define LOADED_SCENE "\n\t\tSCENE HAS BEEN LOADED! :)\n\n"
// ERRORS
# define ERROR "\033[1;31mError\033[1;37m"
# define E_USAGE "Usage: ./mini-rt <file.rt>"
# define E_VIEW "[VIEW]"
# define E_CAMERA "[CAMARA]"
# define E_AMBIENT_LIGHT "[AMBIENT LIGHT]"
# define E_LIGHT "[LIGHT]"
# define E_SPHERE "[SPHERES]"
# define E_PLANE "[PLANE]"
# define E_CYLINDER "[CYLINDER]"
# define E_EXTENSION "The extension file is not correct. It must be '.rt'"

#endif
