NAME = mini-rt

CC = gcc
CFLAGS = -I./include -I./lib/minilibx #-Wall -Wextra -Werror

SRC_DIR = ./src
OBJ_DIR = ./.obj

SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/parser/parser.c \
      $(SRC_DIR)/parser/conditions.c \
      $(SRC_DIR)/parser/processor.c \
      $(SRC_DIR)/parser/elements.c \
      $(SRC_DIR)/view/window.c \
      $(SRC_DIR)/view/camera.c \
      $(SRC_DIR)/view/scene.c \
      $(SRC_DIR)/models/render.c \
      $(SRC_DIR)/models/sphere.c \
      $(SRC_DIR)/models/plane.c \
      $(SRC_DIR)/models/cylinder.c \
      $(SRC_DIR)/utils/utils.c \
      $(SRC_DIR)/utils/color.c \
      $(SRC_DIR)/vectors/vector2.c \
      $(SRC_DIR)/vectors/vector3.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

MLX = -L./lib/minilibx -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(MLX)


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/parser \
	&& mkdir -p $(OBJ_DIR)/utils \
	&& mkdir -p $(OBJ_DIR)/view \
	&& mkdir -p $(OBJ_DIR)/models \
	&& mkdir -p $(OBJ_DIR)/vectors


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(OBJ_DIR)


fclean: clean
	rm -f $(NAME)


re: fclean all


valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) scenes/1.rt

.PHONY: all clean fclean re valgrind
