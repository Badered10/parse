/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 20:33:15 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/09 15:53:16 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_echo(t_mini *mini , int fd)
{
    char **str;
    str = ft_split(mini->input, ' ');
    write(fd,str[1],ft_strlen(str[1]));
    write(fd, "\n", 1);
}
