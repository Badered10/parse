/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:33:35 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/03 17:19:02 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*new_value(char *s, int size, t_minishell *minishell)
{
	char	*new;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = s;
	new = ft_malloc(minishell, size);
	if (!new)
		return (NULL);
	while (*tmp)
	{
		if (*tmp == '$')
			fill_dollar(tmp, new, &j, minishell);
		else
			new[j++] = (*tmp)++;
	}
	new[j] = '\0';
	if (!new[0])
		return (NULL);
	return (new);
}

char	*helper_expander(char *s, t_minishell *minishell)
{
	char	*new;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '$')
			handle_dollar(s, &i, &len, minishell);
		else
		{
			len++;
			i++;
		}
	}
	new = new_value(s, len + 1, minishell);
	return (new);
}

int	contains_space(char *s)
{
	int	i;

	i = 0;
	while (s[i] && !ft_isspace(s[i]))
		i++;
	return ((s[i] != '\0'));
}
