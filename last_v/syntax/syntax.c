/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:13:52 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/03 17:44:53 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	syntax_first_phase(t_token *token)
{
	if (first_checker_left(token) == -1)
		return (-1);
	if (first_checker_right(token) == -1)
		return (-1);
	return (0);
}

int	count_nb_here_doc(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == LL_REDIR)
			count++;
		tokens = tokens->next;
	}
	if (count > 16)
	{
		print_errors("maximum here-document count exceeded");
		return (-1);
	}
	else
		return (0);
}

int	general_check(t_minishell *minishell)
{
	if (nb_paren(minishell))
		return (-1);
	if (nb_quotes(minishell))
		return (-1);
	if (count_nb_here_doc(minishell->tokens))
		return (-1);
	return (0);
}

int	syntax(t_minishell *minishell)
{
	t_token	*token;

	check_hd_expand(minishell->tokens);
	remove_whitespaces(&minishell->tokens);
	token = minishell->tokens;
	while (token)
	{
		if (syntax_first_phase(token) || syntax_second_phase(token)
			|| syntax_third_phase(token))
		{
			set_env_var(minishell->our_env, "?", "2");
			gc_free_all(minishell);
			return (-1);
		}
		token = token->next;
	}
	if (general_check(minishell) == -1)
	{
		set_env_var(minishell->our_env, "?", "2");
		gc_free_all(minishell);
		return (-1);
	}
	return (0);
}
