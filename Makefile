# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nwyseur <nwyseur@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 21:18:35 by nwyseur           #+#    #+#              #
#    Updated: 2023/02/15 17:05:04 by nwyseur          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= pipex
NAME_BONUS	:= 

SRCS_FILES	:= main.c \
				error_management.c \
				free_management.c \

BONUS_FILES	:=

HEADER_FILE_BONUS := 

HEADER_FILE	:= pipex.h

SRCS_DIR	:= ./srcs/
INC_DIR		:= ./includes/

BONUS_DIR	:= 

LIBFT		:= ./libft/libft.a
LIBFT_PATH	:= ./libft

SRCS		:= $(addprefix ${SRCS_DIR}, ${SRCS_FILES})
OBJS		:= ${SRCS:.c=.o}
HEADER		:= $(addprefix ${INC_DIR}, ${HEADER_FILE})

BONUS_SRCS	:= $(addprefix ${BONUS_DIR}, ${BONUS_FILES})
BONUS_OBJS	:= ${BONUS_SRCS:.c=.o}
BONUS_HEADER := $(addprefix ${INC_DIR}, ${HEADER_FILE_BONUS})

CC			:= cc
CC_FLAGS	:= -Wall -Wextra -Werror -g3

RM			:= rm -f

%.o : %.c	${HEADER}
			${CC} ${CC_FLAGS} -I${INC_DIR} -c $< -o $@

all:		${NAME}

${NAME}:	${OBJS} ${LIBFT}
			${CC} ${CC_FLAGS} -I${INC_DIR} -o ${NAME} ${OBJS} ${LIBFT}

${NAME_BONUS}: ${BONUS_OBJS} ${LIBFT}
				${CC} ${CC_FLAGS} -I${INC_DIR} -o ${NAME_BONUS} ${BONUS_OBJS} ${LIBFT}

${LIBFT}:	
			make -C ${LIBFT_PATH}

bonus:		${NAME_BONUS}

clean:
			make -C ${LIBFT_PATH} clean
			${RM} ${OBJS} ${BONUS_OBJS}

fclean:		clean
			make -C ${LIBFT_PATH} fclean
			${RM} ${NAME} ${NAME_BONUS}

re:			fclean all

.PHONY: 	all clean fclean re bonus