/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27–– 16:08:33 by baouragh          #+#    #+#             */
/*   Updated: 2024/04/27 17:40:29 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft_V1/libft.h"


int main(int argc, char **argv, char **env)
{
    printf("----------->|%s|\n",argv[1]);
    char *cmd[4];
–––––––––≠≠
    cmd[0] = "grep";
    cmd[1] = "-E";
    cmd[2] = argv[1];
    cmd[3] = NULL;

    execve("/usr/bin/grep",cmd,env);
    printf("ERROR\n");
}