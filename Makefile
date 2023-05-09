# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 12:23:37 by mdanchev          #+#    #+#              #
#    Updated: 2023/05/09 10:42:31 by mdanchev         ###   lausanne.ch        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c \
			  envp_routine.c \
			  parsing.c \
			  is_token.c \
			  is_operator.c \
			  is_dollar.c \
			  is_quote.c \
			  is_white_space.c \
			  launch_setup.c \
			  handler_ctr_c.c \
			  token_routine.c \
			  parsing_syntax_errors.c\
			  parsing_syntax_errors_print_message.c \
			  parsing_token_extraction.c\
			  malloc_error_print_message.c

OBJS		= ${SRCS:.c=.o}

NAME		= minishell

CC			= gcc

RM			= rm -f

HEADERS		= minishell.h

LIBFT_FOLD	= libft

# DEPS		= ${INC_LIBFT}/includes/libft.h

CFLAGS		+= -Wall -Wextra -Werror

SANITIZE	?= 0

ifeq ($(SANITIZE), 1)
CFLAGS += -g3 -fsanitize=address
CFLAGS += -fno-omit-frame-pointer
endif

CFLAGS		+= -I. -Ilibft/includes
LIBFT		= -L./libft -lft

ifeq ($(USER), margaritamakarova)
CFLAGS		+= -I/opt/homebrew/opt/readline/include
READLINE 	= -L/opt/homebrew/opt/readline/lib -lreadline
else
CFLAGS		+= -I$(HOME)/.brew/opt/readline/include
READLINE	=  -L$(HOME)/.brew/opt/readline/lib -lreadline
endif


.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${HEADERS}
			${MAKE} -C ${LIBFT_FOLD}
			${CC} ${CFLAGS} ${LIBFT} ${READLINE} -o ${NAME} ${OBJS}

all:		${NAME}

clean:
			${RM} ${OBJS}
			${MAKE} -C ${LIBFT_FOLD} clean

fclean:		clean
			${MAKE} -C ${LIBFT_FOLD} fclean
			${RM} ${NAME}

re:			fclean all

.PHONY: all clean fclean re
