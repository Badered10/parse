/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:50:08 by baouragh          #+#    #+#             */
/*   Updated: 2024/05/15 11:01:09 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

#include "charitr.h"

typedef struct t_scanner
{
    t_charitr charitr;
    t_token
    
}   t_scanner;

t_scanner scanner_value(const char *start, size_t lenght);
bool scanner_has_next(const t_scanner *self);
char scanner_peak(t_scanner *self);

#endif