/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:01:30 by alassiqu          #+#    #+#             */
/*   Updated: 2024/07/12 17:17:05 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*new_token(char *value, t_type type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	gc_add(g_minishell, new_token);
	// printf("**gc** :: token => '%p'\n", new_token);
	new_token->value = value;
	new_token->type = type;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	add_token_back(t_token **tokens, t_token *new_token)
{
	t_token	*curr_node;

	if (!*tokens)
	{
		*tokens = new_token;
		g_minishell->nb_tokens += 1;
		return ;
	}
	curr_node = *tokens;
	while (curr_node && curr_node->next)
		curr_node = curr_node->next;
	curr_node->next = new_token;
	new_token->prev = curr_node;
	g_minishell->nb_tokens += 1;
}

int	append_separator(t_token **tokens, char **line, t_type type)
{
	t_token	*token;
	char	*value;

	if (type == RR_REDIR || type == LL_REDIR || type == AND || type == OR)
		value = ft_substr(*line, 0, 2);
	else
		value = ft_substr(*line, 0, 1);
	gc_add(g_minishell, value);
	// printf("**gc** :: value(sep) => '%p'\n", value);
	token = new_token(value, type);
	if (!token)
		return (0);
	add_token_back(tokens, token);
	(*line)++;
	if (type == RR_REDIR || type == LL_REDIR || type == AND || type == OR)
		(*line)++;
	return (1);
}

int	append_identifier(t_token **tokens, char **line) //ls -a
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
		gc_add(g_minishell, value);
		// printf("**gc** :: value(special) => '%p'\n", value);
		new = choose_token(value, *tmp);
		return ((*line += 1), add_token_back(tokens, new), 1);
	}
	while (tmp[i] && !is_separator(tmp + i) && !is_quote(*(tmp + i)))
		i++;
	value = ft_substr(tmp, 0, i);
	if (!value)
		return (0);
	gc_add(g_minishell, value);
	// printf("**gc** :: value(id) => '%p'\n", value);
	new = new_token(value, WORD);
	if (!new)
		return (0);
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
	gc_add(g_minishell, value);
	// printf("**gc** :: value(spc) => '%p'\n", value);
	token = new_token(value, WHITESPACE);
	if (!token)
		return (0);
	add_token_back(tokens, token);
	(*line) += i;
	return (1);
}
