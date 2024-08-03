/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:01:30 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/03 17:57:55 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*new_token(char *value, t_type type, t_minishell *minishell)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	gc_add(minishell, new_token);
	new_token->value = value;
	gc_add(minishell, new_token->value);
	new_token->type = type;
	new_token->hd_expand = 0;
	new_token->next_space = 0;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	add_token_back(t_token **tokens, t_token *new_token, t_minishell *minishell)
{
	t_token	*curr_node;

	if (!*tokens)
	{
		*tokens = new_token;
		minishell->nb_tokens += 1;
		return ;
	}
	curr_node = *tokens;
	while (curr_node && curr_node->next)
		curr_node = curr_node->next;
	curr_node->next = new_token;
	new_token->prev = curr_node;
	minishell->nb_tokens += 1;
}

int	append_separator(t_token **tokens, char **line, t_type type, t_minishell *minishell)
{
	t_token	*token;
	char	*value;

	if (type == RR_REDIR || type == LL_REDIR || type == AND || type == OR)
		value = ft_substr(*line, 0, 2);
	else
		value = ft_substr(*line, 0, 1);
	// printf(">>>> value %s, type %d\n", value, type);
	token = new_token(value, type, minishell);
	if (!token)
		return (0);
	add_token_back(tokens, token, minishell);
	(*line)++;
	if (type == RR_REDIR || type == LL_REDIR || type == AND || type == OR)
		(*line)++;
	return (1);
}

int	append_identifier(t_token **tokens, char **line, t_minishell *minishell)
{
	t_token	*new;
	char	*value;
	char	*tmp;
	size_t	i;

	tmp = *line;
	i = 0;
	if (is_special(*tmp))
	{
		value = ft_substr(tmp, 0, 1);
		new = choose_token(value, *tmp, minishell);
		*line += 1;
		return (add_token_back(tokens, new, minishell), 1);
	}
	while (tmp[i] && !is_separator(tmp + i) && !is_quote(*(tmp + i)))
		i++;
	value = ft_substr(tmp, 0, i);
	if (!value)
		return (0);
	new = new_token(value, WORD, minishell);
	if (!new)
		return (0);
	*line += i;
	return (add_token_back(tokens, new, minishell), 1);
}

int	append_space(t_token **tokens, char **line, t_minishell *minishell)
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
	token = new_token(value, WHITESPACE, minishell);
	if (!token)
		return (0);
	add_token_back(tokens, token, minishell);
	(*line) += i;
	return (1);
}
