/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 21:14:00 by alassiqu          #+#    #+#             */
/*   Updated: 2024/08/03 16:09:08 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

// Function that custome the splitted string.
char	**custome_split(char **split);

// Function that free the split.
void	free_split(char **s);

#endif /* BUILTINS_H */