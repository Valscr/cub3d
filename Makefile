
NAME = cub3d

C_FILES = main.c get_next_line.c get_next_line_utils.c

SRC_DIR		=	./src/

DIR_OBJ = objs/

OBJS = ${C_FILES:%.c=$(DIR_OBJ)%.o}

CFLAGS += -Wall -Wextra -Werror

MLXFLAGS	= -Lmlx_linux -lmlx_Linux -Imlx_linux -L/usr/lib -lXext -lX11 -lm

LIBSFLAGS	=  libft/libft.a ft_printf/libftprintf.a

CC		= gcc
RM		= rm -f

$(NAME): ${OBJS} maker
		@$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(MLXFLAGS) $(LIBSFLAGS)
		@echo " [ OK ] Cub3d is ready"		

$(DIR_OBJ)%.o : $(SRC_DIR)%.c
		@mkdir -p $(DIR_OBJ)
		@$(CC) $(CFLAGS) $(MLXFLAGS) -c $< -o $@
		@echo " [ OK ] "

all: ${NAME}

maker:
		@chmod +x mlx_linux/configure
		@make -C mlx_linux
		@make -C libft
		@make -C ft_printf

clean:
		@${RM} -rf ${DIR_OBJ}
		@make clean -C libft
		@make clean -C ft_printf

fclean:	clean
		@make clean -C mlx_linux
		@make fclean -C libft
		@make fclean -C ft_printf
		@${RM} ${NAME}

re:		fclean all

norm:
	norminette $(SRC_DIR)*.c includes/so_long.h libft/*.c libft/*.h ft_printf/*.c ft_printf/*.h