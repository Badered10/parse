/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:58:27 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/24 16:32:39 by baouragh         ###   ########.fr       */
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
        while (node->data.list)
        {
            printf("'%s' ", (char*)node->data.list->content);
            node->data.list = node->data.list->next;
        }
        printf("\n");
    }
	else if(node->type == PAIR_NODE)
	{
		// printf("(\n");
        printf("TYPE %u\n",node->data.pair.type);
        printAST(node->data.pair.left, 1);
        printAST(node->data.pair.right, 0);
        // printf(")\n");
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
