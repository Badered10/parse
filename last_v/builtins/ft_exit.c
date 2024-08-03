/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:18:18 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/03 15:43:56 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_out_of_range(const char *str)
{
	const char	*pos_limit = "9223372036854775807";
	const char	*neg_limit = "-9223372036854775808";
	size_t		len;

	len = strlen(str);
	if (str[0] == '-')
	{
		if (len > 20)
			return (1);
		if (len == 20 && ft_strcmp(str, neg_limit) > 0)
			return (1);
	}
	else
	{
		if (str[0] == '+')
		{
			len--;
			str++;
		}
		if (len > 19)
			return (1);
		if (len == 19 && ft_strcmp(str, pos_limit) > 0)
			return (1);
	}
	return (0);
}

void	ft_exit(char *args, int print, t_minishell *minishell)
{
	int	exit_status;

	exit_status = minishell->exit_s;
	if (args)
	{
		exit_status = ft_atoi(args);
	}
	if (print)
		ft_putstr_fd("exit\n", 1);
	if (is_out_of_range(args))
	{
		print_exit_error(args);
		exit(2);
	}
	cleanup_minishell(minishell);
	exit(exit_status);
}
