/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:15:09 by baouragh          #+#    #+#             */
/*   Updated: 2024/08/03 16:47:42 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*build_file_name(char *join)
{
	char	**split;
	char	*name;
	char	*tmp;
	int		i;

	split = ft_split(ttyname(0), '/');
	name = NULL;
	i = 0;
	while (split[i])
	{
		tmp = name;
		name = ft_strjoin(name, split[i]);
		free(tmp);
		i++;
	}
	tmp = name;
	name = ft_strjoin(name, join);
	free(tmp);
	if (access(name, F_OK) != 0)
		return (free_double(split), name);
	else
	{
		tmp = name;
		name = ft_strjoin(name, join);
		return (free_double(split), free(tmp), name);
	}
	return (NULL);
}

int	open_hidden_file(int doc_num)
{
	char	*join;
	char	*path;
	char	*name;
	int		fd;

	join = ft_itoa(doc_num);
	path = build_file_name(join);
	name = ft_strjoin(PATH, path);
	fd = open(name, O_CREAT | O_RDWR, 0777);
	free(name);
	free(path);
	free(join);
	if (fd < 0)
	{
		perror("here_doc failed to get input");
		return (-1);
	}
	return (fd);
}

int	re_open_hidden_file(int doc_num)
{
	char	*join;
	char	*path;
	char	*name;
	int		fd;

	join = ft_itoa(doc_num);
	path = build_file_name(join);
	name = ft_strjoin(PATH, path);
	fd = open(name, O_RDONLY);
	free(name);
	free(path);
	free(join);
	if (fd < 0)
	{
		perror("here_doc failed to get input");
		return (-1);
	}
	return (fd);
}

int	write_or_break(int fd, char *limiter, char *buf, int count)
{
	int		doc_len;
	int		buf_len;
	char	*count_s;

	if (!buf)
	{
		ft_putstr_fd("warning: here-document at line ", 2);
		count_s = ft_itoa(count);
		ft_putstr_fd(count_s, 2);
		free(count_s);
		ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(limiter, 2);
		ft_putstr_fd("')", 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	doc_len = ft_strlen(limiter);
	buf_len = ft_strlen(buf);
	if (!ft_strncmp(limiter, buf, buf_len + doc_len))
		return (0);
	write(fd, buf, buf_len);
	write(fd, "\n", 1);
	return (1);
}

void	read_buf(char **buf, int expand_flag, t_minishell *minishell)
{
	minishell->lines++;
	*buf = readline("> ");
	gc_add(minishell, *buf);
	if (*buf)
	{
		if (ft_strchr(*buf, '$') && expand_flag)
			*buf = helper_expander(*buf, minishell);
		gc_add(minishell, *buf);
	}
}

void	get_lines_count(int *pipe, t_minishell *minishell)
{
	char	buf[2048];

	close(pipe[1]);
	read(pipe[0], &buf, 2048);
	minishell->lines = ft_atoi(buf);
}

int	here_doc(char *limiter, int expand_flag, t_minishell *minishell)
{
	// int		id;
	int		pipe[2];
	int		fd_hidden;

	open_pipe(pipe);
	fd_hidden = -1;
	minishell->last_child = fork();
	if (!minishell->last_child)
	{
		do_here_doc(limiter, pipe, expand_flag, minishell);
		exit(0);
	}
	else
	{
		wait_and_get(minishell);
		if (minishell->exit_s != 130)
			get_lines_count(pipe, minishell);
		if (!minishell->exit_s)
		{
			fd_hidden = re_open_hidden_file(minishell->docs);
			return (fd_hidden);
		}
	}
	return (-1);
}
