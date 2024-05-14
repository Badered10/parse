/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charitr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:39:21 by baouragh          #+#    #+#             */
/*   Updated: 2024/05/14 15:47:40 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "charitr.h"

t_charitr charitr_value(const char *start, size_t lenght)
{
    t_charitr res;
    res.cursor = start;
    res.guard = start + lenght;
    return(res);
}
const char * charitr_cursor(const t_charitr *self)
{
    return(self->cursor);
}

bool charitr_has_next(const t_charitr *self)
{
    return (self->cursor != self->guard && self->cursor != '\0' 
            && self->cursor != '\n');
}

char charitr_peak(t_charitr *self)
{
    char c;
    if(charitr_has_next(self))
    {
        c = *(self->cursor);
        (self->cursor)++;
        return(c);
    }
    else
        return ('\0');
}
