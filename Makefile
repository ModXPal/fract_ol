SRCS		=	./srcs/julia.c \
			./srcs/mandelbrot.c \
			./srcs/zoom.c \
			./srcs/utils.c \
			./srcs/main.c \
			./srcs/utils2.c

OBJS		=	$(SRCS:.c=.o)

UNAME		:=	$(shell uname)

NAME		=	fract_ol

CC		=	clang	

CFLAGS		=	-Wall -Wextra -Werror -Iincludes -g

ifeq ($(UNAME), Darwin)
LIB		=	-Lmlx -lmlx -framework OpenGL -framework AppKit
MLX_PATH	=	./mlx/
else
LIB		=	-Lmlx_linux -lmlx -Imlx_linux -lX11 -lXext -lm
MLX_PATH	=	./mlx_linux/
endif

RM		=	rm -rf

MLX_MAKE	=	@$(MAKE) -C $(MLX_PATH)

all:		$(NAME)

mlx_make:
		@$(MLX_MAKE)

%.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@

ifeq ($(UNAME), Darwin)
$(NAME):	$(OBJS) mlx_make
			@$(CC) $(LIB) $(OBJS) -o $(NAME)
			@echo "$(NAME) created"
else
$(NAME):	$(OBJS) mlx_make
			@$(CC) $(OBJS) $(LIB) -o $(NAME)
			@echo "$(NAME) created"
endif

clean:
			$(MAKE) -C $(MLX_PATH) clean
			@$(RM) $(OBJS)
			@echo ".o deleted"

fclean:		clean
			$(MAKE) -C $(MLX_PATH) clean
			@$(RM) $(NAME)
			@echo "$(NAME) deleted"

re:			fclean all

.PHONY:		all clean flcean re
