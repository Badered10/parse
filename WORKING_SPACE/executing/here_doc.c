/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:15:09 by baouragh          #+#    #+#             */
/*   Updated: 2024/07/09 09:52:21 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	open_hidden_file(int doc_num)
{
	int	fd;
	char *join;
	char *name;

	join  = ft_itoa(doc_num);
	name = ft_strjoin(PATH, join);
	fd = open(name, O_CREAT | O_RDWR | O_APPEND, 0777);
	free(name);
	free(join);
	if (fd < 0)
	{
		perror("1 --> here_doc failed to get input");
		exit(EXIT_FAILURE);
	}
	return(fd);
}

static int	re_open_hidden_file(int doc_num)
{
	int	fd;
	char *join;
	char *name;

	join  = ft_itoa(doc_num);
	name = ft_strjoin(PATH, join);
	fd = open(name, O_RDONLY);
	free(name);
	free(join);
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
	doc_len = ft_strlen(limiter);
	buf_len = ft_strlen(buf);
	if (buf[0] == '\0' || !ft_strncmp (limiter, buf, buf_len))
		return (0);
	write(fd, buf, buf_len);
	write(fd,"\n",1);
	return (1);
}

static void	read_buf(char **buf)
{
	*buf = readline(">");
	if(*buf)
		gc_add(g_minishell, *buf);
}

static void	ft_sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		sig = 0;
		exit(130);
	}
}

void	h_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	here_doc(char *limiter ,int doc_num)
{
	char	*buf;
	int		fd;
	int		fd_hidden;
	int 	id;
	
	id = fork();
	if (!id)
	{
		h_signals();
		fd = open_hidden_file(doc_num);
		while (1)
		{
			read_buf(&buf);
			if (!write_or_break(fd, limiter, buf))
				break;
		}
		exit(0);
	}
	else
	{
		// after_signals();
		wait_and_get();
		if(!g_minishell->exit_s)
		{
			fd_hidden = re_open_hidden_file(doc_num);
			return(fd_hidden);
		}
		else if(g_minishell->exit_s == 130)
		{
			printf("CTRL + C , remove tmp file !!\n");
			unlink("/var/tmp/tmp.txt");
		}
	}
	return(-1);
}


// void	signal_rr(int s)
// {
// 	if (s == SIGINT)
// 	{
// 		printf("dd\n");
// 		exit(130);
// 	}
// }

// void	signal_rr_oo(int s)
// {
// 	if (s == SIGINT)
// 	{
// 		printf("\n");
// 	}
// }
