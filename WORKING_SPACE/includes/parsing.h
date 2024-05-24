/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 09:42:47 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/24 16:18:41 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define LEFT 0
# define RIGHT 1
#include "tokenization.h"
#include "../libft/libft.h"

typedef struct s_ast
{
    char            *value;
    struct s_ast    *left;
    struct s_ast    *right;
}                    t_ast;

// typedef struct s_cmd
// {
// 	char *arg;
// 	struct s_cmd *next;
// }				t_cmd;

typedef struct t_tree
{
    char *value;
    struct t_tree *left;
    struct t_tree *right;
}               t_tree;

typedef char CHAR_VALUE; // char
typedef const char * ERROR_VALUE;

typedef enum e_node // enum define two types of nodes.
{
    ERROR_NODE = -1,
	PAIR_NODE,
	CHAR_NODE,
	STRING_NODE
}			e_node_type;

typedef struct t_node t_node;


typedef struct s_pair_value
{
	t_type type;
	t_node *left;
	t_node *right;
}				t_pair_value;

typedef union u_node_value 
{
	t_pair_value	pair;
	CHAR_VALUE		char_value;
	t_list			*list;
    ERROR_VALUE 	error;
}				u_node_value;

struct t_node // strcut define a node
{
	e_node_type type;
	u_node_value data;
};

t_node *char_node_new(char c);
// t_node *pair_node_new(t_node *left, t_node *right);
t_node *pair_node_new(t_node *left, t_node *right, t_type type);
t_node *string_node_new(t_list *list);
t_node *error_node_new(const char *msg);
t_node *parsing(t_token *tokens);
t_node *parse(t_token **tokens);

// Function that checks the syntax.
int                    syntax(void);

#endif
