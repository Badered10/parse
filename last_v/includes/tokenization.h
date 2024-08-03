/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:04:32 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/03 17:56:54 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include <stdbool.h>

typedef enum e_type
{
	WORD,
	PIPE,
	OR,
	AND,
	LL_REDIR,
	RR_REDIR,
	L_REDIR,
	R_REDIR,
	END,
	L_PAREN,
	R_PAREN,
	S_QUOTE,
	D_QUOTE,
	ASTERISK,
	DOLLAR,
	AMPERSAND,
	WHITESPACE,
	WORD_QUOTE,
	ERROR
}					t_type;

typedef struct s_token
{
	char			*value;
	t_type			type;
	bool			hd_expand;
	bool			word_expand;
	int				next_space;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

#endif /* TOKENIZATION_H */