# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 12:23:37 by mdanchev          #+#    #+#              #
#    Updated: 2023/05/20 15:58:41 by mmakarov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c \
			  envp_routine.c \
			  is_token.c \
			  is_operator.c \
			  is_dollar.c \
			  is_quote.c \
			  is_white_space.c \
			  is_question.c \
			  launch_setup.c \
			  handler_ctr_c.c \
			  token_routine.c \
			  token_routine_set_id.c \
			  token_routine_delete.c \
			  parsing.c \
			  parsing_syntax_errors.c\
			  parsing_syntax_errors_print_message.c \
			  parsing_token_extraction.c\
			  parsing_expansion.c \
			  parsing_expansion_helper.c \
			  parsing_expansion_dollar_conditions.c \
			  parsing_expansion_expand_var_helper.c \
			  parsing_expansion_looping.c \
			  parsing_expansion_trim_dollar.c \
			  parsing_expansion_join_tokens.c \
			  parsing_quote_removing.c \
			  malloc_error_print_message.c\
			  builtins.c\
			  copy_env_tab.c\


OBJS		= ${SRCS:.c=.o}

NAME		= minishell

CC			= gcc

RM			= rm -f

HEADERS		= minishell.h

LIBFT_FOLD	= libft

# DEPS		= ${INC_LIBFT}/includes/libft.h

CFLAGS		+= -Wall -Wextra -Werror

SANITIZE	?= 0

## DE MARIYA
# J'AI AJOUTE UN VARIABLE SANITIZE
# SI TU FAIT LE MAKE AVEC LA COMMANDE: "make SANITIZE=1"
# LA COMPILATION S'EFFECTUERA AVEC LE FLAG "-fsanitize=address"
# SINON, CE SERA SANS LE FLAG ET ON POURRAIT UTILISER LEAKS AT EXIT
ifeq ($(SANITIZE), 1)
CFLAGS += -g3 -fsanitize=address
CFLAGS += -fno-omit-frame-pointer
endif

CFLAGS		+= -I. -Ilibft/includes
LIBFT		= -L./libft -lft

# ifeq ($(USER), margaritamakarova)
# CFLAGS		+= -I/opt/homebrew/opt/readline/include
# READLINE 	= -L/opt/homebrew/opt/readline/lib -lreadline
ifeq ($(USER), mariyadancheva)
CFLAGS		+= -I/opt/homebrew/Cellar/readline/8.2.1/include
READLINE	= -L/opt/homebrew/Cellar/readline/8.2.1/lib -lreadline
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
