/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:25:01 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/13 16:17:44 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit_status(char *s)
{
	if (!ft_strncmp(s, "$?", 2))
	{
		printf("%d\n", g_minishell->exit_status);
		return (1);
	}
	return (0);
}

int	ft_check_var(char *s)
{
	if (!ft_strncmp(s, "$", 1))
	{
		s++;
	}
	return (0);
}

int	ft_check_option(char *s)
{
	int	i;

	i = 0;
	if (s[0] != '-')
		return (0);
	i++;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(char **args)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 0;
	if (args[i] != NULL && ft_check_option(args[i]) == 1)
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
}
