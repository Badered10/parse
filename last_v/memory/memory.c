/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:20:20 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/03 18:15:43 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tree(t_node **tree)
{
	t_redir	*new;
	t_list	*tmp;

	new = NULL;
	while ((*tree)->data.redir)
	{
		new = (*tree)->data.redir->content;
		tmp = (*tree)->data.redir->next;
		if (new->cmd)
		{
			ft_lstclear(&new->cmd, free);
			free(new->cmd);
		}
		free(new->file);
		free((*tree)->data.redir);
		free(new);
		(*tree)->data.redir = tmp;
	}
	free((*tree));
}

void	clear_ast(t_node *tree)
{
	if (!tree)
		return ;
	if (tree->type == STRING_NODE)
	{
		ft_lstclear(&tree->data.cmd, free);
		free(tree);
	}
	else if (tree->type == PAIR_NODE)
	{
		clear_ast(tree->data.pair.left);
		clear_ast(tree->data.pair.right);
	}
	else if (tree->type == REDIR_NODE)
	{
		free_tree(&tree);
	}
}

char	*ft_malloc(t_minishell *minishell, size_t size)
{
	char	*memory;

	memory = malloc(size);
	if (!memory)
		return (perror("Malloc failed!"), NULL);
	gc_add(minishell, memory);
	return (memory);
}

void	cleanup_minishell(t_minishell *minishell)
{
	close(minishell->stdin);
	close(minishell->stdout);
	clear_env(minishell->our_env);
	gc_free_all(minishell);
	free(minishell);
}
