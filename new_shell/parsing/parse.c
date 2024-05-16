/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:09:11 by baouragh          #+#    #+#             */
/*   Updated: 2024/05/16 16:18:55 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

static t_node *parse_string(t_token **tokens)
{
    t_token *next;
    next = consume_token(&tokens);
    // printf("s_parse check :'%s'\n",next->value);
    return(string_node_new(next->value));
}

static t_node *parse_pair(t_token **tokens) // 
{
    t_node *left;
    t_node *right;
    t_token *next;

    next = consume_token(&tokens); // consume a;
    printf("passed to parse '%s'\n",(*tokens)->value);
    left = parse(tokens);
    next = consume_token(&tokens); // consume space !!
    printf("passed to parse '%s'\n",(*tokens)->value);
    right = parse(tokens);
    next = consume_token(&tokens); // consume R_paren !!
    return(pair_node_new(left, right));
}

t_node *parse(t_token **tokens) // input :  (a (b c))
{
    t_token *next;

    next = consume_token(&tokens);
    if (next->type == WORD)
        return(printf("WORD_PARSE interd \n"),parse_string(tokens));
    else if(next->type == L_PAREN)
        return(printf("PAIR_PARSE interd \n"),parse_pair(tokens));
    else
        return(printf("OTHER interd \n"),error_node_new("Expected ( or string"));
}

t_node *parsing(t_token *tokens)
{
    t_node *res;

    res = NULL;
    // while(tokens)
    // {
    //     res = parse(&tokens);
    //     printf("from while-> '%s'\n",res->data.string);
    //     tokens = tokens->next;
    // }
    res = parse_pair(&tokens); // (a b)
    printf("type is %s\n",tokens->value);
    return(res);
}