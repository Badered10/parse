/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:57:05 by baouragh          #+#    #+#             */
/*   Updated: 2024/06/26 10:57:09 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_malloc(t_minishell *mini, size_t size)
{
	char	*memory;

	memory = malloc(size);
	if (!memory)
		return (perror("malloc failed!"), NULL);
	gc_add(mini, memory);
	return (memory);
}
