/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:40:40 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/11 15:42:11 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


t_tree *creat_node(void *data) // int x = 3; // char *str = "hello"; // char c = 'c';
{
    t_tree *new;
    new = malloc(sizeof(t_tree));
    new->data = data;
    new->right = NULL;
    new->left = NULL;
    return (new);
}

void insert_data(t_tree *node, void *data, int side)
{
    if (!side)
        node->left = creat_node(data);
    else
        node->right = creat_node(data);
}

// int        parse_input(t_mini *mini)
// {
    
// }