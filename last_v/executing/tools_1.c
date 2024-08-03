/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:11:26 by baouragh          #+#    #+#             */
/*   Updated: 2024/08/03 16:43:55 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <errno.h>
#include <stdio.h>

char	**get_env_paths(t_minishell *minishell)
{
	char	**res;
	char	*tmp;

	tmp = get_env_var(minishell->our_env, "PATH");
	if(!tmp)
		return (NULL);
	res = ft_split(tmp, ':');
	if(!res)
		return(NULL);
	return (res);
}

bool get_path_data(char *argv, char	**paths, char	***cmd, int *paths_num)
{
	if (!(paths))
		return (0);
	*paths_num = strings_count((paths));
	if(*paths_num == -1 || !*paths_num)
		return (free_double((paths)), 0);
	*cmd = ft_split(argv, ' ');
	if (!*cmd)
		return (free_double((paths)), 0);
	return (1);
}

char	*get_fullpath(char *argv, t_minishell *minishell)
{
	int		paths_num;
	char	**cmd;
	char	**paths;
	char	*fullpath;
	int		i;

	if (!argv || !*argv || ft_isspace(*argv))
		return (NULL);
	fullpath = NULL;
	i = 0;
	paths = get_env_paths(minishell);
	if (!get_path_data(argv, paths, &cmd, &paths_num))
		return (NULL);
	if (!(access(*cmd, F_OK)))
	{
		if ((*argv == '/' || *argv == '.') && !access(*cmd, X_OK))
			return (founded_cmd(argv, paths, cmd, minishell));
	}
	else if (*argv != '/' && *argv != '.')
		while (paths_num-- > 0 && !fullpath)
			fullpath = add_slash_cmd(paths[i++], *cmd);
	return (free_double(cmd), free_double(paths), fullpath);
}

int	check_cmd(char *argv, t_minishell *minishell)
{
	char		*cmd;
	struct stat	statbuf;

	statbuf.st_mode = 0;
	stat(argv, &statbuf);
	if (S_ISDIR(statbuf.st_mode) == true && ft_strchr(argv, '/'))
		return (print_err("Is a directory", argv), 126);
	cmd = get_fullpath(argv, minishell);
	gc_add(minishell, cmd);
	if (!cmd && *argv == '.')
		cmd = get_command(argv, minishell);
	if (*argv != '\0' && (*argv == '/' || *argv == '.'
			|| !get_env_var(minishell->our_env, "PATH")) && access(cmd, F_OK))
		return (print_err("no such file or directory", argv), 127);
	else if (ft_strlen(argv) == 1 && argv[0] == '.')
	{
		print_err("filename argument required\n.: usage: . filename [arguments]",
			NULL);
		return (2);
	}
	else if (access(cmd, F_OK) || (argv[0] == '.' &&  argv[1] == '.')) //
		return (print_err("command not found", argv), 127);
	else if (access(cmd, X_OK))
		return (print_err("permission denied", argv), 126);
	return (0);
}

void	call_execev(char **env, char *argv, char **cmd, t_minishell *minishell)
{
	char	*founded_path;
	int		len;

	len = ft_strlen(argv);
	founded_path = get_fullpath(argv, minishell);
	execve(founded_path, cmd, env);
	print_err("EXEVE FAILED ", NULL);
}

int	ft_malloc_error(char **tab, size_t i)
{
	size_t	j;

	j = 0;
	while (j <= i)
	{
		free(tab[j]);
		j++;
	}
	free(tab);
	return (1);
}
