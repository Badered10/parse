/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:26:57 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/02 17:42:42 by baouragh         ###   ########.fr       */
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

int	builtins_exec_check(char **args)
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
		return (g_minishell->exit_s = 1, 1);
	}
	if ((!ft_strcmp(args[0], "export") || !ft_strcmp(args[0], "exit")
			|| !ft_strcmp(args[0], "unset")) && nb_options(args) == 0)
	{
		ft_putstr_fd(RED "badashell$ : ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": can't run it with options.\n" RESET, 2);
		return (g_minishell->exit_s = 1, 1);
	}
	return (0);
}

int	check_cd_and_exit(t_minishell *mini, char **args)
{
	int	flag;

	if (!ft_strcmp(args[0], "cd"))
	{
		if (nb_args(args) > 2)
		{
			print_errors("cd : too many arguments.");
			return (g_minishell->exit_s = 1, -1);
		}
		else
			return (ft_cd(mini, args[1]), 0);
	}
	else
	{
		flag = process_exit(args);
		if (flag == 0)
			return (0);
	}
	g_minishell->exit_s = 0;
	return (1);
}

void	execute_builtins(t_minishell *mini, char **args)
{
	if (builtins_exec_check(args))
		return ;
	if (!ft_strcmp(args[0], "echo"))
		ft_echo(args);
	else if (!ft_strcmp(args[0], "cd") || !ft_strcmp(args[0], "exit"))
		check_cd_and_exit(mini, args);
	else if (!ft_strcmp(args[0], "env"))
		ft_env(mini->our_env);
	else if (!ft_strcmp(args[0], "pwd"))
		ft_pwd(mini->our_env);
	else if (!ft_strcmp(args[0], "export"))
		ft_export(args, nb_args(args));
	else if (!ft_strcmp(args[0], "unset"))
	{
		if (args[1])
			ft_unset(args[1]);
	}
}
