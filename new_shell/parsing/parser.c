/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 09:42:13 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/13 14:10:08 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *parse_exp(t_token *token, int min_prec) // --> 0 , || &&
{
    char *lookahead;
    char op;
    int prec;
    int old_prec;
    char *rhs;

    old_prec = 0;
    prec = 0;
    lookahead = token->next->value;
    if (*lookahead == '*')
        old_prec = 1;
    while((*lookahead < '0' || *lookahead > '9') && old_prec >= min_prec && *lookahead)
    {
        op = *(lookahead);
        if (op == '*')
            prec = 1;
        printf("the lookahead token is %c, with precedence %d. the outer while loop is entered.\n",op,prec);
        lookahead++;
        rhs = lookahead;
        lookahead++;
            if (*lookahead == '*')
                prec = 1;
                else
                    prec = 0;
        while((*lookahead < '0' || *lookahead > '9') && prec >= old_prec && *lookahead)
        {
            printf("the lookahead token is %c, with precedence %d. the inner while loop is entered., min = %d, old = %d\n",*lookahead,prec,min_prec, old_prec);
            rhs = parse_exp(rhs, prec);
            lookahead++;
        }
        if(op == '*')
            lhs = ft_itoa(ft_atoi(lhs) * ft_atoi(rhs));
            else if(op == '-')
                lhs = ft_itoa(ft_atoi(lhs) - ft_atoi(rhs));
                else if (op == '+')
                   lhs = ft_itoa(ft_atoi(lhs) + ft_atoi(rhs));
    }
    return (printf("%s\n",lhs),lhs);
}

t_ast parser(t_token *tokens)
{
    
    printf("res :|%s|\n",parse_exp(tokens, 0));
}
