/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baouragh <baouragh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:33:43 by baouragh          #+#    #+#             */
/*   Updated: 2024/06/25 16:40:59 by baouragh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int  env_size(t_env *env)
{
    int size;
    
    size = 0;
    while(env)
    {
        size++;
        env = env->next;
    }
    return(size);
}

void print_double(char ** argv)
{
    int i = 0;

    while(argv[i])
    {
        printf("%s\n",argv[i]);
        i++;
    }
}

char **env_to_envp(t_env *env)
{
    char **argv;
    int size;
    int i;
    int len;

    i = 0;
    size = env_size(env);
    argv = malloc(sizeof(char *) * (size + 1));
    while(i < size)
    {
        len = ft_strlen(env->key) + ft_strlen(env->value) + 2; // +2 one for \0 , and one for = symbol
        argv[i] = malloc(sizeof(char) * len);
        argv[i] = ft_strjoin(ft_strjoin(env->key, "="),env->value);
        env = env->next;
        i++;
    }
    argv[i] = NULL;
    return(argv);
}

char **list_to_argv(t_list *list)
{
    char **argv;
    int size;
    int i;
    int len;

    i = 0;
    size = ft_lstsize(list);
    argv = malloc(sizeof(char *) * (size + 1));
    while(i < size)
    {
        len = ft_strlen(list->content) + 1;
        argv[i] = malloc(sizeof(char) * len);
        ft_memmove(argv[i], list->content, len);
        list = list->next;
        i++;
    }
    argv[i] = NULL;
    return(argv);
}
void do_cmd(void)
{
    int id;

    id = fork();
    if (!id)
    {
        execve("/bin/ls", list_to_argv(g_minishell->ast->data.cmd), list_to_argv(g_minishell->ast->data.cmd));
    }
    else
    {
        wait(NULL);
    }
}

void execution(t_node *node) // execve( char *path, char **argv, char **envp);
{
    
//     if (!node) return;

    if (node->type == STRING_NODE)
    {
        // print_double(list_to_argv(node->data.cmd));
        // print_double(env_to_envp(g_minishell->our_env));
        do_cmd();
    }
	// else if(node->type == PAIR_NODE)
	// {
    //         printAST(node->data.pair.left, 1 , tmp);
    //         printAST(node->data.pair.right, 0 , tmp);
    // }
//     else if (node->type == REDIR_NODE)
//     {
//         while(node->data.redir)
//         {
//             t_redir *new = node->data.redir->content;
//             printf("REDIR NODE , name: '%s'\n",new->file);
//             while (new->cmd)
//             {
//                 printf("'%s' ", (char*)new->cmd->content);
//                 new->cmd = new->cmd->next;
//             }
//             printf("\n");
//             node->data.redir = node->data.redir->next;
//         }
//     }
//     else if(node->type == ERROR_NODE)
//     {
//         printf("add'%p', -ERROR -------> '%s",node ,node->data.error);
//     }
}