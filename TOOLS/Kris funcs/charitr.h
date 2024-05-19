/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charitr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:34:12 by baouragh          #+#    #+#             */
/*   Updated: 2024/05/14 15:48:53 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARITR_H
# define CHARITR_H

#include <stddef.h>
#include <stdbool.h>

typedef struct t_charitr
{
    char *cursor;
    char *guard;
}           t_charitr;

t_charitr charitr_value(const char *start, size_t lenght);
const char * charitr_cursor(const t_charitr *self);
bool charitr_has_next(const t_charitr *self);
char charitr_peak(t_charitr *self);

#endif