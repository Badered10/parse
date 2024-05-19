/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:59:18 by baouragh          #+#    #+#             */
/*   Updated: 2024/05/14 13:04:32 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void print_tree(t_tree *root)
{
    if(!root)
        return;
    printf("%s\n",root->value);
    print_tree(root->left);
    print_tree(root->right);
}

