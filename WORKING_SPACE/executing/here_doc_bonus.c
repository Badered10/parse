/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:15:09 by baouragh          #+#    #+#             */
/*   Updated: 2024/07/02 23:53:48 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	dup_2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) < 0)
		return (-1);
	close(old_fd);
	return (0);
}

static int	open_hidden_file(void)
{
	int fd;
	fd = open("/var/tmp/tmp.txt", O_CREAT | O_RDWR | O_APPEND, 0777);
	if (fd < 0)
	{
		perror("1 --> here_doc failed to get input");
		exit(EXIT_FAILURE);
	}
	return(fd);
}

static int	re_open_hidden_file(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		perror("2 --> here_doc failed to get input");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static int	write_or_break(int fd, char *limiter, char *buf)
{
	int	doc_len;
	int	buf_len;

	if(!buf)
		return(0);
	doc_len = ft_strlen(limiter); // LIMITER
	if (buf[doc_len] == '\n' || buf[doc_len] == '\0')
		if (buf[0] == '\0' || !ft_strncmp (limiter, buf, doc_len))
			return (0);
	buf_len = ft_strlen(buf);
	write(fd, buf, buf_len);
	return (1);
}

static void	read_buf(char **buf)
{
	*buf = readline(">");
	// if(*buf)
	// 	gc_add(g_minishell, buf);
}

void	here_doc(char *limiter)
{
	char	*buf;
	int		fd;
	int		fd_hidden;

	fd = open_hidden_file();
	while (1)
	{
		// while (read_buf[0] == '\0')
		// 	read_input(read_buf);
		read_buf(&buf);
		if(signals())
			return;
		if (!write_or_break(fd, limiter, buf))
			break;
	}
	fd_hidden = re_open_hidden_file("/var/tmp/tmp.txt");
	dup_2(fd_hidden, 0);
}
