/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 21:05:29 by alassiqu          #+#    #+#             */
/*   Updated: 2024/07/11 19:35:59 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		// ft_putstr_fd("^C\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		set_env_var(g_minishell->our_env, "?", "130");
		g_minishell->exit_s = 130;
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		printf("WESH1\n");
		set_env_var(g_minishell->our_env, "?", "131");
		g_minishell->exit_s = 131;
	}
}
void	ft_sigint_after(int sig)
{
	if (sig == SIGINT)
	{
		set_env_var(g_minishell->our_env, "?", "130");
		g_minishell->exit_s = 130;
		// printf("after \n");
	}
	else if (sig == SIGQUIT)
	{
		printf("WESH2\n");
		set_env_var(g_minishell->our_env, "?", "131");
		g_minishell->exit_s = 131;
	}
}
void after_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, ft_sigint_after);
	signal(SIGQUIT, SIG_IGN);
}
void	signals(void)
{
	// rl_catch_signals = 0;
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
