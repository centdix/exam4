#include "header.h"

int     get_args(char ***args, int ac, char **av)
{
    int i;

    i = 0;
    while (av[i] && !issep(av[i]) && !ispipe(av[i]))
        i++;
    if (!(*args = malloc(sizeof(char *) * (i + 1))))
        return (1);
    i = 0;
    while (av[i] && !issep(av[i]) && !ispipe(av[i]))
    {
        (*args)[i] = av[i];
        i++;
    }
    (*args)[i] = NULL;
    return (0);
}

int     get_lst(t_lst **lst, int ac, char **av)
{
    char    **args;

    if (ac > 1)
    {
        av++;
        while (*av)
        {
            if (ispipe(*av))
            {
                add_cmd(lst, PIPE, NULL);
                av++;
            }
            else if (issep(*av))
                av++;
            else
            {
                if (get_args(&args, ac, av))
                    return (-1);
                if (ft_strlen(args[0]) == 2 && !strncmp(args[0], "cd", 2))
                    add_cmd(lst, CD, args);
                else
                    add_cmd(lst, BIN, args);
                while (*av && !issep(*av) && !ispipe(*av))
                    av++;
            }
        }
    }
    return (0);
}

int     launch_cmd(t_lst *lst)
{
    if (lst->type == CD)
        return (run_cd(lst->args));
    else if (lst->type == BIN)
        return (run_bin(lst));
    return (0);
}

int     main(int ac, char **av)
{
    t_lst   *lst;

    if (get_lst(&lst, ac, av) == -1)
    {
        ft_putstr("error: fatal\n");
        return (1);
    }
    while (lst)
    {
        if (launch_cmd(lst) == -1)
        {
            ft_putstr("error: fatal\n");
            return (1);
        }
        if (lst->args)
            free(lst->args);
        free(lst);
        lst = lst->next;
    }
    system("leaks a.out");
    return (0);
}