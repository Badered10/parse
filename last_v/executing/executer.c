/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:33:43 by baouragh          #+#    #+#             */
/*   Updated: 2024/07/28 03:51:05 by marvin           ###   ########.fr       */
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
	t_list *save_next;

	if(!lst || !*lst || !new)
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

void expand_list(t_list *cmd_lst)
{
	t_list *list;

	list = NULL;
	if (!cmd_lst)
		return;
	while(cmd_lst)
	{
		if (ft_strchr((char*)cmd_lst->content, '$'))
		{
			list = dollar_functionality((char **)&cmd_lst->content);
			add_list_into_list(&cmd_lst, list);
		}
		else if(ft_strchr((char*)cmd_lst->content, '*'))
		{
			list = asterisk_functionality((char*)cmd_lst->content);
			add_list_into_list(&cmd_lst, list);
		}
		cmd_lst = cmd_lst->next;
	}
}

void	execute_cmd(t_node *node)
{
	int	id;

	if (!node)
		return ;
	id = 0;
	expand_list(node->data.cmd);
	set_null_as_true(&node);
	if(!node->data.cmd)
		return (set_env_var(g_minishell->our_env, "_", ""));
	set_env_var(g_minishell->our_env, "_", (char *)ft_lstlast(node->data.cmd)->content);
	if (ft_is_builtin(node->data.cmd->content))
	{
		execute_builtins(g_minishell, list_to_argv(node->data.cmd));
		set_env_var(g_minishell->our_env, "?", "0");
		g_minishell->exit_s = 0;
	}
	else
	{
		id = fork();
		if (!id)
			do_cmd(node);
	}
}

void	execute_and_or(t_node *node)
{
	if (!node)
		return;
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

void fork_pair(int type, t_node *node , int *pfd, bool way) // LEFT OR RIGHT, TYPE = || or &&
{
	int	id;

	id = fork();
	if (!id)
	{
		close(pfd[0]);
		if(!way)
			dup_2(pfd[1], 1);
		else
			close(pfd[1]);
		executer(node->data.pair.left); // -> [pipe]
		wait_and_get();
		if(type == AND && !g_minishell->exit_s)
			executer(node->data.pair.right); // -> [pipe]
		else if (type == OR && g_minishell->exit_s && g_minishell->exit_s != 130)
			executer(node->data.pair.right); // -> [pipe]
		wait_and_get();
		exit(g_minishell->exit_s);
	}
	if(!way)
		dup_2(pfd[0], 0);
	else
		close(pfd[0]);
}

void pipe_left(t_node *node, int *pfd)
{
	int std_in;
	int std_out;

	if(!node)
		return;
	if (node->type != STRING_NODE && node->type != PIPE)
		{
			if (node->data.pair.type == AND)
				fork_pair(AND , node, pfd, 0);
			else if (node->data.pair.type == OR)
				fork_pair(OR , node, pfd, 0);
			else if (node->type == REDIR_NODE)
			{
				std_out = dup(1);
				std_in = dup(0);
				executer(node);
				dup_2(std_out, 1);
				dup_2(std_in, 0);
			}
			else
				executer(node);
		}
	else
		do_pipe(node, 0, pfd);
}

void pipe_right(t_node *node, int *pfd)
{
	if(!node)
		return;
	if (node->type != STRING_NODE)
		{
			if (node->data.pair.type == AND)
				fork_pair(AND , node, pfd, 1);
			else if (node->data.pair.type == OR) // OR CASE
				fork_pair(OR , node, pfd, 1);
			else
				executer(node);
		}
	else
		do_pipe(node, 1, pfd);
}

void	execute_pair(t_node *node)
{
	int pfd[2];
	int id;

	if (node->data.pair.type == PIPE)
	{
		open_pipe(pfd);
		pipe_left(node->data.pair.left, pfd);
		pipe_right(node->data.pair.right, pfd);
		close(pfd[1]);
		close(pfd[0]);
	}
	else
		execute_and_or(node);
}

void	executer(t_node *node)
{
	if (!node)
		return ;
	if (node->type == STRING_NODE)
		execute_cmd(node);
	else if (node->type == PAIR_NODE)
		execute_pair(node);
	else if (node->type == REDIR_NODE)
		execute_redires(node->data.redir);
	// fprintf(stderr,"DONE --> ast : --> ");
	// print_ast("", node, false);
	// fprintf(stderr,"\n");
}
