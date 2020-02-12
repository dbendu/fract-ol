all:
	gcc -g -Wall -Werror -Wextra *.c -I . -I libft/includes -I minilibx_macos -L libft -lft -L minilibx_macos -lmlx -framework OpenGL -framework AppKit -framework OpenCL

#gcc -Wall -Werror -Wextra *.c -I . -I libft/includes -I minilibx_macos -L libft -lft -L minilibx_macos -lmlx -lX11 -lXext -lm