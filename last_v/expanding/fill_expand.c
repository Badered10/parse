/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:38:26 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/03 17:13:41 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	search_and_copy(char *expand, char *new, int *k, t_minishell *minishell)
{
	char	*expanded;
	char	*var;
	int		i;

	i = 0;
	var = ft_substr(expand, 0, (*k));
	expanded = get_env_var(minishell->our_env, var);
	free(var);
	if (!expanded)
		return ;
	else
	{
		while (expanded[i])
		{
			*new = expanded[i++];
			(*new)++;
		}
	}
}

void	general_case(char **expand, int *k)
{
	(*expand)++;
	while ((*expand)[(*k)])
	{
		if (ft_isalnum((*expand)[(*k)])
			|| !ft_strncmp(&(*expand)[(*k)], "_", 1))
			(*k)++;
		else
			break ;
	}
}

int	double_copy_case(char *expand)
{
	return (!ft_strncmp(&expand[1], "$", 1) || ft_isspace(expand[1])
		|| (!ft_isalnum(expand[1]) && ft_strncmp(&expand[1], "_", 1)
			&& ft_strncmp(&expand[1], "?", 1)) || !ft_isalnum(expand[1])
		|| ft_isnum(expand[1]));
}

void	fill_dollar(char *s, char *new, int *j, t_minishell *minishell)
{
	char	*expand;
	int		k;

	expand = s;
	k = 0;
	if (!ft_strncmp(&expand[1], "\0", 1))
		return (new[(*j)++] = (*s)++, (void)0);
	else if (!ft_strncmp(&expand[1], "?", 1) || !ft_strncmp(&expand[1], "_", 1))
	{
		k = 1;
		expand++;
	}
	else if (double_copy_case(expand))
	{
		new[(*j)++] = (*s)++;
		new[(*j)++] = (*s)++;
		return ;
	}
	else
		general_case(&expand, &k);
	s += k + 1;
	search_and_copy(expand, &new[*j], &k, minishell);
}
