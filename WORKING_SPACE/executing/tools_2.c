/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:20:22 by baouragh          #+#    #+#             */
/*   Updated: 2024/07/05 16:15:40 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void wait_and_get(void)
{
	char *exit;

	wait(&g_minishell->exit_s);
	if (WIFEXITED(g_minishell->exit_s))
		g_minishell->exit_s = WEXITSTATUS(g_minishell->exit_s);
	exit = ft_itoa(g_minishell->exit_s);
	if(!exit)
		return(print_errors("ERROR WITH FT_ITOA\n"));
	set_env_var(g_minishell->our_env, "?", exit);
	free(exit);
}

void do_cmd(t_node *ast)
{
    int id;
    char **cmd;
    char **env;

    cmd = list_to_argv(ast->data.cmd); // /path
    if(!cmd)
        return;
    env = env_to_envp(g_minishell->our_env);
    if(!env)
		return;
	id = check_cmd(*cmd, env);
	if(!id)
		call_execev(env, *cmd , cmd);
	exit(id);
}

void do_pipe(t_node *cmd , int mode , int *pfd) // cat -e 
{
	int	id;
	// int	pfd[2];

	// open_pipe(pfd);
	id = fork();
	if (id < 0)
	{
		print_err("pipex: error occuerd with fork!", NULL);
		return;
	}
	if (id == 0)
	{
			fd_duper(pfd, mode); // mode 0 normal, 1 last cmd // close pipe[0][1]
			do_cmd(cmd);
	}
	else
	{
		close(pfd[1]);
		dup_2(pfd[0], 0); // stdin -> pipe
		if(mode)
			wait_and_get();
	}
}
