/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:22:58 by baouragh          #+#    #+#             */
/*   Updated: 2024/05/17 15:03:12 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Consume tokens bye one , and return the consumed one
t_token *consume_token(t_token ***tokens)
{
    t_token *next;

    next = **tokens;
    **tokens = (**tokens)->next;
    printf("'%s' Consumed and tokens point to vlaue '%s'\n",next->value, (**tokens)->value);
    return(next);
}