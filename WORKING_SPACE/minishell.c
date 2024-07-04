/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:58:27 by alassiqu          #+#    #+#             */
/*   Updated: 2024/07/04 13:01:41 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_minishell	*g_minishell;

void	print_root(t_type type, int x)
{
	if (type == PIPE)
	{
		if (x == 1)
			printf("\nLEFT OF '|' -> ");
		else if (x == 0)
			printf("\nRIGHT OF '|' ----> ");
	}
	else if (type == OR)
	{
		if (x == 1)
			printf("\nLEFT OF '||' ----> ");
		else if (x == 0)
			printf("\nRIGHT OF '||' ----> ");
	}
	else if (type == AND)
	{
		if (x == 1)
			printf("\nLEFT OF '&&' ----> ");
		else if (x == 0)
			printf("\nRIGHT OF '&&' ----> ");
	}
	else if (type == L_PAREN)
	{
		if (x == 1)
			printf("\nLEFT OF '(' ----> ");
		else if (x == 0)
			printf("\nRIGHT OF '(' ----> ");
	}
}

void printAST(t_node* node , int x , t_type type) 
{
    t_type tmp;
    if (!node) return;
    tmp  = ERROR;
    if (node->type == STRING_NODE) // leaf
    {
        print_root(type, x);
        while (node->data.cmd)
        {
            printf("'%s' ", (char*)node->data.cmd->content);
            node->data.cmd = node->data.cmd->next;
        }
        printf("\n");
    }
	else if(node->type == PAIR_NODE) // root
	{
		print_root(type, x); // 4832948 , 234234
        if(node->data.pair.type == PIPE)
        {
            printf("------------------->PIPE<----------------------\n");
            tmp = PIPE;
        }
        else if (node->data.pair.type == OR)
        {
            printf("------------------->OR<----------------------\n");
            tmp = OR;
        } 
        else if (node->data.pair.type == AND)
        {
            printf("------------------->AND<----------------------\n");
            tmp = AND;
        }
            printAST(node->data.pair.left, 1 , tmp);
            printAST(node->data.pair.right, 0 , tmp);
    }
    else if (node->type == REDIR_NODE) // leaf
    {
        print_root(type, x);
        while(node->data.redir)
        {
            t_redir *new = node->data.redir->content;
            printf("REDIR NODE , name: '%s'\n",new->file);
            while (new->cmd)
            {
                printf("'%s' ", (char*)new->cmd->content);
                new->cmd = new->cmd->next;
            }
            printf("\n");
            node->data.redir = node->data.redir->next;
        }
    }
    else if(node->type == ERROR_NODE) // leaf
    {
        printf("add'%p', -ERROR -------> '%s",node ,node->data.error);
    }
}


void	print_tokens(t_token *tokens)
{
	t_token	*token;

	token = tokens;
	while (token)
	{
		printf("value => '%s'\n", token->value);
		printf("type => '%u'\n", token->type);
		token = token->next;
	}
}

int	init_minishell(char **env)
{
		g_minishell = malloc(sizeof(t_minishell));
		if (!g_minishell)
			return (0);
		g_minishell->dq_flag = 0;
		g_minishell->gc = NULL;
		g_minishell->stdin = dup(0);
		g_minishell->stdout = dup(1);
		// increment_shlvl();
		g_minishell->our_env = dup_env(env);
		if (!g_minishell->our_env)
			return (print_errors("dup_env failed !"), 0);
		add_env_var(g_minishell->our_env, "?", "0", false);
	return (1);
}

int	get_exit_status()
{
	char	*value;
	int		exit_status;

	value = get_env_var(g_minishell->our_env, "?");
	exit_status = ft_atoi(value);
	return (exit_status);
}

void	ft_readline(void)
{
	g_minishell->line = readline(ORANGE PROMPT RESET);
	// printf("\nYOOOOOOO\n");
	gc_add(g_minishell, g_minishell->line);
	// printf("**gc** :: line => '%p'\n", g_minishell->line);
	// set_env_var(g_minishell->our_env, "?", "0");
	if (!g_minishell->line)
	{
		ft_putstr_fd("line is empty exit\n", 1);
		clear_env();
		gc_free_all(g_minishell);
		free(g_minishell);
		// exit(get_exit_status());
		exit(1);
	}
		if (g_minishell->line[0])
			add_history(g_minishell->line);
}

int	main(int ac, char **av, char **env)
{
	(void)ac, (void)av;
	if (!init_minishell(env))
		return (1);
	while (1)
	{
		signals();
		ft_readline();
		after_signals();
		g_minishell->tokens = tokenizer();
		if (!g_minishell->tokens || syntax() == -1)
			continue ;
		g_minishell->ast = parsing();
		if (!g_minishell->ast)
			continue ;
		// printAST(g_minishell->ast, 3212, 23123);
		executer(g_minishell->ast);
		while(waitpid(-1, NULL, 0)!= -1);
		// dup2(g_minishell->stdin, 0);
		gc_free_all(g_minishell);
		dup2(g_minishell->stdout, 1);
		dup2(g_minishell->stdin, 0);
	}
	gc_free_all(g_minishell);
	clear_env();
	free(g_minishell);
	return (0);
}
