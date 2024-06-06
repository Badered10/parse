/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 09:42:47 by alassiqu          #+#    #+#             */
/*   Updated: 2024/06/06 10:04:23 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define LEFT 0
# define RIGHT 1
#include "tokenization.h"
#include "../libft/libft.h"


typedef char CHAR_VALUE; // char
typedef const char * ERROR_VALUE;

typedef enum e_node // enum define two types of nodes.
{
    ERROR_NODE = -1,
	PAIR_NODE,
	CHAR_NODE,
	REDIR_NODE,
	STRING_NODE
}			e_node_type;

typedef struct t_node t_node;


typedef struct s_redir
{
	t_type type;
    int mode;
    int fd;
    char *file;
    t_list *cmd;
}              t_redir;

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
	t_list			*cmd;
	t_list			*redir;
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
t_node *redir_node_new(t_list *red_list ,t_type type ,char *file);
t_node *parsing(t_token *tokens);
// t_node *parse(t_token **tokens);

// Function that checks the syntax.
int                    syntax(void);

#endif
