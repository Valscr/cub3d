# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: valentin <valentin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 13:32:44 by valentin          #+#    #+#              #
#    Updated: 2023/06/01 19:01:04 by valentin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

C_FILES = main.c get_next_line.c get_next_line_utils.c utils.c ft_split2.c calculate_point.c \
			calculate_point_bis.c intersection.c intersection_bis.c check_wall.c free_error.c \
			key_hook.c parse_map.c parse_texture_color.c parse_xpm.c render.c init.c \
			render_rect.c check_map.c copy_map.c key_hook_bis.c

SRC_DIR		=	./src/

DIR_OBJ = objs/

OBJS = ${C_FILES:%.c=$(DIR_OBJ)%.o}

CFLAGS += -Wall -Wextra -Werror

MLXFLAGS	= -Lmlx_linux -lmlx_Linux -Imlx_linux -L/usr/lib -lXext -lX11 -lm

LIBSFLAGS	=  libft/libft.a

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

clean:
		@${RM} -rf ${DIR_OBJ}
		@make clean -C libft

fclean:	clean
		@make clean -C mlx_linux
		@make fclean -C libft
		@${RM} ${NAME}

re:		fclean all

norm:
	norminette $(SRC_DIR)*.c includes/cub3d.h libft/*.c libft/*.h