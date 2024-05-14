/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:22:14 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/11 09:26:05 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: `", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("': No such file or directory\n", 2);
}

int	cd_home(t_minishell *mini)
{
	char	*home;

	set_env_var(mini->our_env, "OLDPWD", get_env_var(mini->our_env, "PWD"));
	home = get_env_var(mini->our_env, "HOME");
	if (!home)
		return (ft_putstr_fd(RED "$minishell >> : cd: HOME not set\n" RESET, 2),
			1);
	if (!chdir(home))
		return (set_env_var(mini->our_env, "PWD", home), 0);
	return (1);
}

void	ft_cd(t_minishell *mini, char *path)
{
	char	*cwd;

	if (!path)
	{
		cd_home(mini);
		return ;
	}
	if (!chdir(path))
	{
		cd_error(path);
		return ;
	}
	set_env_var(mini->our_env, "OLDPWD", get_env_var(mini->our_env, "PWD"));
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		printf("getcwd: unable to determine current directory.\n");
		return ;
	}
	set_env_var(mini->our_env, "PWD", cwd);
}
