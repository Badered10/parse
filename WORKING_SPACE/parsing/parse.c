/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:09:11 by baouragh          #+#    #+#             */
/*   Updated: 2024/06/08 16:10:08 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

static t_redir *do_red(t_token **tokens) // 
{
    t_redir *new;

    new = malloc(sizeof(t_redir));
    if(!new)
        return(NULL);
    ft_bzero(new, sizeof(t_redir));
    new->type = (*tokens)->type;
    (*tokens) = (*tokens)->next;
    if((*tokens)->type == WHITESPACE)
        (*tokens) = (*tokens)->next;
    new->file = (*tokens)->value;
    return (new);
}

static t_node *parse_cmd(t_token **tokens) // 
{
    t_list *cmd_list;
    t_list *red_list;
    t_list *new;
    t_redir *red;

    cmd_list = NULL;
    red_list = NULL;
    while(*tokens && ((*tokens)->type != END && (*tokens)->type != PIPE && (*tokens)->type != OR && (*tokens)->type != AND  && (*tokens)->type != L_PAREN))
    {
        if((*tokens)->type >= 4 && (*tokens)->type <= 7)
        {
            red = do_red(tokens);
            new = ft_lstnew(red);
            if (!new)
                return(NULL);
            ft_lstadd_back(&red_list, new);
        }
        else if((*tokens)->type == WORD)
        {
            new = ft_lstnew((*tokens)->value);
            if (!new)
                return(NULL);
            ft_lstadd_back(&cmd_list,new);
        }
            (*tokens) = (*tokens)->next;
    }
    if(!red_list)
        return(string_node_new(cmd_list));
    else
    {
        red->cmd = cmd_list;
        return (redir_node_new(red_list));
    }
}

static t_node *parse_pipe(t_token **tokens) // (1 && 2) || 3
{
    t_node *left;
    t_type type;

    left = NULL;
    // if((*tokens)->type == L_PAREN)
    //         (*tokens) = (*tokens)->next;
    if(*tokens && ((*tokens)->type == WORD || ((*tokens)->type >= 4 && (*tokens)->type <= 7)) )
        left = parse_cmd(tokens);
    if(*tokens && (*tokens)->type == WHITESPACE)
        (*tokens) = (*tokens)->next;
    if(*tokens && ((*tokens)->type == PIPE))
    {
        type = (*tokens)->type;
        (*tokens) = (*tokens)->next;
        if((*tokens)->type == WHITESPACE)
            (*tokens) = (*tokens)->next;
        return (pair_node_new(left, parse_pipe(tokens), type));
    }
    // else if(!left)
    //     return(error_node_new("invalid pair node from pipe func\n"));
    else
        return (left);
}

t_node *parse_or(t_token **tokens)
{
    t_node *left;
    t_type type;

    left = parse_pipe(tokens);
    if(*tokens && (*tokens)->type == OR)
    {
        type = (*tokens)->type;
        (*tokens) = (*tokens)->next;
        if((*tokens)->type == WHITESPACE || (*tokens)->type == L_PAREN)
            (*tokens) = (*tokens)->next;
        return (pair_node_new(left, parse_or(tokens), type));
    }
    else
        return(left);
}

t_node *parse_seq(t_token **tokens) // 
{
    t_node *left;
    t_type type;

    left = parse_or(tokens);
    if(*tokens && (*tokens)->type == AND)
    {
        type = (*tokens)->type;
        (*tokens) = (*tokens)->next;
        if((*tokens)->type == WHITESPACE || (*tokens)->type == L_PAREN)
            (*tokens) = (*tokens)->next;
        return (pair_node_new(left, parse_seq(tokens), type));
    }
    else
        return(left);
}

t_node *parse_block(t_token **tokens) // (ls)
{
    t_node *left;
    t_type type;

    if((*tokens)->type != L_PAREN)
        left = parse_seq(tokens);
    if(*tokens && (*tokens)->type == L_PAREN)
    {
        type = (*tokens)->type;
        (*tokens) = (*tokens)->next;
        left = parse_seq(tokens);
        if((*tokens)->type == WHITESPACE)
            (*tokens) = (*tokens)->next;
        return (pair_node_new(left, parse_block(tokens), type));
    }
    else
        return(left);
}

t_node *parsing(t_token *tokens) // (1 && 2) || 3
{
    t_node *res;

    printf("first cur token value :'%u'\n",tokens->type);
    res = parse_block(&tokens);
    printf("last cur token value :'%u'\n",tokens->type);
    printf("( ,cur token value :'%u'\n",L_PAREN);

    return(res);
}