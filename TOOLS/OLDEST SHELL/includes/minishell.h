/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:02:39 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/11 15:42:49 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../42_libft/libft.h"
# include "builtins.h"
# include "parsing.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define RED "\033[1;31m"
# define ORANGE "\033[1;33m"
# define RESET "\033[0m"

# define LEFT 0
# define RIGHT 1


typedef struct t_tree
{
    void *data;
    struct t_tree *right;
    struct t_tree *left;
}           t_tree;

typedef char CHAR_VALUE; // char

typedef enum e_node // enum define two types of nodes.
{
	PAIR_NODE,
	CHAR_NODE
}			e_node_type;

typedef struct s_node // strcut define a node
{
	e_node_type type;
	CHAR_VALUE value;
}				t_node;

typedef struct s_pair_value
{
	t_node left;
	t_node right;
}				t_pair_value;

typedef union u_node_value 
{
	t_pair_value pair;
	CHAR_VALUE value;
}				u_node_value;



typedef enum e_type
{
	WHITE_SPACE,
	WORD,
	NUMERIC,
	REDIR_L,
	REDIR_R,
	REDIR_LL,
	REDIR_RR,
	PIPE,
	QUOTE_S,
	QUOTE_D,
	OTHER
}			t_type;

typedef struct s_token
{
	char	*str;
	int		type;
}			t_token;

typedef struct s_env
{
	char	*var;
	char	*value;
}			t_env;

typedef struct s_mini
{
	t_env	**our_env;
	char	*input;
	t_token	*tokens;
}			t_mini;

// Function to protect the malloc.
void		*safe_malloc(size_t size, void **data, int i);

// Function that duplicate the env.
t_env		**dup_env(char **env);

// Function that set a special variable of the environment.
void		set_env_var(t_env **env, char *var, char *new);

// Function that get a special variable value from the environment.
char		*get_env_var(t_env **env, char *var);

// Function that prints the environment variables.
void		ft_env(t_env **env);

// Function that prints the working directory.
void		ft_pwd(t_mini *mini);

// Funtion that change the working directory.
void		ft_cd(t_mini *mini);

// Function that tokenize the getted input.
void		tokenizer(t_mini *mini, t_token *token);

// Function that write input to a fd.
void    ft_echo(t_mini *mini, int fd);

t_tree *creat_node(void *data);

void insert_data(t_tree *node, void *data, int side);

#endif