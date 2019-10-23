# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hvromman <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/19 11:36:12 by hvromman          #+#    #+#              #
#    Updated: 2019/04/02 16:33:49 by nsondag          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = srcs/
HEAD = includes/
LIB = libft/
FILE = minishell.h
H = $(addprefix $(HEAD), $(FILE))

FILES = error.o exit.o main.o reader.o term_util.o signal.o command_handler.o util.o
OBJ = $(addprefix $(SRCS), $(FILES))

BUILTIN_DIR = builtin/
BUILTIN = builtin_dispatcher.o cd_builtin.o echo_builtin.o env_builtin.o \
exit_builtin.o pwd_builtin.o setenv_builtin.o unsetenv_builtin.o
OBJ += $(addprefix $(SRCS), $(addprefix $(BUILTIN_DIR), $(BUILTIN)))

ENV_DIR = env/
ENV = get_env.o set_env.o
OBJ += $(addprefix $(SRCS), $(addprefix $(ENV_DIR), $(ENV)))

HIST_DIR = history/
HIST = get_history.o set_history.o
OBJ += $(addprefix $(SRCS), $(addprefix $(HIST_DIR), $(HIST)))

SANITIZE = -fsanitize=address

RED=\033[0;91m
GREEN=\033[0;92m
CYAN=\033[0;96m
NC=\033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB)
	@$(CC) $(CFLAGS) -o $@ $^ -L$(LIB) -lft
	@echo "$(GREEN)$(NAME) compiled$(NC)"

%.o: %.c $(H)
	@$(CC) $(CFLAGS) -c -o $@ $< -I $(HEAD) -I $(LIB)$(HEAD)

clean:
	@make -C $(LIB) clean
	@rm -f $(OBJ)
	@echo "$(RED)$(NAME) cleaned$(NC)"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB) fclean
	@echo "$(RED)$(NAME) fcleaned$(NC)"

debug: $(OBJ)
	@make -C $(LIB)
	@$(CC) $(CFLAGS) -o $@ $^ -L$(LIB) -lft $(SANITIZE)
	@echo "$(GREEN)$(NAME) compiled$(NC)"

re: fclean all
