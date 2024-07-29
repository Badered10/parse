/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:23:51 by alassiqu          #+#    #+#             */
/*   Updated: 2024/07/28 21:47:29 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_env *env)
{
	char	*cwd;

	cwd = NULL;
	if (!get_env_var(env, "PWD"))
	{
		cwd = getcwd(NULL, 0);
		gc_add(g_minishell, cwd);
		printf("%s\n", cwd);
		return ;
	}
	printf("%s\n", get_env_var(env, "PWD"));
	set_env_var(g_minishell->our_env, "?", "0");
	g_minishell->exit_s = 0;
}
