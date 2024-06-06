/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:09:11 by baouragh          #+#    #+#             */
/*   Updated: 2024/06/06 17:28:24 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

static t_redir *do_red(t_token **tokens) // take file and type
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

static t_node *parse_cmd(t_token **tokens) // "ls < file -a"
{
    t_list *cmd_list;
    t_list *red_list;
    t_list *new;
    t_redir *red;

    cmd_list = NULL;
    red_list = NULL;
    while(*tokens && ((*tokens)->type == WORD || (*tokens)->type == WHITESPACE || (*tokens)->type == R_PAREN || ((*tokens)->type >= 4 && (*tokens)->type <= 7)))
    {
        if((*tokens)->type != WHITESPACE && (*tokens)->type != R_PAREN && ((*tokens)->type < 4 || (*tokens)->type > 7))
        {
            new = ft_lstnew((*tokens)->value);
            if (!new)
                return(NULL);
            ft_lstadd_back(&cmd_list,new);
        }
        else if((*tokens)->type >= 4 && (*tokens)->type <= 7) // > file -a
        {
            red = do_red(tokens);
            new = ft_lstnew(red);
            if (!new)
                return(NULL);
            ft_lstadd_back(&red_list, new);
        }
        if (*tokens)
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