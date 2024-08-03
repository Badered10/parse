/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:23:51 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/03 15:42:35 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_env *env, t_minishell *minishell)
{
	char	*cwd;

	cwd = NULL;
	if (!get_env_var(env, "PWD"))
	{
		cwd = getcwd(NULL, 0);
		gc_add(minishell, cwd);
		printf("%s\n", cwd);
		return ;
	}
	printf("%s\n", get_env_var(env, "PWD"));
	minishell->exit_s = 0;
}
