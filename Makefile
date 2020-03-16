NAME =				fractol

SRCS =				draw.c		keyboard.c		main.c		mouse.c		opencl.c

MLX_LUNIX_DIR =		mlx/mlx_linux
MLX_MACOS_DIR =		mlx/mlx_macos
FLAGS_LINUX =		-g -Wall -Wextra -Werror -Iincludes -I libft/includes -I $(MLX_LINUX_DIR)
FLAGS_MACOS =		-g -Wall -Wextra -Werror -Iincludes -I libft/includes -I $(MLX_MACOS_DIR)
FLAGS_MLX_MAC =		-framework AppKit -framework OpenGL -framework OpenCL
FLAGS_MLX_LIN =		-lX11 -lXext -lm -lX11 -lXext -lOpenCL
FLAGS_LINUX_LINK =	-L libft -lft -L $(MLX_LINUX_DIR) -lmlx
FLAGS_MACOS_LINK =	-L libft -lft -L $(MLX_MACOS_DIR) -lmlx
FLAGS_MAKE =		--no-print-directory

OBJS =	$(SRCS:.c=.o)

SYSTEM = $(shell uname -s)

%.o: %.c
ifeq ($(SYSTEM), Darwin)
	$(CC) $(FLAGS_MACOS) -o $@ -c $<
endif
ifeq ($(SYSTEM), Linux)
	@$(CC) $(FLAGS_LINUX) -o $@ -c $<
endif

$(NAME): $(OBJS)
	make -C libft $(FLAGS_MAKE)
#compile mlx
ifeq ($(SYSTEM), Darwin)
	make -C $(MLX_MACOS_DIR) $(FLAGS_MAKE)
endif
ifeq ($(SYSTEM), Linux)
	make -C $(MLX_LINUX_DIR) $(FLAGS_MAKE)
endif
#end compile mlx
ifeq ($(SYSTEM), Darwin)
	$(CC) $(FLAGS_MACOS) *.o -o $(NAME) $(FLAGS_MACOS_LINK) $(FLAGS_MLX_MAC)
endif
ifeq ($(SYSTEM), Linux)
	$(CC) $(FLAGS_LINUX) *.o -o $(NAME) $(FLAGS_LINUX_LINK) $(FLAGS_MLX_LIN)
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
