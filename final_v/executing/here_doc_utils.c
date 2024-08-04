/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:08:11 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/04 10:41:28 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_here_doc(char *limiter, int fd, int *pipe, int expand_flag)
{
	char	*lines;
	int		old_count;
	char	*buf;

	buf = NULL;
	old_count = g_minishell->lines;
	while (1)
	{
		signal(SIGINT, here_doc_sig);
		read_buf(&buf, expand_flag);
		if (!write_or_break(fd, limiter, buf, old_count))
			break ;
	}
	lines = ft_itoa(g_minishell->lines);
	write(pipe[1], lines, ft_strlen(lines));
	free(lines);
	close(pipe[0]);
}
bool output_redirs(t_redir *new)
{
	if (!access(new->file, F_OK))
	{
		if (!access(new->file, W_OK))
			return (0);
		return (print_err("Permission denied", new->file), 1);
	}
	return (0);
}

bool	check_name(t_redir *new)
{
	struct stat	statbuf;

	statbuf.st_mode = 0;
	stat(new->file, &statbuf);
	if (S_ISDIR(statbuf.st_mode) == true)
		return (print_err("Is a directory", new->file), 1);
	if (new->fd == -1)
		return (print_err("ambiguous redirect", new->file), 1);
	if (new->type != L_REDIR)
		return (output_redirs(new));
	else if (!access(new->file, F_OK))
	{
		if (!access(new->file, R_OK))
			return (0);
		return (print_err("Permission denied", new->file), 1);
	}
	else
		return (print_err("No such file or directory", new->file), 1);
}
