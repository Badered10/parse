/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:58:27 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/12 09:56:16 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_minishell	*g_minishell;

int	main(int ac, char **av, char **env)
{
	(void)ac, (void)av;
	g_minishell = malloc(sizeof(t_minishell));
	if (!g_minishell)
		return (1);
	g_minishell->our_env = dup_env(env);
	signals();
	while (1)
	{
		g_minishell->line = ft_strtrim(readline(ORANGE PROMPT RESET), " \t\n\v\f\r");
		if (g_minishell->line[0])
			add_history(g_minishell->line);
		g_minishell->tokens = tokenizer();
		g_minishell->ast = parser();
		system("leaks minishell");
	}
	return (0);
}
