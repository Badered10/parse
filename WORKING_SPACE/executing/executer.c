/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:33:43 by baouragh          #+#    #+#             */
/*   Updated: 2024/07/05 12:15:49 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_redires(t_list *red_list)
{
	int fd_input;
	int fd_output;

	if (do_here_docs(red_list) == 0)
		return (print_errors("ERROR ACCURE WITH HERE_DOC\n"));
	open_and_set(red_list);
	fd_input = input_to_dup(red_list);
	fd_output = output_to_dup(red_list);
	if(fd_input > 0)
		dup2(fd_input, 0);
	if(fd_output > 0)
		dup2(fd_output, 1);
	run_doc_cmd(red_list);
}

void execute_cmd(t_node *node)
{
	int id;
	if (ft_is_builtin(node->data.cmd->content))
    {
        printf("Yes its a builtin\n");
        execute_builtins(g_minishell, list_to_argv(node->data.cmd));
    }
    else
	{
		id = fork();
		if(!id)
            do_cmd(node);
		else
			wait_and_get();
	}
}

void execute_and_or(t_node *node)
{
	if (node->data.pair.type == OR)
	{
		executer(node->data.pair.left);
		if(g_minishell->exit_s)
		{
			// dup2(g_minishell->stdin, 0);
			executer(node->data.pair.right);
		}
	}
	else if (node->data.pair.type == AND)
	{
		executer(node->data.pair.left);
		if(!g_minishell->exit_s)
		{
			// dup2(g_minishell->stdin, 0);
			executer(node->data.pair.right);
		}
	}
}

// void handlle_pair_pipe(t_node *node) // (ls && ps ) | cat -e | cat -n
// {
// 	if(node->type == AND)
// 	{
// 		if(node->data.pair.left == PAIR_NODE)
// 			handlle_pair_pipe(node->data.pair.left);
// 		else
// 		{
// 			do_pipe(node, 0);
// 		}
// 		if(!g_minishell->exit_s)
// 		{
// 			// dup2(g_minishell->stdin, 0);
// 			if(node->data.pair.right == PAIR_NODE)
// 				handlle_pair_pipe(node->data.pair.right);
// 			else
// 				do_pipe(node, 1);
// 		}
// 	}
// 	else if(node->type == OR)
// 	{
// 		if(node->data.pair.left == PAIR_NODE)
// 			handlle_pair_pipe(node->data.pair.left);
// 		else
// 			do_pipe(node->data.pair.left , 0);
// 		if(g_minishell->exit_s)
// 		{
// 			// dup2(g_minishell->stdin, 0);
// 			if(node->data.pair.right == PAIR_NODE)
// 				handlle_pair_pipe(node->data.pair.right);
// 			else
// 				do_pipe(node->data.pair.left , 1);
// 		}
// 	}
// }

void execute_pair(t_node *node)
{
	if(node->data.pair.type == PIPE) // (ls && ps ) | cat -e | cat -n
	{
		int	pfd[2];
		open_pipe(pfd);
		char buf[10];
	
		if(node->data.pair.left->type != STRING_NODE)
		{
			dup_2(g_minishell->pipe[1], 1);
			executer(node->data.pair.left); // write on pipe !!
			read(1, &buf, 10);
			// dup2(g_minishell->stdout, 1);
			write(2, buf, sizeof(buf));
			// dup_2(1, 0);
			close(g_minishell->pipe[0]);
		}
			// handlle_pair_pipe(node);
		else
		{
			do_pipe(node->data.pair.left , 0 , pfd); // do cmd
		}
		if(node->data.pair.right->type != STRING_NODE)
			executer(node->data.pair.right);
			// handlle_pair_pipe(node);
		else
			do_pipe(node->data.pair.right, 1, pfd); // do last one
	}
	else
		execute_and_or(node);
}

void    executer(t_node *node) // ls | wc | cat && ps
{
	if (!node)
		return;
    if (node->type == STRING_NODE) // leaf 
		execute_cmd(node);
	else if(node->type == PAIR_NODE) // pair
		execute_pair(node);
    else if (node->type == REDIR_NODE) // leaf
		execute_redires(node->data.redir);
}
