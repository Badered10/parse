/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:03:59 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/07 18:51:49 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_chunk_length(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

void	set_env_var(t_env **env, char *var, char *new)
{
	int	i;

	i = 0;
	if (!env || !*env || !var || !new || var[0] == '\0')
		return ;
	while (env[i] && ft_strncmp(env[i]->var, var, ft_strlen(env[i]->var)))
		i++;
	if (!env[i])
		return ;
	free(env[i]->value);
	env[i]->value = ft_strdup(new);
}

char	*get_env_var(t_env **env, char *var)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i]->var, var, ft_strlen(env[i]->var)))
		i++;
	if (!env[i])
		return (NULL);
	return (env[i]->value);
}

t_env	**dup_env(char **env)
{
	t_env	**var;
	int		i;

	i = 0;
	while (env[i])
		i++;
	var = malloc((sizeof(t_env *) * (i + 1)));
	if (!var)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		var[i] = safe_malloc(sizeof(t_env), (void **)var, i);
		if (!var[i])
			return (NULL);
		var[i]->var = ft_substr(env[i], 0, ft_chunk_length(env[i]));
		var[i]->value = ft_strdup(getenv(var[i]->var));
	}
	var[i] = NULL;
	return (var);
}
