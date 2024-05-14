/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:42:10 by alassiqu          #+#    #+#             */
/*   Updated: 2024/04/30 17:08:05 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_quotes(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	return (0);
}

int	ft_is_pipe(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	ft_is_redirection(char c)
{
	if (c == '>')
		return (1);
	else if (c == '<')
		return (2);
	return (0);
}

int	ft_iswhitespace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

void	tokenizer(t_mini *mini, t_token *token)
{
	int	start;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mini->input[i])
	{
		start = i;
		if (ft_isalpha(mini->input[i]))
		{
			while (ft_isalpha(mini->input[i]))
				i++;
			token[j].str = ft_substr(mini->input, start, i - start);
            token[j++].type = WORD;
		}
		else if (ft_iswhitespace(mini->input[i]))
		{
			while (ft_iswhitespace(mini->input[i]))
                i++;
			token[j].str = ft_substr(mini->input, start, i - start);
            token[j++].type = WHITE_SPACE;
		}
		else if (ft_is_redirection(mini->input[i]))
		{
			while (ft_is_redirection(mini->input[i]))
                i++;
			if(i - start == 3)
				return(ft_putstr_fd("Minishell: syntax error near unexpected token `>'\n",2));
			else if(i - start > 3)
				return(ft_putstr_fd("Minishell: syntax error near unexpected token `>>'\n",2));
			token[j].str = ft_substr(mini->input, start, i - start);
			if (ft_strncmp(token[j].str, "<<", 2) == 0 && ft_strlen(token[j].str) == 2)
            	token[j++].type = REDIR_LL;
			else if (ft_strncmp(token[j].str, ">>", 2) == 0 && ft_strlen(token[j].str) == 2)
            	token[j++].type = REDIR_RR;
			else if (ft_strncmp(token[j].str, "<", 1) == 0 && ft_strlen(token[j].str) == 1)
            	token[j++].type = REDIR_L;
			else if (ft_strncmp(token[j].str, ">", 1) == 0 && ft_strlen(token[j].str) == 1)
            	token[j++].type = REDIR_R;
		}
		else if (ft_is_pipe(mini->input[i]))
		{
			while (ft_is_pipe(mini->input[i]))
                i++;
			if(i - start > 2)
				return(ft_putstr_fd("Minishell: syntax error near unexpected token `||'\n",2));
			token[j].str = ft_substr(mini->input, start, i - start);
            token[j++].type = PIPE;
		}
		else if (ft_is_quotes(mini->input[i]))
		{
			while (ft_is_quotes(mini->input[i]))
                i++;
			// if(i - start == 3)
			// 	return(ft_putstr_fd( "Minishell: syntax error near unexpected token `>'\n",2));
			// else if(i - start > 3)
			// 	return(ft_putstr_fd("Minishell: syntax error near unexpected token `>>'\n",2));
			token[j].str = ft_substr(mini->input, start, i - start);
			if (ft_strncmp(token[j].str, "\"", 1) == 0)
            	token[j++].type = QUOTE_D;
			else if (ft_strncmp(token[j].str, "\'", 1) == 0)
            	token[j++].type = QUOTE_S;
		}
		else if (mini->input[i])
		{
			i++;
			token[j].str = ft_substr(mini->input, start, i - start);
            token[j++].type = OTHER;
		}
	}
	printf("number of tokens is %d\n", j);
	int k = 0;
	while (k < j)
	{
		printf("the token %d is a %d\n", k, token[k].type);
		printf("its value is '%s'\n", token[k].str);
		k++;
	}
}
