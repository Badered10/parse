/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:02:18 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/12 16:47:11 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
	1) first read a line .
	2) token it with supported symbols .
	3) pars it , like in input like "echo "hello exemple"" 
	must be echo -> CMD, and 'hello exemple'-> ARG .
	4) link it in a tree
*/


#include "includes/minishell.h"

void	check_builtins(t_mini *mini)
{
	if (ft_strncmp(mini->input, "env", 3) == 0)
		ft_env(mini->our_env);
	else if (ft_strncmp(mini->input, "pwd", 3) == 0)
		ft_pwd(mini);
	// else if (ft_strncmp(mini->input, "echo", 4) == 0) // echo hello | echo " hello" | echo hello > file | echo hello >> file
	// 	ft_echo(mini, 1);
	else if (ft_strncmp(mini->input, "env", 3) == 0)
		ft_env(mini->our_env);
	// else if (ft_strncmp(mini->input, "exit", 4) == 0)
	// 	ft_exit();
	// else if (ft_strncmp(mini->input, "export", 6) == 0)
	// 	ft_export();
	// else if (ft_strncmp(mini->input, "unset", 5) == 0)
	// 	ft_unset();
}

void	check_for_input(t_mini *mini)
{
	t_token	*token;

	token = malloc(sizeof(t_token) * (ft_strlen(mini->input) + 1));
	if (token)
		tokenizer(mini, token);
	free(mini->input);
}

void	minishell(char **env)
{
	t_mini	*mini = NULL;

	mini = malloc(sizeof(t_mini));
	if (!mini)
		return ;
	mini->input = NULL;
	mini->tokens = NULL;
	mini->our_env = dup_env(env);
    while (1)
    {
        mini->input = ft_strtrim(readline(ORANGE"$minishell > "RESET), " \t\n\v\r\f");
		if(!mini->input)
			return(ft_putstr_fd("ERROR NULL in strtrim\n",2));
		check_for_input(mini);
    }
}

// int	main(int ac, char **av, char **env)
// {
//     (void)av;
// 	if (ac == 1)
// 		minishell(env);
// 	else
// 		printf("Expected : ./minishell\n");
// 	return (0);
// }

int main(void)
{
    t_tree *root = creat_node(ft_strdup("\t\t[DATA 1]"));
	
	insert_data(root, ft_strdup("[left Child a]"),LEFT);
	insert_data(root, ft_strdup("[Right Child b]"),RIGHT);
	insert_data(root->left, ft_strdup("[left Child c]"),LEFT);
	insert_data(root->left, ft_strdup("[Right Child d]"),RIGHT);
	while(root)
	{
		printf("%s\n",root->data);
		root = root->left;
	}
}
