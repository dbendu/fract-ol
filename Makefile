NAME =				fractol.a

SRCS =				draw.c		keyboard.c		main.c		mouse.c		opencl.c

FLAGS =				-Wall -Wextra -Werror -Iincludes -I libft/includes -I minilibx
FLAGS_MLX_MAC =		-framework AppKit -framework OpenGL
FLAGS_MLX_LIN =		-lX11 -lXext -lm

OBJS =	$(SRCS:.c=.o)

SYSTEM = $(shell uname -s)

%.o: %.c
ifeq ($(SYSTEM), Darwin)
	$(CC) $(FLAGS) -o $@ -c $<
endif
ifeq ($(SYSTEM), Linux)
	$(CC) $(FLAGS) -o $@ -c $<
endif

$(NAME): $(OBJS)
	make -C libft
	make -C minilibx
ifeq ($(SYSTEM), Darwin)
	$(CC) $(FLAGS) $(FLAGS_MLX_MAC) *.o -o $(NAME) -L minilibx -lmlx -framework OpenCL -L libft -lft
endif
ifeq ($(SYSTEM), Linux)
	$(CC) $(FLAGS) $(FLAGS_MLX_LIN) *.o -o $(NAME) -L minilibx -lmlx -lOpenCL -L libft -lft
endif

all: $(NAME)

clean:
	rm -f *.o
	make c -C libft

fclean: clean
	make f -C libft
	@rm -f $(NAME)

re: fclean all

c: clean

f: fclean
