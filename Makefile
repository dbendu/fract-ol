NAME =				fractol

SRCS =				main.c				\
					draw.c				\
					mouse.c				\
					opencl.c			\
					keyboard.c			\
					init_data.c			\
					quit.c				\
					reset_fractol.c

SRCS_DIR =			srcs

OBJS_DIR =			objs

INCLUDES_DIRS =		includes			\
					libft/includes

INCLUDES =			$(addprefix -I, $(INCLUDES_DIRS))

OBJS =				$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

FLAGS =				-Wall -Werror -Wextra -g
LINK_FLAGS =		-L libft -lft -lOpenCL -lSDL2


all: $(NAME)


$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@gcc $(FLAGS) $(INCLUDES) -o $@ -c $<

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS_DIR) $(OBJS)
	@make -C libft
	@gcc $(FLAGS) $(OBJS) $(LINK_FLAGS) -o $(NAME)


clean:
	@rm -rf $(OBJS_DIR)
	@make clean -C libft

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all

c: clean

f: fclean

.PHONY: all clean fclean re c f
