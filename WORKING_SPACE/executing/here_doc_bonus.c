/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:15:09 by baouragh          #+#    #+#             */
/*   Updated: 2024/07/01 21:42:42 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	open_hidden_file(t_fd *doc_fd)
{
	doc_fd->infile = open(".tmp.txt", O_CREAT | O_RDWR | O_APPEND, 0777);
	if (doc_fd->infile < 0)
	{
		perror("here_doc failed to get input");
		exit(EXIT_FAILURE);
	}
}

static int	re_open_hidden_file(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		perror("here_doc failed to get input");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static void	read_input(char *read_buf)
{
	int	bytes_readed;

	bytes_readed = 0;
	bytes_readed = read(0, read_buf, MAX_INPUT);
	read_buf[bytes_readed] = 0;
	if (bytes_readed && read_buf[bytes_readed - 1] != '\n')
		write(1, "\n", 1);
}

static int	write_or_break(t_fd *fd, char **argv, char *read_buf)
{
	int	doc_len;
	int	buf_len;

	doc_len = ft_strlen(argv[2]); // LIMITER
	if (read_buf[doc_len] == '\n' || read_buf[doc_len] == '\0')
		if (!ft_strncmp (argv[2], read_buf, doc_len))
			return (0);
	buf_len = ft_strlen(read_buf);
	write(fd->infile, read_buf, buf_len);
	return (1);
}

void	here_doc(t_fd *fd, char **argv, int *i, int *cmds)
{
	char	*read_buf;
	int		fd_hidden;

	open_hidden_file(fd);
	while (1)
	{
		// write(1, "heredoc> ", sizeof("heredoc> "));
		// read_input(read_buf);
		// while (read_buf[0] == '\0')
		// 	read_input(read_buf);
		ft_readline(0);
		if (!write_or_break(fd, argv, read_buf))
			break ;
	}
	fd_hidden = re_open_hidden_file(".tmp.txt");
	dup_2(fd_hidden, 0);
	(*i) = 1;
	(*cmds)--;
}
