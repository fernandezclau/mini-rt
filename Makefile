NAME = mini-rt

CC = gcc
CFLAGS = -I./include -I./lib/minilibx -Wall -Wextra -Werror #-fsanitize=address,undefined

SRC_DIR = ./src
OBJ_DIR = ./.obj

SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/parser/parser.c \
      $(SRC_DIR)/parser/conditions.c \
      $(SRC_DIR)/parser/conditions_2.c \
      $(SRC_DIR)/parser/processor.c \
      $(SRC_DIR)/parser/processor_2.c \
      $(SRC_DIR)/parser/elements.c \
      $(SRC_DIR)/view/window.c \
      $(SRC_DIR)/view/camera.c \
      $(SRC_DIR)/view/scene.c \
      $(SRC_DIR)/intersections/render.c \
      $(SRC_DIR)/intersections/ray.c \
      $(SRC_DIR)/intersections/sphere.c \
      $(SRC_DIR)/intersections/plane.c \
      $(SRC_DIR)/intersections/cylinder.c \
      $(SRC_DIR)/intersections/normal.c \
      $(SRC_DIR)/utils/utils.c \
      $(SRC_DIR)/utils/error.c \
      $(SRC_DIR)/utils/log.c \
      $(SRC_DIR)/utils/cy_calculation.c \
      $(SRC_DIR)/vectors/vector2.c \
      $(SRC_DIR)/vectors/vector3.c \
      $(SRC_DIR)/vectors/vector3_2.c \
      $(SRC_DIR)/vectors/vector3_3.c \
      $(SRC_DIR)/vectors/vector3_4.c \
      $(SRC_DIR)/vectors/color.c \
      $(SRC_DIR)/vectors/color_2.c \
      $(SRC_DIR)/light/light.c \
      $(SRC_DIR)/light/ambient_light.c \
      $(SRC_DIR)/light/spotlight.c \
      ./lib/get_next_line/get_next_line.c \
      ./lib/get_next_line/get_next_line_utils.c \

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

MLX = -L./lib/minilibx -lmlx -lXext -lX11 -lm #-fsanitize=address,undefined

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(MLX)


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/parser \
	&& mkdir -p $(OBJ_DIR)/utils \
	&& mkdir -p $(OBJ_DIR)/view \
	&& mkdir -p $(OBJ_DIR)/intersections \
      && mkdir -p $(OBJ_DIR)/light \
	&& mkdir -p $(OBJ_DIR)/vectors \
      && mkdir -p $(OBJ_DIR)/get_next_line


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(OBJ_DIR)


fclean: clean
	rm -f $(NAME)


re: fclean all


valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) scenes/intersections/intersection.rt 

.PHONY: all clean fclean re valgrind
