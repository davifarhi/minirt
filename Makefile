# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/11 12:17:38 by dfarhi            #+#    #+#              #
#    Updated: 2022/11/09 10:09:51 by dfarhi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES		= minirt

FILES_D		=	mlx_setup mlx_utils colors_utils render_loop render_camera_ray \
				math_utils render_setup render_sphere render_per_pixel \
				render_plane render_cylinder render_cylinder_utils vector_op1 \
				vector_op2 vector_op3 render_antialiasing time
FILES_M		= 	parsing parsing_setup parsing_tab parsing_volumes errors free \
				display parsing_utils parsing_range render_lights render_shadows \
				lights_combinations lights_utils render_lights_types parsing_lights \
				parsing_volumes_param

FILES		:= $(FILES) $(FILES_D) $(FILES_M)
FILES		:= $(addprefix src/, ${FILES})
FILES		:= $(addsuffix .c, ${FILES})
OBJS		= ${FILES:.c=.o}

NAME		= miniRT

CC			= gcc -Wall -Wextra -Werror

INCLUDES	= -I./includes -I./libft/includes

LIB			= -L./libft/ -lft -lm -pthread
LIBFT		= libft/libft.a
LIBFT_ARGS	=
MINILIBX_V	=
MINILIBX	=

SYSTEM		= $(shell uname -s)

ifeq ($(SYSTEM), Linux)
MINILIBX_V	= minilibx_linux
MINILIBX	= $(MINILIBX_V)/libmlx.a
LIB			:= $(LIB) -L./$(MINILIBX_V) -lmlx -lXext -lX11
else
INCLUDES	:= ${INCLUDES} -D MACOS
MINILIBX_V	= minilibx_macos
MINILIBX	= $(MINILIBX_V)/libmlx.a
LIB			:= $(LIB) -framework OpenGL -framework AppKit -L./$(MINILIBX_V) -lmlx
endif
INCLUDES	:= $(INCLUDES) -I./$(MINILIBX_V)

${NAME}:	${LIBFT} ${OBJS} ${MINILIBX}
			${CC} ${INCLUDES} -o ${NAME} ${OBJS} ${LIB}

.c.o:
			${CC} -c ${INCLUDES} $< -o ${<:.c=.o}

all:		${NAME}

${MINILIBX}:
			$(MAKE) -C ./$(MINILIBX_V)

AddressSanitizer:	CC := ${CC} -fsanitize=address -g
ifeq ($(SYSTEM), Linux)
AddressSanitizer:	CC := ${CC} -static-libasan
endif
AddressSanitizer:	LIBFT_ARGS := ${LIBFT_ARGS} ADDRESS_SANITIZER=1
AddressSanitizer:	${NAME}

# cmd to prof code:
# gprof ${NAME} gmon.out > analysis.txt
profile:	fclean
profile:	CC := ${CC} -pg
profile:	LIBFT_ARGS := ${LIBFT_ARGS} PROFILE=1
profile:	${NAME}

${LIBFT}:
			$(MAKE) -C ./libft expanded get-next-line ${LIBFT_ARGS}

git:
			git submodule update --init --recursive

clean:
			rm -f ${OBJS}
			make -C ./libft clean
			make -C ./$(MINILIBX_V) clean

fclean:		clean
			rm -f ${NAME} libft/libft.a

re:			fclean all

.PHONY:		all clean fclean re
