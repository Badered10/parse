/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:40:46 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/21 17:13:32 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_left_valid3(t_type type)
{
	return ((type >= L_PAREN && type <= DOLLAR) || type == WORD);
}

int	is_right_valid3(t_type type)
{
	return (is_pipe_or_and(type) || type == R_PAREN || type == L_PAREN
		|| type == END);
}

int	check_right_parenthesis(t_token *token)
{
	if (!token->prev || !is_left_valid3(token->prev->type))
	{
		printf(RED "minishell: syntax error near unexpected token `)'\n" RESET);
		return (-1);
	}
	else if (!token->next || !is_right_valid3(token->next->type))
	{
		if (!is_right_valid3(token->next->type))
		{
			printf(RED "minishell: syntax error near unexpected token `%s'\n" RESET,
				token->next->value);
			return (-1);
		}
	}
	return (0);
}
