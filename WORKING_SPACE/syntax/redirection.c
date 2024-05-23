/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:38:34 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/21 20:51:25 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_right_valid1(t_type type)
{
	return (type == S_QUOTE || type == D_QUOTE || type == ASTERISK
		|| type == DOLLAR || type == WORD);
}

int	is_redirection(t_type type)
{
	return ((type >= LL_REDIR && type <= R_REDIR));
}

int	syntax_second_phase(t_token *token)
{
	if (is_redirection(token->type))
	{
		if (!token->next || token->next->type == END)
		{
			printf(RED "minishell: syntax error near unexpected token `newline`\n" RESET);
            return (-1);
		}
		else if (!is_right_valid1(token->next->type))
		{
			printf(RED "minishell3: syntax error near unexpected token `%s`\n" RESET,
			token->next->value);
            return (-1);
        }
	}
	return (0);
}
