#include "header.h"

char	*get_cmd(int ac, char **av)
{
	int 	i;
	char	*cmd;
	char	*tmp;
	
	cmd = NULL;
	i = 1;
	while (i < ac)
	{
		tmp = cmd;
		cmd = ft_strjoin(tmp, av[i]);
		if (tmp)
			free(tmp);
		if (i != ac - 1)
		{
			tmp = cmd;
			cmd = ft_strjoin(tmp, " ");
			free(tmp);
		}
		i++;
	}
	return (cmd);
}

void	parse_cmd(t_lst **lst_cmd, char *cmd)
{
	char	**args;
	char	*current;
	int		i;

	while (*cmd)
	{
		i = 0;
		while (cmd[i] != ';' && cmd[i])
			i++;
		current = ft_substr(cmd, i);
		if (has_pipe(current))
			parse_pipe(lst_cmd, current);
		else
		{
			args = ft_split(current, ' ');
			if (!ft_strncmp(args[0], "cd", 2))
				add_cmd(lst_cmd, CD, args);
			else
				add_cmd(lst_cmd, BIN, args);
		}
		free(current);
		while (*cmd != ';' && *cmd)
			cmd++;
		while (*cmd == ';')
			cmd++;
	}
}

int		launch_cmd(t_lst *lst_cmd)
{
	t_lst	*next;
	t_lst	*prev;

	next = lst_cmd->next;
	prev = lst_cmd->prev;
	if (lst_cmd->type == BIN)
	{
		if (next && next->type == PIPE)
			pipe(next->pipes);
		if (!(fork()))
		{
			if (prev && prev->type == PIPE)
				dup2(prev->pipes[0], 0);
			if (next && next->type == PIPE)
				dup2(next->pipes[1], 1);
			return (run_bin(lst_cmd->args));
		}
		else
			wait(NULL);
		if (prev && prev->type == PIPE)
			close(prev->pipes[0]);
		if (next && next->type == PIPE)
			close(next->pipes[1]);
	}
	else if (lst_cmd->type == CD)
		return (run_cd(lst_cmd->args));
	return (0);
}

int 	main(int ac, char **av)
{
	char 	*cmd;
	t_lst	*lst_cmd;
	int		ret;

	cmd = get_cmd(ac, av);
	if (cmd)
	{
		parse_cmd(&lst_cmd, cmd);
		while (lst_cmd)
		{
			ret = launch_cmd(lst_cmd);
			lst_cmd = lst_cmd->next;
		}
	}
	return (0);
}
