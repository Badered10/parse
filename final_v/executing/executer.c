/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:33:43 by baouragh          #+#    #+#             */
/*   Updated: 2024/08/04 09:53:10 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_redires(t_list *red_list)
{
	int	fd_input;
	int	fd_output;

	if (!open_and_set(red_list))
		return ;
	fd_input = input_to_dup(red_list);
	fd_output = output_to_dup(red_list);
	if (fd_input > 0)
		dup_2(fd_input, 0);
	if (fd_output > 0)
		dup_2(fd_output, 1);
	run_doc_cmd(red_list);
}

void	add_list_into_list(t_list **lst, t_list *new)
{
	t_list	*save_next;

	if (!lst || !*lst || !new)
		return ;
	save_next = (*lst)->next;
	(*lst)->content = new->content;
	(*lst)->next = new->next;
	ft_lstlast(*lst)->next = save_next;
}

t_list	*dollar_functionality(char **s)
{
	t_list	*lst;
	t_list	*temp;
	char	**split;
	char	*tmp;
	int		i;

	i = 0;
	lst = NULL;
	here_doc_expanding(s);
	if (!*s)
		return (*s = NULL, NULL);
	split = ft_split(*s, ' ');
	if (!split)
		return (*s = NULL, NULL);
	while (split[i])
	{
		tmp = ft_strdup(split[i]);
		gc_add(g_minishell, tmp);
		temp = ft_lstnew(tmp);
		gc_add(g_minishell, temp);
		ft_lstadd_back(&lst, temp);
		i++;
	}
	free_double(split);
	return (lst);
}

void	expand_list(t_list *cmd_lst)
{
	t_list	*list;

	list = NULL;
	if (!cmd_lst)
		return ;
	while (cmd_lst)
	{
		if (cmd_lst->content)
		{
			if (ft_strchr((char *)cmd_lst->content, '$') && cmd_lst->wd_expand)
			{
				list = dollar_functionality((char **)&cmd_lst->content);
				add_list_into_list(&cmd_lst, list);
			}
			else if (ft_strchr((char *)cmd_lst->content, '*'))
			{
				list = asterisk_functionality((char *)cmd_lst->content);
				add_list_into_list(&cmd_lst, list);
			}
		}
		cmd_lst = cmd_lst->next;
	}
}

void	execute_cmd(t_node *node)
{
	if (!node)
		return ;
	g_minishell->last_child = 0;
	expand_list(node->data.cmd);
	remove_null(&node);
	if (!node->data.cmd)
		return (set_env_var(g_minishell->our_env, "_", ""));
	set_env_var(g_minishell->our_env, "_",
		(char *)ft_lstlast(node->data.cmd)->content);
	if (ft_is_builtin(node->data.cmd->content))
		execute_builtins(g_minishell, list_to_argv(node->data.cmd));
	else
	{
		g_minishell->last_child = fork();
		if (!g_minishell->last_child)
		{
			signal(SIGQUIT, SIG_DFL);
			do_cmd(node);
			exit(0);
		}
	}
}

void	execute_and_or(t_node *node)
{
	if (!node)
		return ;
	if (node->data.pair.type == OR)
	{
		executer(node->data.pair.left);
		wait_and_get();
		if (g_minishell->exit_s && g_minishell->exit_s != 130)
			executer(node->data.pair.right);
	}
	else if (node->data.pair.type == AND)
	{
		executer(node->data.pair.left);
		wait_and_get();
		if (!g_minishell->exit_s)
			executer(node->data.pair.right);
	}
}

void	pipe_left(t_node *node, int *pfd, bool mode)
{
	if (!node)
		return ;
	if (node->type != STRING_NODE && node->type != PIPE)
	{
		if (node->data.pair.type == AND)
			executer(node);
		else if (node->data.pair.type == OR)
			executer(node);
		else if (node->type == REDIR_NODE)
			execute_redires(node->data.redir);
		else
			executer(node);
	}
	else
		do_pipe(node, mode, pfd);
}

void	pipe_right(t_node *node, int *pfd, bool mode)
{
	if (!node)
		return ;
	if (node->type != STRING_NODE)
	{
		if (node->data.pair.type == AND)
			executer(node);
		else if (node->data.pair.type == OR)
			executer(node);
		else if (node->type == REDIR_NODE)
			execute_redires(node->data.redir);
		else
			executer(node);
	}
	else
		do_pipe(node, mode, pfd);
}

void	execute_pair(t_node *node)
{
	int	pfd[2];
	int fd_in;
	int fd_out;

	if (node->data.pair.type == PIPE) // (ls | cat -e) | cat -n | cat
	{
		fd_in = dup(0);
		fd_out = dup(1);
		open_pipe(pfd);
		dup_2(pfd[1], 1);
		pipe_left(node->data.pair.left, pfd, 0); //  (ls | cat -e)
		dup2(fd_out, 1);
		dup_2(pfd[0], 0);
		pipe_right(node->data.pair.right, pfd, 1); // cat -n | cat  
		dup_2(fd_in, 0);
		dup_2(fd_out, 1);
	}
	else
		execute_and_or(node);
}

void selcet_and_excute(t_node *node, int type)
{
	int id;

	id = fork();
	if(!id)
	{
		if (type == STRING_NODE)
			execute_cmd(node);
		else if (type == PAIR_NODE)
			execute_pair(node);
		else
			execute_redires(node->data.redir);
		wait_last();
		while(waitpid(-1, NULL, 0) != -1);
		exit(g_minishell->exit_s);
	}
	else
		wait_last();
}

void	executer(t_node *node)
{
	if (!node)
		return ;
	if (node->type == STRING_NODE)
	{
		if(node->data.cmd->is_block 
				&& ft_is_builtin((char *)node->data.cmd->content))
			selcet_and_excute(node, STRING_NODE);
		else
			execute_cmd(node);
	}
	else if (node->type == PAIR_NODE)
	{
		if(node->data.pair.is_block)
			selcet_and_excute(node, PAIR_NODE);
		else
			execute_pair(node);
	}
	else if (node->type == REDIR_NODE)
	{
		if(node->data.redir->is_block)
			selcet_and_excute(node, REDIR_NODE);
		else
			execute_redires(node->data.redir);
	}
}
