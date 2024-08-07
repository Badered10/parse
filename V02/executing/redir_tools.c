/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:14:45 by baouragh          #+#    #+#             */
/*   Updated: 2024/07/19 18:14:07 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_embgous(t_redir *new)
{
	t_list *asterisk;
	int		size;

	size = 0;
	if(ft_strchr(new->file, '*'))
	{
		asterisk = asterisk_functionality(new->file);
		size = ft_lstsize(asterisk);
		if(size == 1 || !size)
		{
			// if(size == 1 && !access((char *)asterisk->content, F_OK)) // < > >>
			// 	return(0);
			if (access(new->file, F_OK) == -1 && new->type != R_REDIR)
				print_err("no such file or directory", new->file);
			else if (!access(new->file, F_OK))
				print_err("permission denied", new->file);
			else
				return (0);
		}
		else if (size > 1)
			print_err("ambiguous redirect", new->file);
		g_minishell->exit_s = 1;
		return (1);
	}
	return (0);
}

int	open_redir(t_redir *redir)
{
	if(!is_embgous(redir))
	{
		redir->fd = open(redir->file, redir->mode, 0644);
		if (redir->fd < 0)
			return (0);
		return (1);
	}
	return (0);
}

int	open_and_set(t_list *red_list)
{
	t_redir	*new;

	while (red_list)
	{
		new = red_list->content;
		if (new->type != LL_REDIR)
		{
			if (!open_redir(new))
				return (0);
		}
		red_list = red_list->next;
	}
	return (1);
}
