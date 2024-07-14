/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:14:45 by baouragh          #+#    #+#             */
/*   Updated: 2024/07/14 17:41:08 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int fix_embgous(t_redir *new)// *0*csdasd
{
        if(new->file[0] == '*')
        {
            if(new->file[1] == '2')
            {
                new->file = ft_substr(new->file, 2, ft_strlen(new->file));
                gc_add(g_minishell, new->file);
                return(2);
            }
            else if (new->file[1] == '0')
            {
                new->file = ft_substr(new->file, 2, ft_strlen(new->file));
                gc_add(g_minishell, new->file);
                return(1);
            }
        }
        return(0);
}

int open_redir(t_redir *redir , int mode)
{
	redir->fd = open(redir->file,redir->mode, 0644); // mode : O_R , O_RW
    if(redir->fd < 0)
    {
        if(!mode || mode == 1)
        {
            if(access(redir->file, F_OK) == -1)
                print_err("badashell: no such file or directory: ",redir->file);
            else
                print_err("badashell: permission denied: ",redir->file);
        }
        else if(mode == 2)
            print_err("badashell: ambiguous redirect: ",redir->file);
        g_minishell->exit_s = 1;
        return (0);
    }
    return (1);
}

int open_and_set(t_list *red_list)
{
    t_redir *new ;
	while(red_list)
    {
		new = red_list->content;
		if(new->type != LL_REDIR)
        {
			if(!open_redir(new ,fix_embgous(new)))
                return (0);
        }
        red_list = red_list->next;
    }
    return (1);
}
