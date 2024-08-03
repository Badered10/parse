/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:41:22 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/03 17:59:47 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_separator(t_token **tokens, char **line, t_minishell *minishell)
{
	if (!ft_strncmp(*line, "<<", 2))
		return (append_separator(tokens, line, LL_REDIR, minishell));
	else if (!ft_strncmp(*line, ">>", 2))
		return (append_separator(tokens, line, RR_REDIR, minishell));
	else if (!ft_strncmp(*line, "<", 1))
		return (append_separator(tokens, line, L_REDIR, minishell));
	else if (!ft_strncmp(*line, ">", 1))
		return (append_separator(tokens, line, R_REDIR, minishell));
	else if (!ft_strncmp(*line, "(", 1))
		return (append_separator(tokens, line, L_PAREN, minishell));
	else if (!ft_strncmp(*line, ")", 1))
		return (append_separator(tokens, line, R_PAREN, minishell));
	else if (!ft_strncmp(*line, "&&", 2))
		return (append_separator(tokens, line, AND, minishell));
	else if (!ft_strncmp(*line, "||", 2))
		return (append_separator(tokens, line, OR, minishell));
	else
		return (append_separator(tokens, line, PIPE, minishell));
}

t_token	*tokenizer_handler(char *line, t_minishell *minishell)
{
	t_token	*tokens;
	int		error;

	tokens = NULL;
	error = 0;
	while (*line)
	{
		if (error)
			return (gc_free_all(minishell), NULL);
		if (ft_isspace(*line))
			error = (!append_space(&tokens, &line, minishell) && 1);
		else if (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1)
			|| !ft_strncmp(line, "|", 1) || !ft_strncmp(line, "&&", 2)
			|| !ft_strncmp(line, "(", 1) || !ft_strncmp(line, ")", 1))
			error = (!handle_separator(&tokens, &line, minishell) && 1);
		else if (is_quote(*line))
			error = (!add_quote(&tokens, &line, minishell) && 1);
		else
			error = (!append_identifier(&tokens, &line, minishell) && 1);
	}
	add_token_back(&tokens, new_token(NULL, END, minishell), minishell);
	return (tokens);
}

t_token	*tokenizer(t_minishell *minishell)
{
	t_token	*tokens;
	char	*line;

	minishell->nb_tokens = 0;
	line = ft_strtrim(minishell->line, " \t\n\v\f\r");
	gc_add(minishell, line);
	tokens = tokenizer_handler(line, minishell);
	if (!tokens)
		gc_free_all(minishell);
	return (tokens);
}
