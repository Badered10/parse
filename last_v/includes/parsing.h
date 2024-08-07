/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 09:42:47 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/02 17:52:38 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define LEFT 0
# define RIGHT 1
# include "../libft/libft.h"
# include "tokenization.h"

typedef enum e_node
{
	PAIR_NODE,
	CHAR_NODE,
	REDIR_NODE,
	STRING_NODE
}						t_node_type;

typedef struct s_node	t_node;

typedef struct s_redir
{
	t_type				type;
	int					mode;
	int					fd;
	int					hd_expand;
	char				*file;
	bool				is_block;
	t_list				*cmd;
	t_node				*node;
}						t_redir;

typedef struct s_pair_value
{
	t_type				type;
	t_node				*left;
	t_node				*right;
	bool				is_block;
}						t_pair_value;

typedef union u_node_value
{
	t_pair_value		pair;
	char				char_value;
	t_list				*cmd;
	t_list				*redir;
}						t_node_value;

struct					s_node
{
	t_node_type			type;
	t_node_value		data;
};

#endif /* PARSER_H */