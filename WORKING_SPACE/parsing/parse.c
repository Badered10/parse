/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:09:11 by baouragh          #+#    #+#             */
/*   Updated: 2024/06/04 22:45:35 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

static t_node *do_red(t_token **tokens)
{
    t_type type;
    type = (*tokens)->type;
    (*tokens) = (*tokens)->next;
    if((*tokens)->type == WHITESPACE)
        (*tokens) = (*tokens)->next;
    return (redir_node_new(type, (*tokens)->value, NULL));
}

static t_node *parse_cmd(t_token **tokens) // "ls < file -a"
{
    t_list *list;
    t_list *new;
    t_node *red;
    int x;

    x = 0;
    red = NULL;
    list = NULL;
    list = ft_lstnew((*tokens)->value);
    if (!list)
        return(NULL);
    while( *tokens && ((*tokens)->type == WORD || (*tokens)->type == WHITESPACE || (*tokens)->type == R_PAREN || ((*tokens)->type >= 4 && (*tokens)->type <= 7)))
    {
        if(x && (*tokens)->type != WHITESPACE && (*tokens)->type != R_PAREN && ((*tokens)->type < 4 || (*tokens)->type > 7))
        {
            new = ft_lstnew((*tokens)->value);
            if (!new)
                return(NULL);
            ft_lstadd_back(&list,new);
        }
        else if((*tokens)->type >= 4 && (*tokens)->type <= 7)
            red = do_red(tokens);
        (*tokens) = (*tokens)->next;
        x++;
    }
    if(!red)
        return(string_node_new(list));
    else
    {
        red->data.redir.cmd = list;
        return(red);
    }
}

static t_node *parse_pipe(t_token **tokens) // ls < file -la | cat 
{
    t_node *left;
    t_node *right;
    t_type type;

    left = NULL;
    right = NULL;
    if((*tokens)->type == L_PAREN)
            (*tokens) = (*tokens)->next;
    if(*tokens && (*tokens)->type == WORD)
        left = parse_cmd(tokens);
    if(*tokens && (*tokens)->type == WHITESPACE)
        (*tokens) = (*tokens)->next;
    if(*tokens && ((*tokens)->type == PIPE || (*tokens)->type == AND || (*tokens)->type == OR) )
    {
        type = (*tokens)->type;
        (*tokens) = (*tokens)->next;
        if((*tokens)->type == WHITESPACE || (*tokens)->type == L_PAREN)
            (*tokens) = (*tokens)->next;
        return (pair_node_new(left, parse_pipe(tokens), type));
    }
    else
        return (left);
}

t_node *parse_seq(t_token **tokens) // input :  "ls -a" | "cat -e file" | cat || ls && cat
{
    return(parse_pipe(tokens));
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
        tmp = parse_seq(&tokens);
        if (x == 0)
            res = tmp;
        x++;
        if(tokens)
            tokens = tokens->next;
    }
    return(res);
}