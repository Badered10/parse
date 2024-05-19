/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:06:35 by baouragh          #+#    #+#             */
/*   Updated: 2024/04/27 15:25:34 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft_V1/libft.h"

int ft_strlen_ascii(char *str, int c)
{
    int i;

    i = 0;
    while(str[i] != c)
        i++;
    return (i);
}

typedef struct  s_env
{
    char    *var;
    char    *value;
}               t_env;

t_env   **take_env(char **env) // VARIABLE='value'
{
    t_env **var;
    int i;

    i = 0;
    while(env[i])
        i++;
    var = malloc((sizeof(t_env *) * (i + 1)));
    if (!var)
        return (NULL);
    i = -1;
    while (env[++i])
    {
        var[i] = malloc(sizeof(t_env));
        var[i]->var = ft_substr(env[i], 0, ft_strlen_ascii(env[i], '='));
        var[i]->value = ft_strdup(getenv(var[i]->var));
    }
    var[i] = NULL;
    return(var);
}

void    search_and_replace(char *search_name, char *new_content, t_env **env)
{
    if (!env || !*env || !search_name || !new_content || search_name[0] == '\0')
        return ;
    while (*env && ft_strncmp((*env)->var, search_name, ft_strlen((*env)->var)))
        env++;
    if(!*env)
        return;
    printf("|%s|\n",(*env)->value);
    free((*env)->value);
    (*env)->value = ft_strdup(new_content);
    printf("|%s|\n",(*env)->value);
}

int main(int argc, char **argv, char **env)
{
    t_env **env_args = take_env(env);
    // t_env **tmp = env_args;
    // while(*env_args)
    // {
    //     printf("%s=%s\n",(*env_args)->var,(*env_args)->value);
    //     env_args++;
    // }
    // env_args = tmp;
    // printf("%s\n", getcwd(getenv("PWD"), sizeof(getenv("PWD"))));
    search_and_replace("USER","ACHRAF", env_args);
    // printf("%s\n", getcwd(getenv("PWD"), sizeof(getenv("PWD"))));
    system("leaks a.out");
}