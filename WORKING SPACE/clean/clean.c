/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 11:30:18 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/12 09:37:31 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cleanup_minishell(void)
{
	int	i;

	i = -1;
	clear_token(&g_minishell->tokens);
	clear_env();
	free(g_minishell->line);
}
