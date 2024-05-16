/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:09:11 by baouragh          #+#    #+#             */
/*   Updated: 2024/05/16 09:52:09 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

static t_node *parse_string(t_token **tokens)
{
    t_token next;
    next = consume_token(tokens);
    return(string_node_new(next.value));
}

static t_node *parse_pair(t_token **tokens) // )
{
    t_node *left;
    t_node *right;
    t_token next;

    next = consume_token(tokens); // consume a;
    printf("after a next '%s'\n",next.value);
    printf("after a tokens '%s'\n",(*tokens)->value);
    left = parse(tokens);
    next = consume_token(tokens); // consume space !!
    printf("after space next '%s'\n",next.value);
    printf("after space next '%s'\n",(*tokens)->value);
    exit(1);
    right = parse(tokens);
    next = consume_token(tokens); // consume R_paren !!
    return(pair_node_new(left, right));
}

t_node *parse(t_token **tokens)
{
    t_token next;

    next = consume_token(tokens);
    if (next.type == WORD)
        return(printf("1\n"),parse_string(tokens));
    else if(next.type == L_PAREN)
        return(printf("2\n"),parse_pair(tokens));
    else
        return(printf("3\n"),error_node_new("Expected ( or string"));
}

t_node *parsing(t_token *tokens)
{
    t_node *res;

    res = NULL;
    while(tokens)
    {
        res = parse(&tokens);
        printf("from while-> '%s'\n",res->data.string);
        tokens = tokens->next;
    }
    return(res);
}