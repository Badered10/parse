/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:09:20 by baouragh          #+#    #+#             */
/*   Updated: 2024/07/04 18:32:01 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_pipe(int *pfd)
{
	if (pipe(pfd))
	{
		perror("pipe:");
		return;
	}
}

int	dup_2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) < 0)
		return (-1);
	close(old_fd);
	return (0);
}

void	fd_duper( int *pfd , int mode)
{
	if (mode == 1) // close pipe and leave stdout to 1 or to file
	{
		close(pfd[1]);
		close(pfd[0]);
	}
	else // write to pipe[1] // 0
	{
		close(pfd[0]);
		if (dup_2(pfd[1], 1)) // 
			exit(EXIT_FAILURE);
	}
}

char	*get_command(char *argv)
{
	char	*cmd;
	int		i;

	i = 0;
	while (argv[i] != ' ' && argv[i] != '\0')
		i++;
	cmd = malloc(i + 1);
	gc_add(g_minishell, cmd);
	if (!cmd)
	{
		perror("malloc");
		return (NULL);
	}
	ft_memmove(cmd, argv, i);
	cmd[i] = '\0';
	return (cmd);
}

char	*add_slash_cmd(char *path, char *cmd)
{
	char	*a_path;
	char	*fullpath;

	a_path = (ft_strjoin(path, "/"));
	fullpath = ft_strjoin(a_path, cmd);
	if (!access(fullpath, X_OK))
		return (free(a_path), fullpath);
	else
		return (free(fullpath), free(a_path), NULL);
}