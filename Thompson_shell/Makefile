# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/27 14:42:36 by alassiqu          #+#    #+#              #
#    Updated: 2024/04/30 13:12:12 by baouragh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
NAME_B	=	minishell_b

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -fsanitize=address -g3
RM		= rm -f

SRCS	= srcs/builtins/ft_env.c srcs/builtins/ft_echo.c srcs/builtins/ft_cd.c
SRCS	+= srcs/builtins/ft_pwd.c srcs/builtins/ft_exit.c srcs/builtins/ft_unset.c
SRCS	+= srcs/builtins/ft_export.c srcs/env.c srcs/safe_function.c
SRCS	+= srcs/parser/tokenization.c srcs/parser/parse_input.c

SRCS_B	= 
SRCS_B	+=

OBJS	= $(SRCS:.c=.o)
OBJS_B	= $(SRCS_B:.c=.o)

LIB		= 42_libft/libft.a

all:	$(NAME)

$(LIB):
	@make -C 42_libft/ --quiet

$(NAME):	$(OBJS) $(LIB)
	@$(CC) $(CFLAGS) $(OBJS) -lreadline -L42_libft -lft minishell.c -o $(NAME)

bonus:	$(OBJS_B)  $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_B) -o $(NAME_B)

clean:
	$(RM) $(OBJS)
	make -C 42_libft/ clean

clean_bonus:
	$(RM) $(OBJS_B)
	make -C 42_libft/ clean

fclean:	clean
	$(RM) $(NAME)
	make -C 42_libft/ fclean

fclean_bonus: clean_bonus
	$(RM) $(NAME_B)
	make -C 42_libft/ fclean

re:	fclean all

re_bonus: fclean bonus

.PHONY:	all clean clean_bonus fclean fclean_bonus re re_bonus