/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:58:27 by alassiqu          #+#    #+#             */
/*   Updated: 2024/07/13 14:03:05 by baouragh         ###   ########.fr       */
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
	t_list *list;

    if (!node) return;
    tmp  = ERROR;
    if (node->type == STRING_NODE) // leaf
    {
        print_root(type, x);
		list = node->data.cmd;
        while (list)
        {
            printf("'%s' ", (char*)list->content);
            list = list->next;
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
			if(new->node)
				printAST(new->node, 121,231);
            node->data.redir = node->data.redir->next;
        }
    }
    // else if(node->type == ERROR_NODE) // leaf
    // {
    //     printf("add'%p', -ERROR -------> '%s",node ,node->data.error);
    // }
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
		g_minishell->stdin = dup(0); //  dup2(pipe[0], 0); parent // dup2 ?? 
		g_minishell->stdout = dup(1); // 
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

int execute_docs(t_list *red_list)
{
	if (do_here_docs(red_list , g_minishell->docs) == 0)
		return (0);
	return(1);
}

int scan_and_set(t_node *node)
{
	if (!node)
		return(0);
	if(node->type == PAIR_NODE)
	{
		if(!scan_and_set(node->data.pair.left))
			return(0);
		if(!scan_and_set(node->data.pair.right))
			return(0);
	}
    else if (node->type == REDIR_NODE) // leaf
		return(execute_docs(node->data.redir));
	return(1);
}

void unlink_docs(int docs)
{
	char *name;
	char *join;

	if(!docs)
		return;
	while(docs >= 0)
	{
		join = ft_itoa(docs);
		name = ft_strjoin(PATH, join);
		unlink(name);
		free(join);
		free(name);
		docs--;
	}
}
void hand(int sig)
{
	if(sig != SIGQUIT)
		return;
	printf("Quit (core dumped)\n");
}

void hand2(int sig)
{
	if(sig != SIGINT)
		return;
	printf("\n");
}

int	main(int ac, char **av, char **env)
{
	char *exit_stat;
	(void)ac, (void)av;
	if (!init_minishell(env))
		return (1);
	while (1)
	{
		g_minishell->docs = 0;
		g_minishell->exit_s = 0;
		signals();
		ft_readline();
		g_minishell->tokens = tokenizer();
		if (!g_minishell->tokens || syntax() == -1)
			continue ;
		g_minishell->ast = parsing();
		if (!g_minishell->ast)
			continue ;
		signal(SIGINT, SIG_IGN);
		if(scan_and_set(g_minishell->ast))
		{
			signal(SIGQUIT, hand);
			signal	(SIGINT, hand2);
			executer(g_minishell->ast);
		}
		// signal(SIGQUIT, SIG_IGN);
		while(wait_and_get() != -1);
		gc_free_all(g_minishell);
		dup2(g_minishell->stdout, 1);
		dup2(g_minishell->stdin, 0);
		unlink_docs(g_minishell->docs);
		exit_stat = ft_itoa(g_minishell->exit_s);
		set_env_var(g_minishell->our_env, "?", exit_stat);
		free(exit_stat);
	}
	gc_free_all(g_minishell);
	clear_env();
	free(g_minishell);
	return (0);
}
