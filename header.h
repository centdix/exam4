#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BIN 1
#define CD 2
#define PIPE 3

typedef struct	s_lst
{
	int		type;
	char	**args;
	int		pipes[2];
	void	*prev;
	void	*next;
}				t_lst;

char	*ft_strjoin(char *str1, char *str2);
char	*ft_substr(char *str, int len);
char	**ft_split(char *str, char sep);
int     ft_strncmp(char *str1, char *str2, char max);

void	add_cmd(t_lst **lst_cmd, int type, char **args);

int		has_pipe(char *str);
void	parse_pipe(t_lst **lst_cmd, char *current);

int     run_bin(char **args);
int     run_cd(char **args);
