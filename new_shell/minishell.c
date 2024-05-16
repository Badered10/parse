/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:58:27 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/16 16:53:50 by baouragh         ###   ########.fr       */
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
		// while (g_minishell->tokens)
        // {
        //     printf("value +> %s\n", g_minishell->tokens->value);
        //     printf("type +> %u\n", g_minishell->tokens->type);
        //     g_minishell->tokens = g_minishell->tokens->next;
        // }
		g_minishell->ast = parsing(g_minishell->tokens);
		if (g_minishell->ast->type == STRING_NODE)
			printf("in main : %s\n",g_minishell->ast->data.string);
	}
	return (0);
}
