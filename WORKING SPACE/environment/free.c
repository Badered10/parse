/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:37:10 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/12 09:35:36 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clear_env(void)
{
	int	i;

	i = -1;
	while (g_minishell->our_env[++i])
	{
		free(g_minishell->our_env[i]->value);
		free(g_minishell->our_env[i]->key);
		free(g_minishell->our_env[i]);
	}
	free(g_minishell->our_env);
}
