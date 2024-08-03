/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:33:43 by baouragh          #+#    #+#             */
/*   Updated: 2024/08/03 18:38:23 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_redires(t_list *red_list, t_minishell *minishell)
{
	int	fd_input;
	int	fd_output;

	if (!open_and_set(red_list, minishell))
		return ;
	fd_input = input_to_dup(red_list);
	fd_output = output_to_dup(red_list);
	if (fd_input > 0)
		dup_2(fd_input, 0);
	if (fd_output > 0)
		dup_2(fd_output, 1);
	run_doc_cmd(red_list, minishell);
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

t_list	*dollar_functionality(char **s, t_minishell *minishell)
{
	t_list	*lst;
	t_list	*temp;
	char	**split;
	char	*tmp;
	int		i;

	i = 0;
	lst = NULL;
	here_doc_expanding(s, minishell);
	if (!*s)
		return (*s = NULL, NULL);
	split = ft_split(*s, ' ');
	if (!split)
		return (*s = NULL, NULL);
	while (split[i])
	{
		tmp = ft_strdup(split[i]);
		gc_add(minishell, tmp);
		temp = ft_lstnew(tmp);
		gc_add(minishell, temp);
		ft_lstadd_back(&lst, temp);
		i++;
	}
	free_double(split);
	return (lst);
}

void	expand_list(t_list *cmd_lst, t_minishell *minishell)
{
	t_list	*list;

	list = NULL;
	if (!cmd_lst)
		return ;
	while (cmd_lst)
	{
		if(cmd_lst->content)
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
		}
		cmd_lst = cmd_lst->next;
	}
}

void	execute_cmd(t_node *node, t_minishell *minishell)
{
	// int	id;

	if (!node)
		return ;
	minishell->last_child = 0;
	expand_list(node->data.cmd, minishell);
	remove_null(&node, minishell);
	if (!node->data.cmd)
		return (set_env_var(minishell->our_env, "_", ""));
	set_env_var(minishell->our_env, "_",
		(char *)ft_lstlast(node->data.cmd)->content);
	if (ft_is_builtin(node->data.cmd->content))
		execute_builtins(minishell, list_to_argv(node->data.cmd, minishell));
	else
	{
		minishell->last_child = fork();
		if (!minishell->last_child)
		{
			signal(SIGQUIT, SIG_DFL);
			do_cmd(node, minishell);
			exit(0);
		}
	}
}

void	execute_and_or(t_node *node, t_minishell *minishell)
{
	if (!node)
		return ;
	if (node->data.pair.type == OR)
	{
		executer(node->data.pair.left, minishell);
		wait_and_get(minishell);
		if (minishell->exit_s && minishell->exit_s != 130)
			executer(node->data.pair.right, minishell);
	}
	else if (node->data.pair.type == AND)
	{
		executer(node->data.pair.left, minishell);
		wait_and_get(minishell);
		if (!minishell->exit_s)
			executer(node->data.pair.right, minishell);
	}
}

void	fork_pair(int type, t_node *node, int *pfd, t_minishell *minishell) // LEFT OR RIGHT, TYPE = || or &&
{
	// int id;

	minishell->last_child = fork();
	if (!minishell->last_child)
	{
		close(pfd[0]);
		if (!minishell->mode)
			dup_2(pfd[1], 1);
		else
			close(pfd[1]);
		executer(node->data.pair.left, minishell); // -> [pipe]
		wait_and_get(minishell);
		if (type == AND && !minishell->exit_s)
			executer(node->data.pair.right, minishell); // -> [pipe]
		else if (type == OR && minishell->exit_s
			&& minishell->exit_s != 130)
			executer(node->data.pair.right, minishell); // -> [pipe]
		wait_and_get(minishell);
		exit(minishell->exit_s);
	}
	close(pfd[1]);
	if (!minishell->mode)
		dup_2(pfd[0], 0);
	else
		close(pfd[0]);
}
void	run_doc_cmd_p(t_list *red_list , int *pfd , bool flag, t_minishell *minishell) // 1 last
{
	t_list	*last;
	t_redir	*new;

	// int id;

	last = ft_lstlast(red_list);
	new = last->content;
	if (new->cmd)
	{
		minishell->last_child = fork();
		if(!minishell->last_child )
		{
			if(flag)
			{
				close(pfd[1]);
			}
			else
			{
				dup_2(pfd[1],1);
			}
			close(pfd[0]);
			do_cmd(string_node_new(new->cmd, minishell), minishell);	
		}
	}
	else if (new->node)
	{	
		minishell->last_child = fork();
		if(!minishell->last_child )
		{
			if(flag)
			{
				close(pfd[1]);
			}
			else
			{
				dup_2(pfd[1],1);
			}
			close(pfd[0]);
			do_cmd(new->node, minishell);
		}
	}
}
void execute_redir_p(t_node *node , bool flag , int *pfd, t_minishell *minishell)
{
	int	fd_input;
	int	fd_output;

	t_list *red_list = node->data.redir;

	if (!open_and_set(red_list, minishell))
		return ;
	fd_input = input_to_dup(red_list);
	fd_output = output_to_dup(red_list);
	if (fd_input > 0)
	{
		dup_2(fd_input, 0);
	}
	else if(!flag)
	{
		dup_2(pfd[0], 0);
	}
	if (fd_output > 0)
	{
		dup_2(fd_output, 1);
	}
	run_doc_cmd_p(red_list, pfd , flag, minishell);
}
void	pipe_left(t_node *node, int *pfd, t_minishell *minishell)
{
	// int fd_in;
	// int fd_out;

	if (!node)
		return ;
	if (node->type != STRING_NODE && node->type != PIPE)
	{
		if (node->data.pair.type == AND)
			fork_pair(AND, node, pfd, 0);
		else if (node->data.pair.type == OR)
			fork_pair(OR, node, pfd, 0);
		else if (node->type == REDIR_NODE)
		{
				execute_redir_p(node, 0 , pfd, minishell);
		}
		else // (ls | cat -e)
		{
			// fd_in = dup(0);
			// fd_out = dup(1);
			// dup2(pfd[1],1);
			executer(node, minishell);
			// dup2(1,fd_out);
		}
	}
	else
		do_pipe(node, 0, pfd, minishell);
}


void	pipe_right(t_node *node, int *pfd, t_minishell *minishell)
{
	// int fd_in;
	// fd_in = dup(0);
	// dup2(pfd[0], 0);
	if (!node)
		return ;
	if (node->type != STRING_NODE)
	{
		if (node->data.pair.type == AND)
			fork_pair(AND, node, pfd, minishell); // 1
		else if (node->data.pair.type == OR) // OR CASE
			fork_pair(OR, node, pfd, minishell); // 1
		else if (node->type == REDIR_NODE)
		{
			execute_redir_p(node, 1 , pfd, minishell);
		}
		else
		{
			executer(node, minishell);
		}
	}
	else
		do_pipe(node, 1, pfd, minishell);
	// dup2(0, fd_in);
}

void	execute_pair(t_node *node, t_minishell *minishell)
{
	int	pfd[2];
	int fd_in;
	int fd_out;

	fd_in = dup(0);
	fd_out = dup(1);
	if (node->data.pair.type == PIPE) // (ls | cat -e) | cat -n | cat
	{
		open_pipe(pfd);
		dup2(pfd[1], 1);
		pipe_left(node->data.pair.left, pfd, minishell); //  (ls | cat -e)
		dup2(fd_out, 1);
		dup2(pfd[0], 0);
		pipe_right(node->data.pair.right, pfd, minishell); // cat -n
		close(pfd[1]);
		close(pfd[0]);
		dup2(fd_in, 0);
		dup2(fd_out, 1);
	}
	else
		execute_and_or(node, minishell);
}

bool check_builtin(char *cmd)
{
	char *built_ins[7];
	int  i;

	i = 0;
	if(!cmd)
		return(0);
	built_ins[0] = "echo";
	built_ins[1] = "cd";
	built_ins[2] = "pwd";
	built_ins[3] = "export";
	built_ins[4] = "unset";
	built_ins[5] = "env";
	built_ins[6] = "exit";
	while(built_ins[i])
	{
		if(!strncmp(cmd, built_ins[i], ft_strlen(cmd)))
			return(1);
		i++;
	}
	return(0);
}

void	executer(t_node *node, t_minishell *minishell) // (ls | cat -n) | cat -e
{
	bool is_builtin;
	int id;

	if (!node)
		return ;
	if (node->type == STRING_NODE)
	{
		is_builtin = ft_is_builtin((char *)node->data.cmd->content); // 
		if(node->data.cmd->is_block && is_builtin)
		{
			id = fork();
			if(!id)
			{
				execute_cmd(node, minishell);
				fprintf(stderr,"------------->1 \n");
				wait_last(minishell);
				fprintf(stderr,"------------->2 \n");
				while(waitpid(-1, NULL, 0) != -1);
				fprintf(stderr,"------------->3 \n");
				exit(minishell->exit_s);
			}
			else
				wait_last(minishell);
		}
		else
			execute_cmd(node, minishell);
		
	}
	else if (node->type == PAIR_NODE) // (ls | ps)
	{
		if(node->data.pair.is_block)
		{
			id = fork();
			if(!id)
			{
				execute_pair(node, minishell);
				wait_last(minishell);
				while(waitpid(-1, NULL, 0) != -1);
				exit(minishell->exit_s);
			}
			else
				wait_last(minishell);
		}
		else
			execute_pair(node, minishell);
	}
	else if (node->type == REDIR_NODE)
	{
		if(node->data.redir->is_block)
		{
			id = fork();
			if(!id)
			{
				execute_redires(node->data.redir, minishell);
				wait_last(minishell);
				while(waitpid(-1, NULL, 0) != -1);
				exit(minishell->exit_s);
			}
			else
				wait_last(minishell);
		}
		else
			execute_redires(node->data.redir, minishell);
	}
	// fprintf(stderr,"DONE --> ast : --> ");
	// print_ast("", node, false);
	// fprintf(stderr,"\n");
}
