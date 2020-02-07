#include "header.h"

int     run_bin(char **args)
{
    if (execv(args[0], args) == -1)
    {
        printf("error: cmd not found\n");
        return (1);
    }
    return (0);
}

int     run_cd(char **args)
{
    int i;

    i = 0;
    while (args[i])
        i++;
    if (i > 2)
    {
        printf("error: argument\n");
        return (1);
    }
    if (chdir(args[1]) == -1)
    {
        printf("error: wrong argument\n");
        return (1);
    }
    return (0);
}