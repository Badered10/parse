/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charitr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:39:21 by baouragh          #+#    #+#             */
/*   Updated: 2024/05/15 12:42:55 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "charitr.h"

t_charitr charitr_value(const char *start, size_t lenght) // []
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
    return (self->cursor != self->guard);
}

char charitr_peak(const t_charitr *self)
{
        return(*(self->cursor));
}

// void charitr_next(t_charitr *self)
// {
//     if(charitr_has_next(self))
//         (self->cursor)++;
//     return;
// }