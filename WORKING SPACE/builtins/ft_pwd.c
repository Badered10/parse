/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:23:51 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/07 18:42:44 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_env **env)
{
	if (!get_env_var(env, "PWD"))
	{
		printf("%s\n", getcwd(NULL, 0));
		return ;
	}
	printf("%s\n", get_env_var(env, "PWD"));
}
