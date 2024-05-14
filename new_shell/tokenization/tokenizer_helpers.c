/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:01:30 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/11 15:27:23 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*new_token(char *value, t_type type)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	return (new_token);
}

void	add_token_back(t_token **tokens, t_token *new_token)
{
	t_token	*curr_node;

	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	curr_node = *tokens;
	while (curr_node && curr_node->next)
		curr_node = curr_node->next;
	curr_node->next = new_token;
	new_token->prev = curr_node;
}

int	append_separator(t_token **tokens, char **line, t_type type)
{
	t_token	*token;

	token = new_token(NULL, type);
	if (!token)
		return (0);
	add_token_back(tokens, token);
	(*line)++;
	if (type == RR_REDIR || type == LL_REDIR || type == AND || type == OR)
		(*line)++;
	return (1);
}

int	append_identifier(t_token **tokens, char **line)
{
	t_token	*new;
	char	*value;
	char	*tmp;
	size_t	i;

	tmp = *line;
	i = 0;
	while (tmp[i] && !is_separator(tmp + i))
	{
		if (is_quote(tmp[i]))
		{
			if (!skip_quotes(tmp, &i))
				return (print_quote_err(tmp[i]), 0);
		}
		else
			i++;
	}
	value = ft_substr(tmp, 0, i);
	if (!value)
		return (0);
	new = new_token(value, WORD);
	if (!new)
		return (free(value), 0);
	*line += i;
	return (add_token_back(tokens, new), 1);
}

int	append_space(t_token **tokens, char **line)
{
	t_token	*token;
	char	*value;
	char	*tmp;
	int		i;

	i = 0;
	tmp = *line;
	while (tmp[i] && ft_isspace(tmp[i]))
		i++;
	value = ft_substr(*line, 0, i);
	if (!value)
		return (0);
	token = new_token(value, WHITESPACE);
	if (!token)
		return (0);
	add_token_back(tokens, token);
	(*line) += i;
	return (1);
}
