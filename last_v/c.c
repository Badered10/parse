#include "includes/minishell.h"
#include <signal.h>

void ft_h(int sig)
{
    fprintf(stderr,"hello\n");
}

int main()
{
    signal(SIGQUIT, ft_h);

    close(0);
    close(1);
    while(1);
}