/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:09:11 by baouragh          #+#    #+#             */
/*   Updated: 2024/05/22 15:22:29 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

static t_node *parse_string(t_token **tokens)
{
    t_token *next;
    next = NULL;
    if(*tokens)
    {
        // next = consume_token(&tokens);
        return(string_node_new((*tokens)->value));
    }
        return(NULL);
    // printf("s_parse check :'%s'\n",next->value);
}

static t_node *parse_pair(t_token **tokens) // 
{
    t_node *left;
    t_node *right;
    // t_token *next;

    // next = consume_token(&tokens); // consume a;
    printf("passed to parse '%s'\n",(*tokens)->value);
    left = parse(tokens);
    // next = consume_token(&tokens); // consume space !!
    printf("passed to parse '%s'\n",(*tokens)->value);
    right = parse(tokens);
    // next = consume_token(&tokens); // consume R_paren !!
    return(pair_node_new(left, right));
}

t_node *parse(t_token **tokens) // input :  (a (b c))
{
    t_token *next;

    next = consume_token(&tokens);
    if (next->type == WORD || next->type == WHITESPACE || next->type == R_PAREN)
        return(printf("'%s'--->WORD_PARSE interd \n",next->value),parse_string(&next));
    else if(next->type == L_PAREN)
        return(printf("'%s'--->PAIR_PARSE interd \n",next->value),parse_pair(tokens));
    else
        return(printf("'%s'--->OTHER interd \n",next->value),error_node_new("Expected ( or string"));
}

t_node *parsing(t_token *tokens)
{
    t_node *tmp;
    t_node *res;
    int x;

    x = 0;
    if (syntax() == -1)
        return (NULL);
    while(tokens)
    {
        tmp = parse(&tokens);
        // printf("from while-> '%s'\n",res->data.string);
        printf("from while-> '%s'\n",tmp->data.string);
        if (x == 0)
            res = tmp;
        x++;
        tokens = tokens->next;
    }
    // res = parse_pair(&tokens); // (a b)
    // printf("type is %s\n",tokens->value);
    return(res);
}