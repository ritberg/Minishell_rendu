# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 12:23:37 by mdanchev          #+#    #+#              #
#    Updated: 2023/05/08 18:52:15 by mdanchev         ###   lausanne.ch        #
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

INC_LIBFT	= libft

DEPS		= ${INC_LIBFT}/includes/libft.h

CFLAGS		+= -Wall -Wextra -Werror -I.
# -g3 -fsanitize=address 


LIBFT		= -Llibft -lft

ifeq ($(USER), margaritamakarova)
READLINE 	= -L/opt/homebrew/opt/readline/lib -lreadline
CFLAGS		+= -I/opt/homebrew/opt/readline/include
else
READLINE	=  -L$(HOME)/.brew/opt/readline/lib -lreadline
CFLAGS		+= -I$(HOME)/.brew/opt/readline/include
endif


.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${HEADERS}
			${MAKE} -C ${INC_LIBFT}
			${CC} ${CFLAGS}  ${LIBFT} -o ${NAME} ${OBJS} ${READLINE}

all:		${NAME}

clean:
			${RM} ${OBJS}
			${RM}
			${MAKE} -C ${INC_LIBFT} clean

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY: all clean fclean re
