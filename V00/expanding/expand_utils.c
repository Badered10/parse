/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:33:35 by alassiqu          #+#    #+#             */
/*   Updated: 2024/07/06 15:36:13 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_token(t_token **head, t_token *token)
{
	if (!token->prev)
	{
		*head = (*head)->next;
		if (*head)
			(*head)->prev = NULL;
	}
	else
	{
		token->prev->next = token->next;
		if (token->next)
			token->next->prev = token->prev;
	}
}

void	replace(t_token *current)
{
	current->value = ft_strdup("\0");
	gc_add(g_minishell, current->value);
	current->type = WORD;
}

void	remove_quotes(t_token **tokens)
{
	t_token	*current;
	t_token	*tmp;

	current = *tokens;
	while (current)
	{
		if (current->next && (current->type == S_QUOTE || current->type == D_QUOTE) && current->type == current->next->type)
		{
			tmp = current->next;
			remove_token(tokens, current);
			current = tmp;
			replace(current);
			current = current->next;
		}
		else if (current->type == S_QUOTE || current->type == D_QUOTE)
		{
			tmp = current->next;
			remove_token(tokens, current);
			current = tmp;
		}
		else
			current = current->next;
	}
}

void	remove_whitespace(t_token **tokens)
{
	t_token	*current;
	t_token	*tmp;

	current = *tokens;
	while (current)
	{
		if (current->type == WHITESPACE)
		{
			tmp = current->next;
			remove_token(tokens, current);
			current = tmp;
		}
		else
			current = current->next;
	}
}

void	post_expander(void)
{
	remove_quotes(&g_minishell->tokens);
}
