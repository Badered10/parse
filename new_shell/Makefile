# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/04 14:32:39 by alassiqu          #+#    #+#              #
#    Updated: 2024/05/12 09:39:20 by alassiqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= minishell

LIBFT_PATH		:= libft/
LIBFT			:= libft/libft.a
READLINE		:= /Users/alassiqu/readline/lib

CC				:= cc
CFLAGS			:= -Wall -Werror -Wextra #-fsanitize=address -g3
RM				:= rm -f

# BUILTINS		:=	builtins/ft_cd.c			\
# 					builtins/ft_echo.c 			\
# 					builtins/ft_env_utils.c 	\
# 					builtins/ft_env.c 			\
# 					builtins/ft_exit.c 			\
# 					builtins/ft_export.c 		\
# 					builtins/ft_pwd.c 			\
# 					builtins/ft_unset.c

ENVIRONMENT		:=	environment/env_utils.c		\
					environment/free.c

# PARSING			:= 

SIGNALS			:=	signals/handle_signals.c

CLEAN			:=	clean/clean.c

TOKENIZATION	:=	tokenization/tokenizer.c			\
					tokenization/tokenizer_utils.c		\
					tokenization/tokenizer_helpers.c	\
					tokenization/tokenizer_free.c

SRCS			:=	$(BUILTINS)		\
					$(ENVIRONMENT)	\
					$(TOKENIZATION)	\
					$(SIGNALS)		\
					$(CLEAN)		\
					minishell.c

OBJS			:=	$(SRCS:.c=.o)

all:	$(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_PATH) -lft -lreadline -L $(READLINE) -o $(NAME) 

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)

re: fclean all

.PHONY: clean