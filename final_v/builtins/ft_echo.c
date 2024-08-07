/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:25:01 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/02 17:41:21 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_option(char *s)
{
	int	i;

	i = 1;
	if (s[0] != '-')
		return (0);
	if (!s[i])
		return (0);
	while (s[i] && s[i] == 'n')
		i++;
	if (!s[i])
		return (1);
	return (0);
}

void	ft_echo(char **args)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 0;
	while (args[i] && ft_check_option(args[i]) == 1)
	{
		new_line = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (new_line == 0)
		ft_putstr_fd("\n", 1);
	g_minishell->exit_s = 0;
}
