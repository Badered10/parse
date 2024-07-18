/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:37:10 by alassiqu          #+#    #+#             */
/*   Updated: 2024/07/18 16:19:36 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_env_var(t_env *env, char *var, char *new)
{
	// printf("var '%p', %s\n,", var, var);
	// printf("new '%p', %s \n", new, new);
	// printf("env '%p', %s \n", env ,env->value);
	while (env && ft_strncmp(env->key, var, ft_strlen(env->key)))
		env = env->next;
	if (!env)
		return ;
	free(env->value);
	if (!new)
		env->value = NULL;
	else if (!ft_strcmp(new, "\0"))
		env->value = ft_strdup("");
	else
		env->value = ft_strdup(new);
}

char	*get_env_var(t_env *env, char *var)
{
	if (!var)
		return (NULL);
	while (env && ft_strncmp(env->key, var, ft_strlen(env->key)))
		env = env->next;
	if (env && ft_strlen(env->key) == ft_strlen(var))
	{
		if (env->value)
			return (env->value);
		else
			return ("");
	}
	else
		return (NULL);
}


void	delete_env_var(t_env **env, char *key)
{
	t_env	*current;
	t_env	*previous;

	if (!env || !*env)
		return ;
	current = *env;
	previous = NULL;
	if(!ft_strncmp((*env)->key, key, ft_strlen(key)))
	{
		(*env) = (*env)->next;
		free(current->value);
		free(current->key);
		// free(current);
		return;
	}
	while (current && ft_strncmp(current->key, key, ft_strlen(key)))
	{
		previous = current;
		current = current->next;
	}
	printf("khrej mn l while\n");
	if (!current)
		return ;
	printf("curr is not null\n");
	if (!previous)
	{
		printf("test test\n");
		*env = current->next;
	}
	else
		previous->next = current->next;
	printf("curr key >>>>>>>> '%s'\n", current->key);
	printf("curr value >>>>>>>> '%s'\n", current->value);
	printf("curr key >>>>>>>> '%p'\n", current);
	// gc_add(g_minishell, current->key);
	// gc_add(g_minishell, current->key);
	// gc_add(g_minishell, current);
}

void	clear_env(t_env *env)
{
	t_env	*current;
	t_env	*next;

	current = env;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current->key);
		free(current);
		current = next;
	}
	env = NULL;
}
