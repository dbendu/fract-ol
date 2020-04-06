NAME =				fractol

SRCS =				main.c				\
					draw.c				\
					mouse.c				\
					opencl.c			\
					keyboard.c

SRCS_DIR =			srcs

OBJS_DIR =			objs

INCLUDES_DIRS =		includes			\
					libft/includes		\
					mlx/mlx_linux

INCLUDES =			$(addprefix -I, $(INCLUDES_DIRS))

OBJS =				$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

FLAGS =				-Wall -Werror -Wextra -O2 -Wno-unused-result
LINK_FLAGS =		-L libft -lft -L mlx/mlx_linux -lmlx -lOpenCL
MLX_FLAGS =			-lX11 -lXext


all: $(NAME)


$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@gcc $(FLAGS) $(INCLUDES) -o $@ -c $<

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS_DIR) $(OBJS)
	@make -C libft
	@make -C mlx/mlx_linux
	@gcc $(FLAGS) $(OBJS) $(LINK_FLAGS) $(MLX_FLAGS) -o $(NAME)


clean:
	@rm -rf $(OBJS_DIR)
	@make clean -C libft
	@make clean -C mlx/mlx_linux

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all

c: clean

f: fclean

.PHONY: all clean fclean re c f

d:
	gcc srcs/*.c $(INCLUDES) -ggdb -g3 -pg -O0 -I libft/includes -I mlx/mlx_linux -I includes libft/libft.a mlx/mlx_linux/libmlx.a -lX11 -lXext -lOpenCL
