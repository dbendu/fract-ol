NAME =				fractol

SRCS =				draw.c		keyboard.c		main.c		mouse.c		opencl.c

FLAGS =				-g -Wall -Wextra -Werror -Iincludes -I libft/includes -I $(MLX_DIR)
FLAGS_MLX_MAC =		-framework AppKit -framework OpenGL -framework OpenCL
FLAGS_MLX_LIN =		-lX11 -lXext -lm -lX11 -lXext -lOpenCL
FLAGS_MAKE =		--no-print-directory
MLX_DIR =			mlx/mlx_linux
FLAGS_LINK =		-L libft -lft -L $(MLX_DIR) -lmlx

OBJS =	$(SRCS:.c=.o)

SYSTEM = $(shell uname -s)

%.o: %.c
ifeq ($(SYSTEM), Darwin)
	$(CC) $(FLAGS) -o $@ -c $<
endif
ifeq ($(SYSTEM), Linux)
	@$(CC) $(FLAGS) -o $@ -c $<
endif

$(NAME): $(OBJS)
	make -C libft $(FLAGS_MAKE)
	make -C $(MLX_DIR) $(FLAGS_MAKE)
ifeq ($(SYSTEM), Darwin)
	$(CC) $(FLAGS) *.o -o $(NAME) $(FLAGS_LINK) $(FLAGS_MLX_MAC)
endif
ifeq ($(SYSTEM), Linux)
	$(CC) $(FLAGS) *.o -o $(NAME) $(FLAGS_LINK) $(FLAGS_MLX_LIN)
endif

all: $(NAME)

clean:
	@rm -f *.o
	@make c -C libft $(FLAGS_MAKE)

fclean: clean
	@make f -C libft $(FLAGS_MAKE)
	@rm -f $(NAME)

re: fclean all

c: clean

f: fclean
