#include "header.h"

int     ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void    ft_putstr(char *str)
{
    write(2, str, ft_strlen(str));
}

int     ispipe(char *str)
{
    if (str && ft_strlen(str) == 1 && str[0] == '|')
        return (1);
    return (0);
}

int     issep(char *str)
{
    if (str && ft_strlen(str) == 1 && str[0] == ';')
        return (1);
    return (0);
}

t_lst   *new_cmd(int type, char **args)
{
    t_lst   *new;

    if (!(new = malloc(sizeof(t_lst))))
        return (NULL);
    new->type = type;
    new->args = args;
    new->prev = NULL;
    new->next = NULL;
    return (new);
}

int     add_cmd(t_lst **lst, int type, char **args)
{
    t_lst   *begin;
    t_lst   *to_add;

    begin = *lst;
    to_add = new_cmd(type, args);
    if (!to_add)
        return (1);
    if (begin)
    {
        while (begin->next)
            begin = begin->next;
        to_add->prev = begin;
        begin->next = to_add;
    }
    else
        *lst = to_add;
    return (0);
}