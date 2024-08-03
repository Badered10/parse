/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:26:57 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/03 15:46:44 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	nb_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	nb_options(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!ft_strncmp(args[i], "-", 1) && args[i + 1]
			&& !ft_isdigit(*args[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

int	builtins_exec_check(char **args , t_minishell *minishell)
{
	if (!ft_strcmp(args[0], "env") && (nb_args(args) > 1 || !nb_options(args)))
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd("badashell$ : env: can't run it with ", 2);
		if (nb_args(args) > 1 && !nb_options(args))
			ft_putstr_fd("args and options.\n" RESET, 2);
		else if (nb_args(args) > 1)
			ft_putstr_fd("args.\n" RESET, 2);
		else if (nb_options(args))
			ft_putstr_fd("options.\n" RESET, 2);
		return (minishell->exit_s = 1, 1);
	}
	if ((!ft_strcmp(args[0], "export") || !ft_strcmp(args[0], "exit")
			|| !ft_strcmp(args[0], "unset")) && nb_options(args) == 0)
	{
		ft_putstr_fd(RED "badashell$ : ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": can't run it with options.\n" RESET, 2);
		return (minishell->exit_s = 1, 1);
	}
	return (0);
}

int	check_cd_and_exit(char **args, t_minishell *minishell)
{
	int	flag;

	if (!ft_strcmp(args[0], "cd"))
	{
		if (nb_args(args) > 2)
		{
			print_errors("cd : too many arguments.");
			return (minishell->exit_s = 1, -1);
		}
		else
			return (ft_cd(args[1], minishell), 0);
	}
	else
	{
		flag = process_exit(args, minishell);
		if (flag == 0)
			return (0);
	}
	minishell->exit_s = 0;
	return (1);
}

void	execute_builtins(t_minishell *minishell, char **args)
{
	int	i;

	i = 0;
	if (builtins_exec_check(args, minishell))
		return ;
	if (!ft_strcmp(args[0], "echo"))
		ft_echo(args, minishell);
	else if (!ft_strcmp(args[0], "cd") || !ft_strcmp(args[0], "exit"))
		check_cd_and_exit(args, minishell);
	else if (!ft_strcmp(args[0], "env"))
		ft_env(minishell->our_env, minishell);
	else if (!ft_strcmp(args[0], "pwd"))
		ft_pwd(minishell->our_env, minishell);
	else if (!ft_strcmp(args[0], "export"))
		ft_export(args, nb_args(args), minishell);
	else if (!ft_strcmp(args[0], "unset"))
	{
		while (args[++i])
			ft_unset(args[i], minishell);
	}
}
