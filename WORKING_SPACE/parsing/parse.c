/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:09:11 by baouragh          #+#    #+#             */
/*   Updated: 2024/05/23 20:45:13 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

// static t_cmd *new_cmd(char *arg)
// {
//     t_cmd *new;

//     if (!arg)
//         return(NULL);
//     new = malloc(sizeof(t_cmd));
//     if (!new)
//         return(NULL);
//     new->arg = ft_strdup(arg);
//     if (!new->arg)
//         return(NULL);
//     new->next = NULL;
// }

// static void add_arg_back(t_cmd **list, t_cmd *new)
// {
    
// }

static t_node *parse_cmd(t_token **tokens) // "ls -a file"
{
    t_list *list;
    t_list *new;
    int x;

    x = 0;
    list = NULL;
    list = ft_lstnew((*tokens)->value);
    if (!list)
        return(NULL);
    while( *tokens && ((*tokens)->type == WORD || (*tokens)->type == WHITESPACE || (*tokens)->type == R_PAREN))
    {
        if(x && (*tokens)->type != WHITESPACE && (*tokens)->type != R_PAREN)
        {
            new = ft_lstnew((*tokens)->value);
            if (!new)
                return(NULL);
            ft_lstadd_back(&list,new);
        }
        (*tokens) = (*tokens)->next;
        x++;
    }
        return(printf("%d\n",x),string_node_new(list));
}

static t_node *parse_pipe(t_token **tokens) // 
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
        return (printf("PAIR, L:%p, R:%p\n",left, right),pair_node_new(left, parse_pipe(tokens)));
    }
    else
        return (printf("LEFT , %p\n",left),left);
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
            // printf("from while-> '%s'\n",res->data.string);
        // if(tmp->type == STRING_NODE)
        //     printf("from while-> '%s'\n",tmp->data.string);
        // if (tmp && tmp->type == PAIR_NODE)
        // {
        //     printf("L from while -> '%s'\n",tmp->data.pair.left->data.string);
        //     printf("R from while -> '%s'\n",tmp->data.pair.right->data.string);
        // }
        if (x == 0)
            res = tmp;
        x++;
        if(tokens)
            tokens = tokens->next;
    }
    // res = parse_pair(&tokens); // (a b)
    // printf("type is %s\n",tokens->value);
    return(res);
}