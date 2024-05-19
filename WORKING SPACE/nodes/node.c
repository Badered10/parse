/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:02:16 by baouragh          #+#    #+#             */
/*   Updated: 2024/05/16 09:24:39 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node *char_node_new(char c)
{
    t_node *new;
    new = malloc(sizeof(t_node));
    new->type = CHAR_NODE;
    new->data.char_value = c;
    return (new);
}
t_node *string_node_new(char *string)
{
    t_node *new;
    new = malloc(sizeof(t_node));
    new->type = STRING_NODE;
    new->data.string = string;
    return (new);
}
t_node *pair_node_new(t_node *left, t_node *right)
{
    t_node *new;
    new = malloc(sizeof(t_node));
    new->type = PAIR_NODE;
    new->data.pair.left = left;
    new->data.pair.right = right;
    return (new);
}
t_node *error_node_new(const char *msg)
{
    t_node *new;
    new = malloc(sizeof(t_node));
    new->type = ERROR_NODE;
    new->data.error = msg;
    return (new);
}