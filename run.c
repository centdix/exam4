#include "header.h"

int     run_cd(char **args)
{
    int i;

    i = 0;
    while (args[i])
        i++;
    if (i != 2)
    {
        ft_putstr("error: cd: bad arguments\n");
        return (1);
    }
    if (chdir(args[1]) == -1)
    {
        ft_putstr("error: cd: cannot change directory to ");
        ft_putstr(args[1]);
        ft_putstr("\n");
        return (1);
    }
    return (0);
}

int     run_bin(t_lst *lst)
{
    t_lst   *prev;
    t_lst   *next;
    int     ret;

    prev = lst->prev;
    next = lst->next;
    if (next && next->type == PIPE)
        if (pipe(next->pipes) == -1)
            return (-1);
    ret = fork();
    if (ret == -1)
        return (-1);
    if (!ret)
    {
        if (next && next->type == PIPE)
        {
            if (dup2(next->pipes[1], 1) == -1)
                return (-1);
            if (close(next->pipes[1]) == -1)
                return (-1);
        }
        if (prev && prev->type == PIPE)
        {
            if (dup2(prev->pipes[0], 0) == -1)
                return (-1);
            if (close(prev->pipes[0]) == -1)
                return (-1);
        }
        if (execv(lst->args[0], lst->args) == -1)
        {
            ft_putstr("error: cannot execute ");
            ft_putstr(lst->args[0]);
            ft_putstr("\n");
            exit(0);
        }
        return (0);
    }
    else
        if (waitpid(-1, NULL, 0) == -1)
            return (-1);
    if (next && next->type == PIPE)
        if (close(next->pipes[1]) == -1)
            return (-1);
    if (prev && prev->type == PIPE)
        if (close(prev->pipes[0]) == -1)
            return (-1);
    return (0);
}