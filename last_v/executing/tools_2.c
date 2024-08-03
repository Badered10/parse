/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:20:22 by baouragh          #+#    #+#             */
/*   Updated: 2024/08/03 17:36:22 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	wait_and_get(t_minishell *minishell)
{
	int		fail;
	int		x;
	char	*exit;

	x = -1;
	fail = -1;
	// fail = waitpid(minishell->last_child, &x, 0);
	fail = wait(&x);
	// if (minishell->exit_s == 130)
	// {
	// 	exit = ft_itoa(minishell->exit_s);
	// 	set_env_var(minishell->our_env, "?", exit);
	// 	return (free(exit), -1);
	// }
	if (x != -1 && WIFEXITED(x))
		minishell->exit_s = WEXITSTATUS(x);
	exit = ft_itoa(minishell->exit_s);
	set_env_var(minishell->our_env, "?", exit);
	return (free(exit), fail);
}

void	do_cmd(t_node *ast, t_minishell *minishell)
{
	// int		id;
	char	**cmd;
	char	**env;

	if (!ast)
		exit(0);
	minishell->last_child = 0;
	if (ft_is_builtin(ast->data.cmd->content))
		execute_builtins(minishell, list_to_argv(ast->data.cmd, minishell));
	else
	{
		cmd = list_to_argv(ast->data.cmd, minishell);
		if (!cmd)
			exit(0);
		env = env_to_envp(minishell->our_env, minishell);
		if (!env)
			exit(0);
		minishell->last_child = check_cmd(*cmd, minishell);
		if (!minishell->last_child)
			call_execev(env, *cmd, cmd, minishell);
	}
	exit(minishell->last_child);
}

void	do_pipe(t_node *cmd, int mode, int *pfd ,t_minishell *minishell)
{
	// int		id;
	t_list	*cmd_lst;
	t_list	*list;

	minishell->last_child = fork();
	if (minishell->last_child < 0)
	{
		print_err("error occuerd with fork!", NULL);
		return ;
	}
	if (minishell->last_child == 0)
	{
		fprintf(stderr,"%d\n",getpid());
		fd_duper(pfd, mode);
		cmd_lst = cmd->data.cmd;
		while (cmd_lst)
		{
			if (ft_strchr((char *)cmd_lst->content, '$') && cmd_lst->wd_expand)
			{
				list = dollar_functionality((char **)&cmd_lst->content, minishell);
				add_list_into_list(&cmd_lst, list);
			}
			else if (ft_strchr((char *)cmd_lst->content, '*'))
			{
				list = asterisk_functionality((char *)cmd_lst->content, minishell);
				add_list_into_list(&cmd_lst, list);
			}
			cmd_lst = cmd_lst->next;
		}
		remove_null(&cmd, minishell);
		if (!cmd->data.cmd)
			exit(0);
		do_cmd(cmd, minishell);
		exit(0);
	}
	else
	{
		close(pfd[1]);
		if(!mode)
			dup2(pfd[0], 0);
		else
			close(pfd[0]);
		// if (mode)
		// 	wait_and_get(minishell);
	}
}

int	execute_docs(t_list *red_list, t_minishell *minishell)
{
	if (do_here_docs(red_list, minishell) == 0)
		return (0);
	return (1);
}

void	unlink_docs(int docs)
{
	char	*name;
	char	*path;
	char	*join;

	if (!docs)
		return ;
	while (docs >= 0)
	{
		join = ft_itoa(docs);
		path = build_file_name(join);
		name = ft_strjoin(PATH, path);
		unlink(name);
		free(join);
		free(path);
		free(name);
		docs--;
	}
}
