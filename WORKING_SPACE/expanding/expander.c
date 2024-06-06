/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 11:11:46 by alassiqu          #+#    #+#             */
/*   Updated: 2024/06/06 11:07:51 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_dollar(char *s, int *i)
{
	char	*expand;
	char	*var;
	int		j;

	j = 0;
	expand = s + *i;
	expand++;
	if (ft_isspace(expand[j]))
	{
		*i += 2;
		return (2);
	}
	if (!ft_strncmp(&expand[j], "?", 1) || !ft_strncmp(&expand[j], "_", 1))
		j++;
	else
		while (expand[j] && (ft_isalnum(expand[j])))
			j++;
	*i += j;
	var = ft_substr(expand, 0, j);
	if (!check_env(var))
		return (0);
	else
		return (check_env(var));
}

char	*helper_expander(char *s)
{
	char	*value;
	int		len;
	int		i;

	i = -1;
	len = 0;
	while (s[++i])
	{
		if (s[i] == '\'')
			len += skip_quote(s, &i);
		else if (s[i] == '$')
			len += handle_dollar(s, &i);
		else
			len++;
	}
	value = fill_value(s, (len + 1));
	return (value);
}

void	expander(void)
{
	t_token	*tokens;

	tokens = g_minishell->tokens;
	while (tokens)
	{
		if (tokens->type == S_QUOTE)
		{
			tokens = tokens->next;
			while (tokens && tokens->type != S_QUOTE)
				tokens = tokens->next;
		}
		else if (tokens->type == WORD && ft_strchr(tokens->value, '$'))
			tokens->value = helper_expander(tokens->value);
		tokens = tokens->next;
	}
}
