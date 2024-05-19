/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:58:45 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/16 11:45:55 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*choose_token(char *value, char c)
{
	t_token *new;

	new = NULL;
	if (c == '\'')
		new = new_token(value, S_QUOTE);
	else if (c == '"')
		new = new_token(value, D_QUOTE);
	else if (c == '*')
		new = new_token(value, ASTERISK);
	else if (c == '$')
		new = new_token(value, DOLLAR);
	else if (c == '&')
		new = new_token(value, AMPERSAND);
	return (new);
}

void	clear_token(t_token **tokens)
{
	t_token	*curr_node;
	t_token	*next;

	curr_node = *tokens;
	if (!curr_node)
		return ;
	while (curr_node)
	{
		free(curr_node->value);
		next = curr_node->next;
		free(curr_node);
		curr_node = next;
	}
	*tokens = NULL;
}
