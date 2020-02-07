#include "header.h"

int		has_pipe(char *str)
{
	while (*str)
	{
		if (*str == '|')
			return (1);
		str++;
	}
	return (0);
}

void	parse_pipe(t_lst **lst_cmd, char *current)
{
	char 	**args;
	char 	**cmds;
	int		i;

	cmds = ft_split(current, '|');
	i = 0;
	while (cmds[i])
	{
		args = ft_split(cmds[i], ' ');
		if (!ft_strncmp(args[0], "cd", 2))
			add_cmd(lst_cmd, CD, args);
		else
			add_cmd(lst_cmd, BIN, args);
		if (cmds[i + 1])
			add_cmd(lst_cmd, PIPE, NULL);
		free(cmds[i]);
		i++;
	}
	free(cmds);
}	
