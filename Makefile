
NAME 	=	mini-rt

CC 	=	gcc

CFLAGS	=	-I./include -I./lib/minilibx #-Wall -Wextra -Werror


SRC 	=	./src/circunferencia.c\
	       	./src/parser.c

OBJ 	= 	$(SRC:.c=.o)


all	:	$(NAME)

$(NAME)	:	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) -L./lib/minilibx -lmlx -lXext -lX11 -lm

%.o	:	%.c
		$(CC) $(CFLAGS) -c $< -o $@

clean	:
		rm -f $(OBJ)

fclean	:	clean
		rm -f $(NAME)

re	:
		fclean all

.PHONY	:	all clean fclean re

