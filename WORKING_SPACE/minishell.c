/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:58:27 by alassiqu          #+#    #+#             */
/*   Updated: 2024/06/06 10:55:58 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <errno.h>
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
        printf("------------------->PIPE<----------------------\n");
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

int    main(int ac, char **av, char **env)
{
    (void)ac, (void)av;
    g_minishell = malloc(sizeof(t_minishell));
    if (!g_minishell)
        return (1);
    g_minishell->our_env = dup_env(env);
    signals();
    while (1)
    {
        g_minishell->line = readline(ORANGE PROMPT RESET);
        if (g_minishell->line[0])
            add_history(g_minishell->line);
        g_minishell->tokens = tokenizer();
        g_minishell->ast = parsing(g_minishell->tokens);
        if (!g_minishell->ast)
            continue ;
        printAST(g_minishell->ast, -1);
        // execution();
        clear_token(&g_minishell->tokens);
        free(g_minishell->line);
        // system("leaks minishell");
    }
    return (0);
}
