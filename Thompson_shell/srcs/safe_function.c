/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:09:58 by alassiqu          #+#    #+#             */
/*   Updated: 2024/05/11 10:25:50 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*safe_malloc(size_t size, void **data, int i)
{
	void	*ptr;
	int		j;

	j = 0;
	ptr = malloc(size);
	if (!ptr)
	{
		while (j++ < i)
			free(data[j]);
		free(data);
		return (NULL);
	}
	return (ptr);
}
