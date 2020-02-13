#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BIN 2
#define CD 3
#define PIPE 4

typedef struct  s_lst
{
    int     type;
    int     pipes[2];
    char    **args;
    void    *prev;
    void    *next;
}               t_lst;

int     ft_strlen(char *str);
int     ispipe(char *str);
int     issep(char *str);
void    ft_putstr(char *str);
int     add_cmd(t_lst **lst, int type, char **args);
int     run_cd(char **args);
int     run_bin(t_lst *lst);