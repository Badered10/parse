/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:41:22 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/16 16:51:22 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_separator(t_token **tokens, char **line)
{
	if (!ft_strncmp(*line, "<<", 2))
		return (append_separator(tokens, line, LL_REDIR));
	else if (!ft_strncmp(*line, ">>", 2))
		return (append_separator(tokens, line, RR_REDIR));
	else if (!ft_strncmp(*line, "<", 1))
		return (append_separator(tokens, line, L_REDIR));
	else if (!ft_strncmp(*line, ">", 1))
		return (append_separator(tokens, line, R_REDIR));
	else if (!ft_strncmp(*line, "(", 1))
		return (append_separator(tokens, line, L_PAREN));
	else if (!ft_strncmp(*line, ")", 1))
		return (append_separator(tokens, line, R_PAREN));
	else if (!ft_strncmp(*line, "&&", 2))
		return (append_separator(tokens, line, AND));
	else if (!ft_strncmp(*line, "||", 2))
		return (append_separator(tokens, line, OR));
	else
		return (append_separator(tokens, line, PIPE));
}

t_token	*tokenizer_handler(char *line)
{
	t_token	*tokens;
	int		error;

	tokens = NULL;
	error = 0;
	while (*line)
	{
		if (error)
			return (clear_token(&tokens), NULL);
		if (ft_isspace(*line))
			error = (!append_space(&tokens, &line) && 1);
		else if (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1)
			|| !ft_strncmp(line, "|", 1) || !ft_strncmp(line, "&&", 2)
			|| !ft_strncmp(line, "(", 1) || !ft_strncmp(line, ")", 1))
			error = (!handle_separator(&tokens, &line) && 1);
		else
			error = (!append_identifier(&tokens, &line) && 1);
	}
	add_token_back(&tokens, new_token(NULL, END));
	return (tokens);
}

t_token	*tokenizer(void)
{
	t_token	*tokens;
	char	*line;

	g_minishell->nb_tokens = 0;
	line = g_minishell->line;
	tokens = tokenizer_handler(line);
	free(line);
	g_minishell->line = NULL;
	return (tokens);
}
