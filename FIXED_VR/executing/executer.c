/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:33:43 by baouragh          #+#    #+#             */
/*   Updated: 2024/08/29 19:43:22 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_and_or(t_node *node)
{
	if (!node)
		return ;
	if (node->data.pair.type == OR)
	{
		executer(node->data.pair.left);
		wait_last();
		wait_all();
		if (g_minishell->exit_s && g_minishell->exit_s != 130)
			executer(node->data.pair.right);
	}
	else if (node->data.pair.type == AND)
	{
		executer(node->data.pair.left);
		wait_last();
		wait_all();
		if (!g_minishell->exit_s)
			executer(node->data.pair.right);
	}
}

void	pipe_left(t_node *node, int *pfd)
{
	if (!node)
		return ;
	if (node->type != STRING_NODE)
	{
		if (node->type == PAIR_NODE)
		{
			g_minishell->last_child = fork();
			if (!g_minishell->last_child)
			{
				close(pfd[0]);
				close(pfd[1]);
				execute_pair(node);
				wait_last();
				while (waitpid(-1, NULL, 0) != -1)
					;
				exit(g_minishell->exit_s);
			}
		}
		else
			execute_redires(node->data.redir);
	}
	else
		do_pipe(node, pfd);
}

void	pipe_right(t_node *node, int *pfd)
{
	if (!node)
		return ;
	if (node->type != STRING_NODE)
	{
		if (node->data.pair.type == AND)
			executer(node);
		else if (node->data.pair.type == OR)
			executer(node);
		else if (node->type == REDIR_NODE)
			execute_redires(node->data.redir);
		else
			executer(node);
	}
	else
		do_pipe(node, pfd);
}

void	execute_pair(t_node *node)
{
	int	pfd[2];
	int	fd_in;
	int	fd_out;

	if (node->data.pair.type == PIPE)
	{
		if (open_pipe(pfd) == -1)
			return ;
		fd_in = dup(0);
		fd_out = dup(1);
		dup_2(pfd[1], 1);
		pipe_left(node->data.pair.left, pfd);
		if (dup2(fd_out, 1) == -1)
			perror("dup2 fd_out");
		dup_2(pfd[0], 0);
		pipe_right(node->data.pair.right, pfd);
		wait_last();
		dup_2(fd_in, 0);
		dup_2(fd_out, 1);
	}
	else
		execute_and_or(node);
}

void	executer(t_node *node)
{
	if (!node)
		return ;
	if (node->type == STRING_NODE)
	{
		if (node->data.cmd && node->data.cmd->is_block
			&& ft_is_builtin((char *)node->data.cmd->content))
			select_and_excute(node, STRING_NODE);
		else
			execute_cmd(node);
	}
	else if (node->type == PAIR_NODE)
	{
		if (node->data.pair.is_block)
			select_and_excute(node, PAIR_NODE);
		else
			execute_pair(node);
	}
	else if (node->type == REDIR_NODE)
		execute_redires(node->data.redir);
}
