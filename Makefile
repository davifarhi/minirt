# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybentaye <ybentaye@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/11 12:17:38 by dfarhi            #+#    #+#              #
#    Updated: 2022/07/12 14:25:27 by dfarhi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES		=

FILES		:= $(FILES)
FILES		:= $(addprefix src/, ${FILES})
FILES		:= $(addsuffix .c, ${FILES})
OBJS		= ${FILES:.c=.o}

NAME		= minirt

CC			= gcc -Wall -Wextra -Werror

INCLUDES	= -I./includes -I./libft/includes

LIB			= -L./libft/ -lft -lreadline
LIBFT		= libft/libft.a
LIBFT_ARGS	=

SYSTEM		= $(shell uname -s)

${NAME}:	${LIBFT} ${OBJS}
			${CC} ${INCLUDES} -o ${NAME} ${OBJS} ${LIB}

.c.o:
			${CC} -c ${INCLUDES} $< -o ${<:.c=.o}

all:		${NAME}

ifeq ($(SYSTEM), Darwin)
LIB			:= $(LIB) -L $(HOME)/.brew/opt/readline/lib
INCLUDES	:= $(INCLUDES) -I$(HOME)/.brew/opt/readline/include
endif

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

fclean:		clean
			rm -f ${NAME} libft/libft.a

re:			fclean all

.PHONY:		all clean fclean re
