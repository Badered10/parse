/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:58:27 by alassiqu          #+#    #+#             */
/*   Updated: 2024/06/06 19:29:34 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

t_minishell	*g_minishell;

void printAST(t_node* node , int x) 
{
    if (!node) return;
    if (node->type == STRING_NODE)
    {
        if (x == 1)
            printf("LEFT ----> ");
            else if (x == 0)
                printf("RIGHT ----> ");      
        while (node->data.cmd)
        {
            printf("'%s' ", (char*)node->data.cmd->content);
            node->data.cmd = node->data.cmd->next;
        }
        printf("\n");
    }
	else if(node->type == PAIR_NODE)
	{
		// printf("(\n");
        if (x == 1)
            printf("LEFT ----> ");
            else if (x == 0)
                printf("RIGHT ----> ");
        if(node->data.pair.type == PIPE)
            printf("------------------->PIPE<----------------------\n");
        else if (node->data.pair.type == OR)
            printf("------------------->OR<----------------------\n");
        else
            printf("------------------->AND<----------------------\n");
        printAST(node->data.pair.left, 1);
        printAST(node->data.pair.right, 0);
        // printf(")\n");
    }
    else if (node->type == REDIR_NODE)
    {
         if (x == 1)
            printf("LEFT ----> ");
            else if (x == 0)
                printf("RIGHT ----> ");
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
}

void   print_tokens(t_token *tokens)
{
    t_token    *token;

    token = tokens;
    while (token)
    {
        printf("value => '%s'\n", token->value);
        printf("type ==> '%u'\n", token->type);
        token = token->next;
    }
}

int	init_minishell(char **env)
{
	g_minishell = malloc(sizeof(t_minishell));
	if (!g_minishell)
		return (0);
	g_minishell->our_env = dup_env(env);
	add_env_var(g_minishell->our_env, "?", "0", false);
	signals();
	return (1);
}

int    main(int ac, char **av, char **env)
{
    (void)ac, (void)av;
    if (!init_minishell(env))
		return (1);
    while (1)
    {
   	    g_minishell->line = readline(ORANGE PROMPT RESET);
		if (g_minishell->line[0])
			add_history(g_minishell->line);
		g_minishell->tokens = tokenizer();
		if (!g_minishell->tokens)
			continue ;
        if (syntax() == -1)
        {
            set_env_var(g_minishell->our_env, "?", ft_itoa(130));
            clear_token(&g_minishell->tokens);
            continue ;
        }
        expander();
        g_minishell->ast = parsing(g_minishell->tokens);
        if (!g_minishell->ast)
            continue ;
        printAST(g_minishell->ast, -1);
        // execution();
        clear_token(&g_minishell->tokens);
        free(g_minishell->line);
        // system("leaks minishell");
    }
    clear_env();
    return (0);
}
