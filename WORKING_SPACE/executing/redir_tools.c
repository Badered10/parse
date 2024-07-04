/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:14:45 by baouragh          #+#    #+#             */
/*   Updated: 2024/07/04 18:14:56 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void open_redir(t_redir *redir)
{
	redir->fd = open(redir->file,redir->mode, 0644);
}

void open_and_set(t_list *red_list)
{
    t_redir *new ;
	while(red_list) // linked list of reds
    {
		new = red_list->content;
        // printf("REDIR NODE , name: '%s'\n",new->file);
		if(new->type != LL_REDIR)
			open_redir(new);
        red_list = red_list->next;
    }
}
