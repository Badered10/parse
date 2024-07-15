/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:38:21 by baouragh          #+#    #+#             */
/*   Updated: 2024/06/26 10:38:22 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MEMORY_H
# define MEMORY_H

typedef struct s_gc
{
	void		*ptr;
	struct s_gc	*next;
}				t_gc;

#endif /* MEMORY_H */