/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:22:58 by baouragh          #+#    #+#             */
/*   Updated: 2024/05/16 16:17:17 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Consume tokens bye one , and return the consumed one
t_token *consume_token(t_token ***tokens)
{
    t_token *next;
    
    next = **tokens;
    **tokens = (**tokens)->next;
    printf("'%s' Consumed and tokens point to type '%u'\n",next->value, (**tokens)->type);
    return(next);
}