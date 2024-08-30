/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 08:08:03 by baouragh          #+#    #+#             */
/*   Updated: 2024/08/30 08:19:25 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	left_pipe(t_node *node, int *pfd, int fd_in, int fd_out)
{
	dup_2(pfd[1], 1);
	pipe_left(node->data.pair.left, pfd);
	if (dup2(fd_out, 1) == -1)
	{
		perror("dup2 fd_out");
		fd_closer(pfd);
		dup_2(fd_in, 0);
		dup_2(fd_out, 1);
		return ;
	}
	dup_2(pfd[0], 0);
}

void	exe_non_opfd(t_node *node, int fd_in, int fd_out)
{
	int	pfd[2];

	if (node->data.pair.type == PIPE)
	{
		if (open_pipe(pfd) == -1)
			return ;
		fd_in = dup(0);
		fd_out = dup(1);
		left_pipe(node, pfd, fd_in, fd_out);
		pipe_right(node->data.pair.right, pfd);
		dup_2(fd_in, 0);
		dup_2(fd_out, 1);
		wait_last();
	}
	else
		execute_and_or(node);
}

void	exe_old_pfd(t_node *node, int *pfd_2, int fd_in, int fd_out)
{
	int	pfd[2];

	g_minishell->last_child = fork();
	if (!g_minishell->last_child)
	{
		fd_closer(pfd_2);
		if (node->data.pair.type == PIPE)
		{
			if (open_pipe(pfd) == -1)
				return ;
			fd_in = dup(0);
			fd_out = dup(1);
			left_pipe(node, pfd, fd_in, fd_out);
			pipe_right(node->data.pair.right, pfd);
			dup_2(fd_in, 0);
			dup_2(fd_out, 1);
			wait_last();
		}
		else
			execute_and_or(node);
		exit(g_minishell->exit_s);
	}
}
