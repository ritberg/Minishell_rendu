# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdanchev <mdanchev@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/08 12:23:37 by mdanchev          #+#    #+#              #
#    Updated: 2023/05/24 14:11:44 by mdanchev         ###   lausanne.ch        #
#                                                                              #
# **************************************************************************** #
GREEN 		= \033[32;6m
MAGNE   	= \033[35;1m
COLOR_END 	= \033[0m
RED 		:= $(shell tput setaf 1)
MAGNETA		:= $(shell tput setaf 5)
YELLOW		:= $(shell tput setaf 3)
RESET		:= $(shell tput sgr0)

SRCS		= main.c \
			  malloc_error_print_message.c\
			  global_variable/init_global.c \
			  environnement/envp_routine.c \
			  is_smth/is_token.c \
			  is_smth/is_operator.c \
			  is_smth/is_dollar.c \
			  is_smth/is_quote.c \
			  is_smth/is_white_space.c \
			  is_smth/is_question.c \
			  is_smth/is_numeric.c \
			  launch_setup.c \
			  handler_ctr_c.c \
			  tokens/token_routine.c \
			  tokens/token_routine_set_id.c \
			  tokens/token_routine_delete.c \
			  parsing/parsing.c \
			  parsing/syntax_errors.c\
			  parsing/syntax_errors_print_message.c \
			  parsing/token_extraction.c\
			  parsing/expansion.c \
			  parsing/expansion_helper.c \
			  parsing/expansion_dollar_conditions.c \
			  parsing/expansion_expand_var_helper.c \
			  parsing/expansion_looping.c \
			  parsing/expansion_trim_dollar.c \
			  parsing/expansion_join_tokens.c \
			  parsing/quote_removing.c \
			  command_struct/init_cmd.c \
			  command_struct/init_cmd_cmd.c \
			  command_struct/init_cmd_cmd_helper.c \
			  command_struct/init_cmd_redir.c \
			  command_struct/free_cmd.c \
			  execution_utils.c \
			  execution.c \
			  exit.c \
			  env.c \
			  echo.c \
			  pwd.c \
			  cd.c \
			  cd_helper.c \
			  cmd_is_bin.c \
			  cmd_is_builtin.c \
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

ifeq ($(SANITIZE), 1)
@ CFLAGS += -g3 -fsanitize=address
@ CFLAGS += -fno-omit-frame-pointer
$(info $(YELLOW) fsanitize active$(RESET))
else
$(info $(MAGNETA) NO SANITIZER$(RESET))
endif

CFLAGS		+= -I. -Ilibft/includes
LIBFT		= -L./libft -lft

ifeq ($(USER), margaritamakarova)
CFLAGS		+= -I/opt/homebrew/opt/readline/include
READLINE 	= -L/opt/homebrew/opt/readline/lib -lreadline
else ifeq ($(USER), mariyadancheva)
CFLAGS		+= -I/opt/homebrew/Cellar/readline/8.2.1/include
READLINE	= -L/opt/homebrew/Cellar/readline/8.2.1/lib -lreadline
else
CFLAGS		+= -I$(HOME)/.brew/opt/readline/include
READLINE	=  -L$(HOME)/.brew/opt/readline/lib -lreadline
endif



.c.o:
	@ ${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${HEADERS}
	@		${MAKE} -C ${LIBFT_FOLD}
	@ 		${CC} ${CFLAGS} ${LIBFT} ${READLINE} -o ${NAME} ${OBJS}
	@echo	"${YELLOW} Compilation ${NAME} done ${RESET}"

all:		${NAME}

clean:
	@		${RM} ${OBJS}
	@		${MAKE} -C ${LIBFT_FOLD} clean
	@echo	"${GREEN} Clean object files done ${COLOR_END}"

fclean:		clean
	@		${MAKE} -C ${LIBFT_FOLD} fclean
	@		${RM} ${NAME}
	
	@echo "${GREEN} Clean ${NAME} done ${COLOR_END}"

re:			fclean all

.PHONY: all clean fclean re
