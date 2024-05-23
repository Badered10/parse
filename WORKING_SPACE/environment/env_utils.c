/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:46:08 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/11 15:34:04 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*safe_malloc(size_t size, void **data, int i)
{
	void	*ptr;
	int		j;

	j = -1;
	ptr = malloc(size);
	if (!ptr)
	{
		while (++j < i)
			free(data[j]);
		free(data);
		return (NULL);
	}
	return (ptr);
}

int	ft_key_length(char *str)
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
	while (env[i] && ft_strncmp(env[i]->key, var, ft_strlen(env[i]->key)))
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
	while (env[i] && ft_strncmp(env[i]->key, var, ft_strlen(env[i]->key)))
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
		var[i]->key = ft_substr(env[i], 0, ft_key_length(env[i]));
		var[i]->value = ft_strdup(getenv(var[i]->key));
	}
	var[i] = 0;
	return ((var));
}
