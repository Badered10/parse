/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 08:21:56 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/03 16:47:52 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_without_space(char *s, int len, t_minishell *minishell)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	gc_add(minishell, new);
	while (s && s[i])
	{
		if (ft_isspace(s[i]))
		{
			new[j++] = ' ';
			while (s && s[i] && ft_isspace(s[i]))
				i++;
		}
		else
			new[j++] = s[i++];
	}
	new[j] = '\0';
	return (new);
}

char	*avoid_spaces(char *s, t_minishell *minishell)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (ft_isspace(s[i]))
		{
			i++;
			len++;
			while (s[i] && ft_isspace(s[i]))
				i++;
		}
		else
		{
			i++;
			len++;
		}
	}
	return (expand_without_space(s, len, minishell));
}

void	here_doc_expanding(char **s, t_minishell *minishell)
{
	*s = avoid_spaces(helper_expander(*s, minishell), minishell);
}
